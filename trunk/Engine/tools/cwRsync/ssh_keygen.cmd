@echo off

set CWRSYNCHOME=%~dp0
set CYGWIN=nontsec
set HOME=%HOMEDRIVE%%HOMEPATH%
set CWOLDPATH=%PATH%
set PATH=%CWRSYNCHOME%\BIN;%PATH%

ssh-keygen.exe -t rsa