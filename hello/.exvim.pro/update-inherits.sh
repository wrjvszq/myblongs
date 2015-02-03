#!/bin/bash
export DEST="./.exvim.pro"
export TOOLS="/root/exvim//vimfiles/tools/"
export TMP="${DEST}/_inherits"
export TARGET="${DEST}/inherits"
sh ${TOOLS}/shell/bash/update-inherits.sh
