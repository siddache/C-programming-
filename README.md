# C programming practice

This repository contains small C programming exercises. `auto_push.py` is an
optional local helper that debounces edits, creates an automatic Git commit,
rebases it onto `origin/<current-branch>`, and pushes it.

## Set up the auto-push helper

Python 3.9+ and Git must be installed and available on your PATH. Create the
environment once from the repository root:

```powershell
py -m venv .venv
.\.venv\Scripts\python.exe -m pip install -r requirements.txt
.\start_auto_push.ps1
```

If the virtual environment reports that its base Python cannot run, install or
repair Python first, remove only `.venv`, then repeat the three setup commands.

On macOS/Linux, use:

```bash
python3 -m venv .venv
.venv/bin/python -m pip install -r requirements.txt
./start_auto_push.sh
```

The helper has a 3-second debounce window and completes a final sync when
stopped with Ctrl+C. It deliberately pauses instead of guessing when there are
manually staged changes, a merge/rebase is underway, a sensitive-looking file
changes, the current commit is detached, or Git reports an error.

To run a project check before each automatic commit, set a command in the
environment before starting it. For example:

```powershell
$env:AUTO_PUSH_TEST_COMMAND = 'gcc -Wall -Wextra C-programminig\Practice\c1.c -o $env:TEMP\c1.exe'
.\start_auto_push.ps1
```

`auto_push.log` records the helper's actions locally and is ignored by Git.
