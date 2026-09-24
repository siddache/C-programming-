#!/usr/bin/env python3
"""Debounce repository edits into commits and sync them to origin safely.

The watcher does not touch manually staged work, sensitive files, or a
repository that is in the middle of a rebase or merge. Set
AUTO_PUSH_TEST_COMMAND to run a project-specific check before an automatic
commit, for example: ``gcc -Wall -Wextra path/to/file.c``.
"""

from __future__ import annotations

import os
import subprocess
import threading
import time
from pathlib import Path

from watchdog.events import FileSystemEventHandler
from watchdog.observers import Observer


REPO_DIR = Path(__file__).resolve().parent
DEBOUNCE_SECONDS = float(os.environ.get("AUTO_PUSH_DEBOUNCE_SECONDS", "3"))
GIT_TIMEOUT_SECONDS = int(os.environ.get("AUTO_PUSH_GIT_TIMEOUT_SECONDS", "60"))
IGNORED_DIRS = {
    ".git",
    ".venv",
    "venv",
    "node_modules",
    "__pycache__",
    ".vscode",
    "build",
    "dist",
}
IGNORED_FILES = {"auto_push.log"}
SENSITIVE_FILE_SUFFIXES = (".pem", ".key", ".p12", ".pfx", ".kdbx")
SENSITIVE_FILE_NAMES = {
    ".env",
    "id_rsa",
    "id_dsa",
    "id_ecdsa",
    "id_ed25519",
    "credentials.json",
    "secrets.json",
}
LOCK_HINTS = (
    "unable to create",
    "index.lock",
    "cannot lock ref",
    "another git process seems to be running",
)
TRANSIENT_NETWORK_HINTS = (
    "could not resolve host",
    "connection timed out",
    "connection reset",
    "remote end hung up",
    "the requested url returned error: 5",
)
OPERATION_MARKERS = (
    "MERGE_HEAD",
    "CHERRY_PICK_HEAD",
    "REVERT_HEAD",
    "rebase-apply",
    "rebase-merge",
)


def report(message: str) -> None:
    """Write a timestamped status message without causing watcher feedback."""
    line = f"{time.strftime('%Y-%m-%d %H:%M:%S')}  {message}"
    print(line, flush=True)
    try:
        with (REPO_DIR / "auto_push.log").open("a", encoding="utf-8") as log:
            log.write(line + "\n")
    except OSError:
        # Console output is still useful if the log cannot be created.
        pass


def run_git(
    args: list[str], retries: int = 3, retry_network: bool = False
) -> subprocess.CompletedProcess[str]:
    """Run Git with bounded lock/network retries and a timeout."""
    command = ["git", "-C", str(REPO_DIR), *args]
    hints = LOCK_HINTS + (TRANSIENT_NETWORK_HINTS if retry_network else ())

    for attempt in range(retries + 1):
        try:
            result = subprocess.run(
                command,
                capture_output=True,
                text=True,
                timeout=GIT_TIMEOUT_SECONDS,
                check=False,
            )
        except FileNotFoundError:
            return subprocess.CompletedProcess(command, 127, "", "Git is not installed or is not on PATH.")
        except subprocess.TimeoutExpired:
            return subprocess.CompletedProcess(
                command,
                124,
                "",
                f"Git command timed out after {GIT_TIMEOUT_SECONDS} seconds.",
            )

        if result.returncode == 0:
            return result

        output = f"{result.stderr or ''}{result.stdout or ''}".lower()
        if attempt < retries and any(hint in output for hint in hints):
            time.sleep(1.5 * (attempt + 1))
            continue
        return result

    raise RuntimeError("Unreachable Git retry state")


def error_text(result: subprocess.CompletedProcess[str]) -> str:
    return (result.stderr or result.stdout or "Git command failed.").strip()


def should_ignore(path: str) -> bool:
    candidate = Path(path)
    if candidate.name.casefold() in IGNORED_FILES:
        return True
    return any(part.casefold() in IGNORED_DIRS for part in candidate.parts)


def should_ignore_event(event: object) -> bool:
    """Ignore only if every affected path is ignored, including rename targets."""
    paths = [getattr(event, "src_path", "")]
    destination = getattr(event, "dest_path", None)
    if destination:
        paths.append(destination)
    return bool(paths) and all(should_ignore(path) for path in paths)


def repository_operation() -> str | None:
    """Return the active Git operation that must be resolved by a person."""
    for marker in OPERATION_MARKERS:
        result = run_git(["rev-parse", "--git-path", marker], retries=0)
        if result.returncode != 0:
            continue
        marker_path = Path(result.stdout.strip())
        if not marker_path.is_absolute():
            marker_path = REPO_DIR / marker_path
        if marker_path.exists():
            return marker
    return None


def current_branch() -> str | None:
    result = run_git(["symbolic-ref", "--quiet", "--short", "HEAD"], retries=0)
    if result.returncode != 0:
        return None
    return result.stdout.strip() or None


def working_paths() -> tuple[list[str] | None, str | None]:
    """List only unstaged/untracked paths so automatic staging is scoped."""
    # Disabling rename detection returns both sides of a rename so `git add -A`
    # can stage the old-path deletion as well as the new-path addition.
    modified = run_git(["diff", "--no-renames", "--name-only", "-z"], retries=0)
    untracked = run_git(["ls-files", "--others", "--exclude-standard", "-z"], retries=0)
    if modified.returncode != 0:
        return None, error_text(modified)
    if untracked.returncode != 0:
        return None, error_text(untracked)

    paths = set(filter(None, modified.stdout.split("\0")))
    paths.update(filter(None, untracked.stdout.split("\0")))
    return sorted(paths), None


def is_sensitive(path: str) -> bool:
    name = Path(path).name.casefold()
    return (
        name in SENSITIVE_FILE_NAMES
        or name.startswith(".env.")
        or name.endswith(SENSITIVE_FILE_SUFFIXES)
    )


def has_staged_changes() -> tuple[bool | None, str | None]:
    result = run_git(["diff", "--cached", "--quiet"], retries=0)
    if result.returncode == 0:
        return False, None
    if result.returncode == 1:
        return True, None
    return None, error_text(result)


def commit_message(paths: list[str]) -> str:
    shown = ", ".join(paths[:3]).replace("\n", " ")
    if len(paths) > 3:
        shown += f" (+{len(paths) - 3} more)"
    return f"auto: update {shown}"[:200]


def run_quality_gate() -> bool:
    command = os.environ.get("AUTO_PUSH_TEST_COMMAND", "").strip()
    if not command:
        return True

    report(f"Running AUTO_PUSH_TEST_COMMAND: {command}")
    try:
        result = subprocess.run(
            command,
            cwd=REPO_DIR,
            shell=True,
            capture_output=True,
            text=True,
            timeout=GIT_TIMEOUT_SECONDS,
            check=False,
        )
    except subprocess.TimeoutExpired:
        report("Quality check timed out; changes were not committed.")
        return False

    if result.returncode == 0:
        return True
    report(result.stderr.strip() or result.stdout.strip() or "Quality check failed; changes were not committed.")
    return False


def worktree_is_clean() -> tuple[bool | None, str | None]:
    result = run_git(["status", "--porcelain"], retries=0)
    if result.returncode != 0:
        return None, error_text(result)
    return not bool(result.stdout.strip()), None


def pull_rebase(branch: str) -> bool:
    result = run_git(["pull", "--rebase", "origin", branch], retries=2, retry_network=True)
    if result.returncode == 0:
        return True
    report(f"Remote sync stopped: {error_text(result)}")
    return False


def sync_remote(branch: str) -> None:
    """Rebase onto the remote branch before an explicit, retryable push."""
    clean, problem = worktree_is_clean()
    if clean is None:
        report(f"Cannot check repository status: {problem}")
        return
    if not clean:
        # A new save happened after staging/committing. Its event will schedule
        # another run; never rebase over it.
        report("New edits detected during sync; they will be handled in the next run.")
        return

    if not pull_rebase(branch):
        return

    destination = f"HEAD:refs/heads/{branch}"
    push = run_git(["push", "origin", destination], retries=2, retry_network=True)
    if push.returncode == 0:
        report(f"Synced {branch} to origin.")
        return

    push_error = error_text(push)
    non_fast_forward = any(
        token in push_error.lower() for token in ("rejected", "fetch first", "non-fast-forward")
    )
    if not non_fast_forward:
        report(f"Push failed: {push_error}")
        return

    # The remote advanced between pull and push. One fresh rebase is safe on a
    # clean worktree; conflicts remain untouched for manual resolution.
    report("Remote changed during push; retrying one safe rebase.")
    if not pull_rebase(branch):
        return
    retry = run_git(["push", "origin", destination], retries=2, retry_network=True)
    if retry.returncode == 0:
        report(f"Synced {branch} to origin after retry.")
    else:
        report(f"Push failed after retry: {error_text(retry)}")


class RepoChangeHandler(FileSystemEventHandler):
    def __init__(self) -> None:
        self.timer_lock = threading.Lock()
        self.commit_lock = threading.Lock()
        self.timer: threading.Timer | None = None

    def on_any_event(self, event: object) -> None:
        # Git does not track empty directories. Ignoring directory metadata also
        # prevents the local log file from feeding back into the watcher.
        if getattr(event, "is_directory", False):
            return
        if should_ignore_event(event):
            return
        self.schedule_sync()

    def schedule_sync(self) -> None:
        with self.timer_lock:
            if self.timer is not None:
                self.timer.cancel()
            self.timer = threading.Timer(DEBOUNCE_SECONDS, self.commit_and_push)
            self.timer.daemon = True
            self.timer.start()

    def flush(self) -> None:
        """Cancel the debounce delay and complete one final serialized sync."""
        with self.timer_lock:
            if self.timer is not None:
                self.timer.cancel()
                self.timer = None
        self.commit_and_push()

    def commit_and_push(self) -> None:
        # Several timers can cross their cancellation boundary. This lock makes
        # every Git transaction strictly one-at-a-time.
        with self.commit_lock:
            try:
                operation = repository_operation()
                if operation:
                    report(f"Git {operation} is in progress; resolve it manually before auto-sync resumes.")
                    return

                branch = current_branch()
                if not branch:
                    report("HEAD is detached; automatic push is paused to avoid updating the wrong branch.")
                    return

                remote = run_git(["remote", "get-url", "origin"], retries=0)
                if remote.returncode != 0:
                    report("Remote 'origin' is not configured; automatic push is paused.")
                    return

                staged, staged_error = has_staged_changes()
                if staged is None:
                    report(f"Cannot inspect staged changes: {staged_error}")
                    return
                if staged:
                    report("Manually staged changes detected; automatic commit is paused to preserve them.")
                    return

                paths, path_error = working_paths()
                if paths is None:
                    report(f"Cannot inspect working changes: {path_error}")
                    return

                sensitive_paths = [path for path in paths if is_sensitive(path)]
                if sensitive_paths:
                    report(f"Sensitive-looking file changed; refusing to stage: {', '.join(sensitive_paths)}")
                    return

                if paths:
                    # Run before staging so a failed check leaves the user's
                    # index exactly as it was.
                    if not run_quality_gate():
                        return

                    add = run_git(["add", "-A", "--", *paths])
                    if add.returncode != 0:
                        report(f"Staging failed: {error_text(add)}")
                        return

                    message = commit_message(paths)
                    commit = run_git(["commit", "-m", message])
                    if commit.returncode != 0:
                        report(f"Commit failed: {error_text(commit)}")
                        return
                    report(f"Created {message!r}.")

                # Runs even with no edits so a previously failed push is
                # retried on startup or on the next meaningful filesystem event.
                sync_remote(branch)
            except Exception as exc:  # Keep the watcher alive after errors.
                report(f"Auto-push error: {exc}")


if __name__ == "__main__":
    handler = RepoChangeHandler()
    observer = Observer()
    observer.schedule(handler, str(REPO_DIR), recursive=True)
    observer.start()
    report(f"Watching {REPO_DIR} (debounce: {DEBOUNCE_SECONDS:g}s). Press Ctrl+C to stop.")

    # Also handles edits made while the watcher was stopped and retries an
    # earlier failed push even if the worktree is already clean.
    handler.schedule_sync()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        report("Stopping watcher; finishing one final sync.")
    finally:
        observer.stop()
        observer.join()
        handler.flush()
