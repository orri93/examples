#!/bin/bash

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null && pwd )"
pushd () {
    command pushd "$@" > /dev/null
}
popd () {
    command popd "$@" > /dev/null
}

EXAMPLES_ROOT_DIR=`readlink -f "${DIR}/.."`


echo ""
echo "================================================================================"
echo " Building the pi4j example projects"
echo "================================================================================"
echo ""
echo "Current location is ${DIR}"
echo "Examples location is ${EXAMPLES_ROOT_DIR}"
echo ""

echo "--------------------------------------------------------------------------------"
echo "Entering pi4j MCP3208 Example"
echo "--------------------------------------------------------------------------------"
pushd "${EXAMPLES_ROOT_DIR}/java/pi4j/mcp3208"
mvn clean
mvn install
mvn exec:java
popd
