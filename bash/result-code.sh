#!/bin/bash

# Exit and Exit Status
# https://tldp.org/LDP/abs/html/exit-status.html

# Introduction to if
# https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_07_01.html

# Bash If Statement Examples ( If then fi, If then else fi, If elif else fi, Nested if )
# https://www.thegeekstuff.com/2010/06/bash-if-statement-examples/

# Resolve the Current Script Directory
SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  TARGET="$(readlink "$SOURCE")"
  if [[ $TARGET == /* ]]; then
    echo "SOURCE '$SOURCE' is an absolute symlink to '$TARGET'"
    SOURCE="$TARGET"
  else
    DIR="$( dirname "$SOURCE" )"
    echo "SOURCE '$SOURCE' is a relative symlink to '$TARGET' (relative to '$DIR')"
    SOURCE="$DIR/$TARGET" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
  fi
done
RDIR="$( dirname "$SOURCE" )"
DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )"
if [ "$DIR" != "$RDIR" ]; then
  echo "DIR '$RDIR' resolves to '$DIR'"
fi

# Absolute Path
ROOT_DIR=`realpath "$DIR"`

FILE_A=${ROOT_DIR}/absolute-path.sh
FILE_B=${ROOT_DIR}/result-code.sh

DIFF_CMD="diff ${FILE_A} ${FILE_B}"
echo "${DIFF_CMD}"
${DIFF_CMD}
if [ $? -eq 0 ]
  then
    echo "The diff command was successful"
  else
    echo "The diff command failed with result code $?"
    exit $?
fi

DIFF_CMD="diff ${FILE_A} ${FILE_B}"
echo "${DIFF_CMD}"
${DIFF_CMD}
if [ $? -ne 0 ] ; then exit $? ; fi
