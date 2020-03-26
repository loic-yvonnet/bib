@echo off

:: Initialize environment variables
set current_directory=%~dp0
call %current_directory%\init_variables.bat

:: Start the container
call docker-compose -f %docker_compose_path% run --service-ports --name %container_alias% dev-image bash
