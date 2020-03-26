@echo off

:: Initialize environment variables
set current_directory=%~dp0
call %current_directory%\init_variables.bat

:: Execute Make
call docker exec -it -w %docker_build_directory% %container_alias% %docker_test_suite%
