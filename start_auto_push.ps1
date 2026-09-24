[CmdletBinding()]
param()

$ErrorActionPreference = 'Stop'
$RepoDir = $PSScriptRoot
$VenvPython = Join-Path $RepoDir '.venv\Scripts\python.exe'

if (Test-Path -LiteralPath $VenvPython) {
    $Python = $VenvPython
    $PythonArguments = @()
}
else {
    $PythonCommand = Get-Command python -ErrorAction SilentlyContinue
    if ($null -ne $PythonCommand) {
        $Python = $PythonCommand.Source
        $PythonArguments = @()
    }
    else {
        $PythonLauncher = Get-Command py -ErrorAction SilentlyContinue
        if ($null -eq $PythonLauncher) {
            Write-Error "Python was not found. Install Python, then run: py -m venv .venv; .\.venv\Scripts\python.exe -m pip install -r requirements.txt"
        }
        $Python = $PythonLauncher.Source
        $PythonArguments = @('-3')
    }
}

& $Python @PythonArguments -c "import sys" 2>$null
if ($LASTEXITCODE -ne 0) {
    Write-Error "Python at '$Python' could not run. Repair or reinstall Python, recreate .venv, then install requirements.txt."
}

& $Python @PythonArguments -c "import watchdog" 2>$null
if ($LASTEXITCODE -ne 0) {
    Write-Error "watchdog is not installed for $Python. Run: & '$Python' -m pip install -r requirements.txt"
}

Set-Location -LiteralPath $RepoDir
& $Python @PythonArguments (Join-Path $RepoDir 'auto_push.py')
exit $LASTEXITCODE
