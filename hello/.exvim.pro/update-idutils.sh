#!/bin/bash
export DEST="./.exvim.pro"
export TOOLS="/root/exvim//vimfiles/tools/"
export TMP="${DEST}/_ID"
export TARGET="${DEST}/ID"
sh ${TOOLS}/shell/bash/update-idutils.sh
