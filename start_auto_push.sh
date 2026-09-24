#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

if [ -x ".venv/bin/python" ]; then
  exec .venv/bin/python auto_push.py
elif [ -f ".venv/Scripts/python.exe" ]; then
  # Supports launching a Windows-created virtual environment from Git Bash.
  exec .venv/Scripts/python.exe auto_push.py
elif command -v python3 >/dev/null 2>&1; then
  exec python3 auto_push.py
elif command -v python >/dev/null 2>&1; then
  exec python auto_push.py
else
  echo "No usable Python was found. Create a virtual environment and install requirements:"
  echo "  python -m venv .venv && .venv/bin/python -m pip install -r requirements.txt"
  exit 1
fi
