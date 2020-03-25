#!/bin/bash

# Directories
export shells_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
export workspace_directory=${shells_directory}/../..
export src_directory=${workspace_directory}/src
export build_directory=${workspace_directory}/build
export release_directory=${workspace_directory}/release
export tools_directory=${workspace_directory}/tools
export docker_directory=${tools_directory}/docker
export docker_bib_core_dev_directory=${docker_directory}/bib-core-dev
export docker_bib_dev_directory=${docker_directory}/bib-dev

# Docker
export docker_core_image=yvo-solutions/bib-core-dev
export docker_core_image_version=${docker_core_image}:latest
export docker_image=yvo-solutions/bib-dev
export docker_image_version=${docker_image}:latest
export container_alias=devenv
export docker_compose_path=${docker_directory}/compose.yml
export docker_workspace_directory=/home/develop/dev
export docker_build_directory=${docker_workspace_directory}/build
export docker_release_directory=${docker_workspace_directory}/release
export docker_vcpkg_dependencies=/vcpkg/scripts/buildsystems/vcpkg.cmake

# Others
export target_program_name=bib
export target_program_path=${build_directory}/bin/${target_program_name}
export docker_target_program_path=${docker_build_directory}/bin/${target_program_name}
