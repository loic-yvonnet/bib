@echo off

:: Initialize environment variables
set current_directory=%~dp0
%current_directory%\init_variables.bat

:: Build the Dockerfile
call docker build -t %docker_core_image_version% %docker_bib_core_dev_directory%
call docker build -t %docker_image_version% %docker_bib_dev_directory%
