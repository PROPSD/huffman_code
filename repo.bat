@echo off
set "repo_url=https://github.com/PROPSD/huffman_code.git"
set "main_script=huffman_gui.py"

set "target=google.com"
ping %target% -n 1 >nul
if errorlevel 1 (
    echo Internet connection not available.
    echo Please connect to the internet and try again.
    pause
    exit
)

where git >nul 2>nul
if errorlevel 1 (
    echo Git is not installed. Please install Git first.
    pause
    exit
)

echo Installing required Python modules...
pip install PyQt6 >nul
echo Modules installed.

git rev-parse --is-inside-work-tree >nul 2>nul
if errorlevel 1 (
    git init
    git remote add origin %repo_url%
)

git add .
git commit -m "Auto-update"
git pull origin main --rebase
git push origin main

python %main_script%
exit
