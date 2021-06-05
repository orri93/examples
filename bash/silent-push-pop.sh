#!/bin/bash

# Silent pushd and popd
silent_pushd () {
  command pushd "$@" > /dev/null
}
silent_popd () {
  command popd "$@" > /dev/null
}

TARGET_DIR="/usr"

echo "Entering ${TARGET_DIR}"
silent_pushd ${TARGET_DIR}

ls -l

echo "Leaving ${TARGET_DIR}"
silent_popd

ls -l