#!/bin/bash
if [[ $# -eq 0 || $1 == "--help" ]]; then
  echo "Usage ./run_build_tests.sh -<option>"
  echo "      <option>: b - build"
  echo "               d - deploy"
  echo "               t - unittest"
  echo "               a - all"
elif [[ "$1" == "-b" || $1 == "--build" ]]; then
  docker build -t lattice_hub.test -f ./Docker/dev.Dockerfile .
elif [[ "$1" == "-d" || $1 == "--deploy" ]]; then
  docker build -t lattice_hub.test -f ./Docker/deploy.Dockerfile .
elif [[ "$1" == "-t" || $1 == "--unit-test" ]]; then
  echo "Unit tests to be added soon."
elif [[ "$1" == "-mt" || $1 == "--manual-test" ]]; then
  docker run -it --net=host lattice_hub.test
elif [[ "$1" == "-e" || $1 == "--env" ]]; then
  docker build -t humbled/lattice_hub.dev -f ./Docker/env.Dockerfile .
elif [[ "$1" == "-a" || $1 == "-all" ]]; then
  docker build -t lattice_hub.test -f ./Docker/dev.Dockerfile .
else
  echo "Invalid command. Try ./run_build_test.sh -help"
fi
