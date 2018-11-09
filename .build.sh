#!/bin/sh

pushd () {
    command pushd "$@" > /dev/null
}

popd () {
    command popd "$@" > /dev/null
}

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null && pwd )"

echo ""
echo "================================================================================"
echo "Building the example projects"
echo "================================================================================"
echo ""
echo "Current location is ${DIR}"
echo ""

echo "--------------------------------------------------------------------------------"
echo "Entering Camel Java SOAP Example"
echo "--------------------------------------------------------------------------------"
pushd "${DIR}/camel/camel-java-soap"
mvn install
popd

echo ""
echo "--------------------------------------------------------------------------------"
echo "Entering Camel Blue-Print Example"
echo "--------------------------------------------------------------------------------"
pushd "${DIR}/camel/camel-blueprint-project"
mvn install
popd

