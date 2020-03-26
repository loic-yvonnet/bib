@echo off

:: Initialize environment variables
set current_directory=%~dp0
%current_directory%\init_variables.bat

:: Clean up
del /s /q %build_directory%\*
rmdir /s /q %build_directory%
