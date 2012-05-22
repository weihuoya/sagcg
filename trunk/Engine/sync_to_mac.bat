@echo off
setlocal enabledelayedexpansion

call sync_config.bat

set ARGS=--update --delete
if "%1"=="-f" (
	set ARGS=
)

rsync -vaSP -e ssh --exclude-from=sync_exclude.txt --delete --chmod=ugo=rwX %ARGS% %LOCAL_PATH% %HOST%:%REMOTE_PATH%/

echo.
echo.
pause