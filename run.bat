@echo off

set exe_path="debugger\remedybg.exe"

if not exist %exe_path% (
    echo Error: Executable file not found!
    pause
    exit /b
)

REM Run with rdb so we get debug info!
start "" %exe_path% -g -q debugger\f2c.rdbg