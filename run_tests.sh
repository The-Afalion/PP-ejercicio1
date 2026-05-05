#!/usr/bin/env bash

if [ "$1" = "integration" ]; then
  make all || exit 1
  mkdir -p integration_tests/tmp

  for cmd_file in integration_tests/*.cmd; do
    test_name=$(basename "$cmd_file" .cmd)
    data_file="integration_tests/$test_name.dat"
    expected_file="integration_tests/$test_name.expected"
    log_file="integration_tests/tmp/$test_name.log"

    tr -d '\r' < "$cmd_file" | ./castle "$data_file" -l "$log_file" > /dev/null || exit 1
    diff -u "$expected_file" "$log_file" || exit 1
    echo "$test_name: OK"
  done

  exit 0
fi

if [ "$1" != "0" ] && [ "$1" != "1" ]; then
  echo "Uso: $0 <0|1> [nombre_test_sin_extension]"
  exit 1
fi

run_test() {
  if [ "$1" = "1" ]; then
    valgrind "./$2"
  else
    "./$2"
  fi
}

if [ -n "$2" ]; then
  make "$2" || exit 1
  run_test "$1" "$2"
  exit 0
fi

make tests || exit 1

for test_file in src/*_test.c; do
  test_name=$(basename "$test_file" .c)
  run_test "$1" "$test_name"
done
