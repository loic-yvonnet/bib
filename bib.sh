#!/bin/bash

./tools/shells/check_docker.sh
if [ $? != 0 ]
then
	exit 1
fi

./tools/shells/run.sh $*