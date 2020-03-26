@echo off

call .\tools\batches\check_docker.bat
if %errorlevel% neq 0 (
	exit /b 1
)

call .\tools\batches\run.bat %*