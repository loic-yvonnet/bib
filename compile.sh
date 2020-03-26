#!/bin/bash

./tools/shells/check_docker.sh
if [ $? != 0 ]
then
	exit 1
fi

echo CMake configuration and generation
./tools/shells/gen_cmake.sh

echo Compilation
./tools/shells/compile.sh