@echo off

set folder_name=build

if exist %folder_name% (
    REM If the folder exists, delete it
    rmdir /s /q %folder_name%
)