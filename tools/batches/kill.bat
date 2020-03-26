@echo off

:: Initialize environment variables
set current_directory=%~dp0
call %current_directory%\init_variables.bat

:: Execute Process Kill
call docker exec -it %container_alias% pkill %target_program_name%
