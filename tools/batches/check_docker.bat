@echo off

:: Check that docker is installed
call docker --version > tmp.log
if %errorlevel% neq 0 (
	echo Please install Docker and Docker Compose.
    del tmp.log
	exit /b 1
)

:: Check that the docker image exists
call docker images -q yvo-solutions/bib-dev:latest > tmp.log
set docker_image_exist=NO
for /f %%A in (tmp.log) do (
    set docker_image_exist=YES
)

if "%docker_image_exist%" == "NO" (
    echo The Docker image does not exist. Please run start.bat.
    del tmp.log
    exit /b 1
)

:: Check that the docker container is up and running
call docker ps --filter="name=devenv" -q > tmp.log
set docker_container_running=NO
for /f %%A in (tmp.log) do (
    set docker_container_running=YES
)

if "%docker_container_running%" == "NO" (
    echo The Docker container is not started. Please run start.bat.
    del tmp.log
    exit /b 1
)

del tmp.log