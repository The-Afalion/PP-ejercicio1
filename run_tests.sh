#!/usr/bin/env bash

mode="$1"
test_elegido="${2:-}"

if [[ -n "$test_elegido" ]]; then
  make "$test_elegido"

  if [[ "$mode" == "0" ]]; then
    "./build/$test_elegido"
  else
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes "./build/$test_elegido"
  fi
else
  make tests

  for binary in build/*_test; do
    if [[ "$mode" == "0" ]]; then
      "./$binary"
    else
      valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes "./$binary"
    fi
  done
fi