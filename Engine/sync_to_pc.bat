@echo off
setlocal enabledelayedexpansion

call sync_config.bat

rsync -vaSP --no-g -e ssh --exclude-from=sync_exclude.txt --update --delete %HOST%:%REMOTE_PATH%/ %LOCAL_PATH%

echo.
echo.
pause