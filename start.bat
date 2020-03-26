@echo off

setlocal enabledelayedexpansion

call docker --version > tmp.log 2>&1
if %errorlevel% equ 1 (
	echo Please install Docker and Docker Compose.
    del tmp.log
	exit /b 1
)

call docker images -q yvo-solutions/bib-dev:latest > tmp.log
set docker_image_exist=NO
for /f %%A in (tmp.log) do (
    set docker_image_exist=YES
)
del tmp.log

if "%docker_image_exist%" == "NO" (
    call .\tools\batches\build_docker_image.bat
    call .\tools\batches\start_container.bat
) else (
    call .\tools\batches\stop_container.bat
    call .\tools\batches\start_container.bat
)

endlocal