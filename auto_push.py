#!/usr/bin/env python3
import os
import subprocess
import threading
import time
from pathlib import Path

from watchdog.events import FileSystemEventHandler
from watchdog.observers import Observer

REPO_DIR = Path(__file__).resolve().parent
IGNORED_DIRS = {".git", ".venv", "venv", "node_modules", "__pycache__"}
LOCK_HINTS = (
    "unable to create",
    "index.lock",
    "cannot lock ref",
    "another git process seems to be running",
)


def run_git(args, check=False, capture_output=True, retries=3):
    last = None
    for attempt in range(retries + 1):
        last = subprocess.run(
            ["git", "-C", str(REPO_DIR), *args],
            check=check,
            capture_output=capture_output,
            text=True,
        )
        if last.returncode == 0:
            return last

        err = (last.stderr or "") + (last.stdout or "")
        if any(hint in err.lower() for hint in LOCK_HINTS):
            if attempt < retries:
                time.sleep(1.5 * (attempt + 1))
                continue
        break
    return last


def ensure_git_identity():
    name = run_git(["config", "--get", "user.name"], check=False)
    if not name.stdout.strip():
        run_git(["config", "user.name", "AutoPush Bot"], check=False)

    email = run_git(["config", "--get", "user.email"], check=False)
    if not email.stdout.strip():
        run_git(["config", "user.email", "autopush@example.com"], check=False)


class RepoChangeHandler(FileSystemEventHandler):
    def __init__(self):
        self.lock = threading.Lock()
        self.timer = None

    def on_any_event(self, event):
        if event.is_directory:
            return
        if should_ignore(event.src_path):
            return
        self.schedule_commit()

    def schedule_commit(self, event=None):
        with self.lock:
            if self.timer is not None:
                self.timer.cancel()
            self.timer = threading.Timer(2.5, self.commit_and_push)
            self.timer.daemon = True
            self.timer.start()

    def commit_and_push(self):
        try:
            status = run_git(["status", "--porcelain"], check=False)
            if not status.stdout.strip():
                return

            run_git(["add", "-A"], check=True)
            message = f"auto-commit {time.strftime('%Y-%m-%d %H:%M:%S')}"
            commit = run_git(["commit", "-m", message], check=False)
            if commit.returncode != 0:
                if "nothing to commit" in (commit.stderr or "").lower():
                    return
                print(commit.stderr.strip() or commit.stdout.strip())
                return

            push = run_git(["push", "origin", "HEAD"], check=False)
            if push.returncode != 0:
                error = push.stderr.strip() or push.stdout.strip()
                print(error or "Push failed.")
            else:
                print("Pushed successfully.")
        except Exception as exc:
            print(f"Auto-push error: {exc}")


def should_ignore(path: str) -> bool:
    p = Path(path)
    for part in p.parts:
        if part in IGNORED_DIRS:
            return True
    return False


def ensure_single_instance():
    pid_file = REPO_DIR / ".git" / "autopush.pid"
    pid = None
    if pid_file.exists():
        try:
            pid = int(pid_file.read_text().strip())
        except ValueError:
            pid = None

        if pid is not None:
            try:
                os.kill(pid, 0)
                print(f"Another auto-push watcher is already running with PID {pid}.")
                raise SystemExit(0)
            except OSError:
                pid_file.unlink(missing_ok=True)

    pid_file.parent.mkdir(parents=True, exist_ok=True)
    pid_file.write_text(str(os.getpid()))


if __name__ == "__main__":
    ensure_single_instance()
    ensure_git_identity()
    handler = RepoChangeHandler()

    observer = Observer()
    observer.schedule(handler, str(REPO_DIR), recursive=True)
    observer.start()
    print(f"Watching {REPO_DIR} for file changes. Press Ctrl+C to stop.")

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    finally:
        observer.join()
        try:
            (REPO_DIR / ".git" / "autopush.pid").unlink(missing_ok=True)
        except Exception:
            pass
