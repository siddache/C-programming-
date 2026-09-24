#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

if [ -f ".venv/bin/activate" ]; then
  . .venv/bin/activate
fi

if command -v python3 >/dev/null 2>&1; then
  exec python3 auto_push.py
elif command -v python >/dev/null 2>&1; then
  exec python auto_push.py
else
  echo "Python is not installed or not in PATH."
  exit 1
fi
