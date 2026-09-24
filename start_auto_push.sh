#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

if [ -f ".venv/bin/activate" ]; then
  . .venv/bin/activate
fi

if command -v python3 >/dev/null 2>&1; then
  PY_CMD=(python3 auto_push.py)
elif command -v python >/dev/null 2>&1; then
  PY_CMD=(python auto_push.py)
else
  echo "Python is not installed or not in PATH."
  exit 1
fi

if [ "${AUTO_PUSH_BACKGROUND:-0}" = "1" ]; then
  exec "${PY_CMD[@]}"
fi

if ! [ -t 0 ] || ! [ -t 1 ]; then
  nohup env AUTO_PUSH_BACKGROUND=1 "${PY_CMD[@]}" >> auto_push.log 2>&1 &
  echo "Auto-push started in background. Log file: $SCRIPT_DIR/auto_push.log"
  exit 0
fi

exec "${PY_CMD[@]}"
