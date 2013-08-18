#!/bin/bash

set -e

export WORKDIR=$(cd $(dirname "$0"); pwd)
cd $WORKDIR

if [ ! -d local-build ]; then
	mkdir local-build
fi

cd local-build
cmake ..
make
