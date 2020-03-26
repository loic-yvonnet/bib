@echo off

:: Initialize environment variables
set current_directory=%~dp0
call %current_directory%\init_variables.bat

:: Remove all docker containers
call docker ps --all --quiet > tmp.docker.ps.log
for /f %%A in (tmp.docker.ps.log) do (
    call docker rm %%A
)
del tmp.docker.ps.log

:: Remove the docker images
call docker rmi %docker_image_version%
call docker rmi %docker_core_image_version%
