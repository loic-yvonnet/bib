@echo off

:: Directories
set shells_directory=%~dp0
set workspace_directory=%shells_directory%\..\..
set src_directory=%workspace_directory%\src
set build_directory=%workspace_directory%\build
set release_directory=%workspace_directory%\release
set tools_directory=%workspace_directory%\tools
set docker_directory=%tools_directory%\docker
set docker_bib_core_dev_directory=%docker_directory%\bib-core-dev
set docker_bib_dev_directory=%docker_directory%\bib-dev

:: Docker
set docker_core_image=yvo-solutions\bib-core-dev
set docker_core_image_version=%docker_core_image%:latest
set docker_image=yvo-solutions\bib-dev
set docker_image_version=%docker_image%:latest
set container_alias=devenv
set docker_compose_path=%docker_directory%\compose.yml
set docker_workspace_directory=/home/develop/dev
set docker_build_directory=%docker_workspace_directory%/build
set docker_release_directory=%docker_workspace_directory%/release
set docker_vcpkg_dependencies=/vcpkg/scripts/buildsystems/vcpkg.cmake

:: Others
set target_program_name=bib
set target_program_path=%build_directory%\bin\%target_program_name%
set docker_target_program_path=%docker_build_directory%/bin/%target_program_name%
set docker_test_suite=%docker_build_directory%/bin/tests
