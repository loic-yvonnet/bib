@echo off

:: Initialize environment variables
set current_directory=%~dp0
call %current_directory%\init_variables.bat

:: Make sure the build directory exists
mkdir %release_directory%

:: Execute CMake
call docker exec -it -w %docker_release_directory% %container_alias% \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=%docker_vcpkg_dependencies% ..

:: Compile
call docker exec -it -w %docker_release_directory% %container_alias% make -j8
