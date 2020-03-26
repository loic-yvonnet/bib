@echo off

:: Initialize environment variables
set current_directory=%~dp0
call %current_directory%\init_variables.bat

:: Start gdb server and attach the target program
call docker exec -d %container_alias% gdbserver :2000 %docker_target_program_path%
