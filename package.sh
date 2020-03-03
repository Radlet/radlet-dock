#!/bin/bash
if [[ $# -eq 0 || $1 == "--help" ]]; then
  echo "Usage ./run_build_tests.sh -<option> --[architecture]"
  echo "      <option>: b - build"
  echo "                d - deploy"
  echo "                ud - update deployment image"
  echo "                mt - manual testing"
  echo "                e - create environment image"
  echo "                d - deploy"
  echo "                t - unittest"
  echo "                a - all"
  echo "                      "
  echo "      <architecture>: arm - ARM 32bit"
elif [ "$2" == "--arm" ]; then
  if [[ "$1" == "-b" || $1 == "--build" ]]; then
    docker build -t radlet_dock.dev:arm -f ./Docker/arm/dev.Dockerfile .

  elif [[ "$1" == "-ud" || $1 == "--update-deploy" ]]; then
    docker build -t radlet/radlet_dock:arm -f ./Docker/arm/deploy.Dockerfile .
    docker push radlet/radlet_dock:arm

  elif [[ "$1" == "-d" || $1 == "--deploy" ]]; then
    mkdir -p hub_sensor_data
    docker-compose -f ./Docker/arm/deploy.docker-compose.yml up

  elif [[ "$1" == "-t" || $1 == "--unit-test" ]]; then
    echo "Unit tests to be added soon."

  elif [[ "$1" == "-mt" || $1 == "--manual-test" ]]; then
    mkdir -p hub_sensor_data
    docker-compose -f ./Docker/arm/dev.docker-compose.yml run radlet_dock

  elif [[ "$1" == "-e" || $1 == "--env" ]]; then
    docker build -t radlet/radlet_dock.env:arm -f ./Docker/arm/env.Dockerfile .

  elif [[ "$1" == "-a" || $1 == "-all" ]]; then
    docker build -t radlet_dock.test -f ./Docker/arm/dev.Dockerfile .

  else
    echo "Invalid command. Try ./run_build_test.sh --help"
  fi
else
  if [[ "$1" == "-b" || $1 == "--build" ]]; then
    docker build -t radlet_dock.dev:x64 -f ./Docker/x64/dev.Dockerfile .

  elif [[ "$1" == "-ud" || $1 == "--update-deploy" ]]; then
    docker build -t radlet/radlet_dock:x64 -f ./Docker/x64/deploy.Dockerfile .
    docker push radlet/radlet_dock:x64

  elif [[ "$1" == "-d" || $1 == "--deploy" ]]; then
    mkdir -p hub_sensor_data
    docker-compose -f ./Docker/x64/deploy.docker-compose.yml up

  elif [[ "$1" == "-t" || $1 == "--unit-test" ]]; then
    echo "Unit tests to be added soon."

  elif [[ "$1" == "-mt" || $1 == "--manual-test" ]]; then
    mkdir -p hub_sensor_data
    docker-compose -f ./Docker/x64/dev.docker-compose.yml run radlet_dock

  elif [[ "$1" == "-e" || $1 == "--env" ]]; then
    docker build -t radlet/radlet_dock.env:x64 -f ./Docker/x64/env.Dockerfile .

  elif [[ "$1" == "-a" || $1 == "-all" ]]; then
    docker build -t radlet_dock.test -f ./Docker/x64/dev.Dockerfile .

  else
    echo "Invalid command. Try ./run_build_test.sh --help"
  fi
fi
