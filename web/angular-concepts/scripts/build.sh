#!/bin/bash

PROJECT_NAME="GOS Angular Concepts Example"

CMAKE=cmake

die() {
  printf '%s\n' "$1" >&2
  exit 1
}

show_help() {
cat << EOF
Usage: ${0##*/} [-h] [-nc]
Build the ${PROJECT_NAME}

     -h --help       display this help and exit
     -v              verbose mode. Can be used multiple times for increased
                     verbosity.
EOF
}

while :; do
  case $1 in
    -h|-\?|--help)
      show_help      # Display a usage synopsis.
      exit
      ;;
    -nc|--no-clean|--not--clean)
      echo "Not Clean detected"
      NOT_CLEAN=NOT_CLEAN
      ;;
    -nb|--no-build|--not-build)
      NOT_BUILD=NOT_BUILD
      ;;
    -nd|--no_doc|--not-doc|--no_docs|--not-docs)
      BUILD_DOCS=OFF
      ;;
    -n|--build-number)
      shift
      BUILD_NUMBER=$1
      ;;
    -b|--base-href)
      shift
      BASE_HREF=$1
      ;;
    --)              # End of all options.
      shift
      break
      ;;
    -?*)
      printf 'WARN: Unknown option (ignored): %s\n' "$1" >&2
      ;;
    *)               # Default case: No more options, so break out of the loop.
      break
  esac
  shift
done

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
echo "SOURCE is '$SOURCE'"
RDIR="$( dirname "$SOURCE" )"
DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )"
if [ "$DIR" != "$RDIR" ]; then
  echo "DIR '$RDIR' resolves to '$DIR'"
fi
echo "DIR is '$DIR'"

# Silent pushd and popd
silent_pushd () {
    command pushd "$@" > /dev/null
}
silent_popd () {
    command popd "$@" > /dev/null
}

#ROOT_DIR=`readlink -f "$DIR/.."`
ROOT_DIR=`realpath "$DIR/.."`

# Fix spaces in folder name
ROOT_DIR=${ROOT_DIR//\ /\\\ }

echo "---------------------------------------------------------------------------"
echo "Build script for the ${PROJECT_NAME}"
echo "${PROJECT_NAME} root directory is defined as ${ROOT_DIR}"

echo "Entering ${ROOT_DIR}"
silent_pushd ${ROOT_DIR}

echo "*** Build Angular Web"
if [ -z "$BASE_HREF" ]
then
  NG_BUILD_CMD="ng build --prod"
else
  NG_BUILD_CMD="ng build --prod --base-href="'"'"${BASE_HREF}"'"'
fi
echo "${NG_BUILD_CMD}"
${NG_BUILD_CMD}

echo "Leaving ${ROOT_DIR}"
silent_popd

echo "---------------------------------------------------------------------------"
