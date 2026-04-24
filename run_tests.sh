#!/usr/bin/env bash

set -euo pipefail

if [[ $# -lt 1 || $# -gt 2 ]]; then
  echo "Uso: $0 <0|1> [nombre_test_sin_extension]"
  exit 1
fi

mode="$1"
selected_test="${2:-}"

if [[ "$mode" != "0" && "$mode" != "1" ]]; then
  echo "El primer argumento debe ser 0 o 1."
  exit 1
fi

run_test() {
  local test_name="$1"

  if [[ "$mode" == "0" ]]; then
    "./$test_name"
  else
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes "./$test_name"
  fi
}

if [[ "$mode" == "1" ]] && ! command -v valgrind >/dev/null 2>&1; then
  echo "Valgrind no está instalado."
  exit 1
fi

if [[ -n "$selected_test" ]]; then
  if [[ ! -f "src/${selected_test}.c" ]]; then
    echo "No existe el fichero de pruebas src/${selected_test}.c."
    exit 1
  fi

  make "$selected_test"
  run_test "$selected_test"
  exit 0
fi

make tests

shopt -s nullglob
test_files=(src/*_test.c)
shopt -u nullglob

if [[ ${#test_files[@]} -eq 0 ]]; then
  echo "No se han encontrado ficheros *_test.c en src."
  exit 1
fi

for test_file in "${test_files[@]}"; do
  test_name="$(basename "$test_file" .c)"
  run_test "$test_name"
done
