@echo off

call .\tools\batches\check_docker.bat
if %errorlevel% neq 0 (
	exit /b 1
)

echo CMake configuration and generation
call .\tools\batches\gen_cmake.bat

echo Compilation
call .\tools\batches\compile.bat