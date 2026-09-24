#!/usr/bin/env python3
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


def run_git(args, retries=3):
    for attempt in range(retries + 1):
        result = subprocess.run(
            ["git", "-C", str(REPO_DIR), *args],
            capture_output=True,
            text=True,
        )
        if result.returncode == 0:
            return result

        err = (result.stderr or "") + (result.stdout or "")
        if any(hint in err.lower() for hint in LOCK_HINTS) and attempt < retries:
            time.sleep(1.5 * (attempt + 1))
            continue
        return result


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

    def schedule_commit(self):
        with self.lock:
            if self.timer is not None:
                self.timer.cancel()
            self.timer = threading.Timer(2.5, self.commit_and_push)
            self.timer.daemon = True
            self.timer.start()

    def commit_and_push(self):
        try:
            status = run_git(["status", "--porcelain"])
            if not status.stdout.strip():
                return

            add = run_git(["add", "-A"])
            if add.returncode != 0:
                print(add.stderr.strip() or add.stdout.strip())
                return

            commit = run_git(["commit", "-m", f"auto-commit {time.strftime('%Y-%m-%d %H:%M:%S')}"])
            if commit.returncode != 0:
                if "nothing to commit" in (commit.stderr or "").lower():
                    return
                print(commit.stderr.strip() or commit.stdout.strip())
                return

            push = run_git(["push", "origin", "HEAD"])
            if push.returncode != 0:
                print(push.stderr.strip() or push.stdout.strip() or "Push failed.")
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


if __name__ == "__main__":
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
