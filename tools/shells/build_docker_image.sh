#!/bin/bash

# Initialize environment variables
current_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
. ${current_directory}/init_variables.sh

# Build the Dockerfile
docker build -t ${docker_core_image_version} ${docker_bib_core_dev_directory}
docker build -t ${docker_image_version} ${docker_bib_dev_directory}
