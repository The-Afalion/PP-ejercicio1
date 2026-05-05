/**
 * @brief It tests character module
 *
 * @file character_test.c
 * @author Rodrigo
 * @version 0.0
 * @date 17-03-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "character_test.h"
#include "test.h"

/** Numero maximo de pruebas disponibles en este modulo. */
#define MAX_TESTS 36

/**
 * @brief Funcion principal de las pruebas del modulo Character.
 *
 * Ejecuta todas las pruebas si no se recibe argumento, o una prueba concreta si
 * se indica su numero.
 *
 * @author Rodrigo
 * @param argc Numero de argumentos de entrada.
 * @param argv Argumentos de entrada.
 * @return 0 si la ejecucion termina correctamente.
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Character:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_character_create();
  if (all || test == 2) test2_character_create();
  if (all || test == 3) test1_character_destroy();
  if (all || test == 4) test2_character_destroy();
  if (all || test == 5) test1_character_get_id();
  if (all || test == 6) test2_character_get_id();
  if (all || test == 7) test1_character_get_name();
  if (all || test == 8) test2_character_get_name();
  if (all || test == 9) test1_character_set_name();
  if (all || test == 10) test2_character_set_name();
  if (all || test == 11) test1_character_get_gdesc();
  if (all || test == 12) test2_character_get_gdesc();
  if (all || test == 13) test1_character_set_gdesc();
  if (all || test == 14) test2_character_set_gdesc();
  if (all || test == 15) test1_character_get_health();
  if (all || test == 16) test2_character_get_health();
  if (all || test == 17) test1_character_set_health();
  if (all || test == 18) test2_character_set_health();
  if (all || test == 19) test1_character_get_friendly();
  if (all || test == 20) test2_character_get_friendly();
  if (all || test == 21) test1_character_set_friendly();
  if (all || test == 22) test2_character_set_friendly();
  if (all || test == 23) test1_character_get_message();
  if (all || test == 24) test2_character_get_message();
  if (all || test == 25) test1_character_set_message();
  if (all || test == 26) test2_character_set_message();
  if (all || test == 27) test1_character_get_following();
  if (all || test == 28) test2_character_get_following();
  if (all || test == 29) test1_character_set_following();
  if (all || test == 30) test2_character_set_following();
  if (all || test == 31) test1_character_print();
  if (all || test == 32) test2_character_print();
  if (all || test == 33) test1_character_set_money();
  if (all || test == 34) test2_character_set_money();
  if (all || test == 35) test1_character_get_money();
  if (all || test == 36) test2_character_get_money();


  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/**
 * @brief Ejecuta la prueba test1_character_create.
 * @author Rodrigo
 */
void test1_character_create() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(c != NULL);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_create.
 * @author Rodrigo
 */
void test2_character_create() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_get_id(c) == 1);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test1_character_destroy.
 * @author Rodrigo
 */
void test1_character_destroy() {
    Character *c = character_create(1);
    character_destroy(c);
    PRINT_TEST_RESULT(1);
}

/**
 * @brief Ejecuta la prueba test2_character_destroy.
 * @author Rodrigo
 */
void test2_character_destroy() {
    character_destroy(NULL);
    PRINT_TEST_RESULT(1);
}


/**
 * @brief Ejecuta la prueba test1_character_get_id.
 * @author Rodrigo
 */
void test1_character_get_id() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_get_id(c) == 1);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_get_id.
 * @author Rodrigo
 */
void test2_character_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

/**
 * @brief Ejecuta la prueba test1_character_get_name.
 * @author Rodrigo
 */
void test1_character_get_name() {
  Character *c;
  c = character_create(1);
  character_set_name(c, "test");
  PRINT_TEST_RESULT(strcmp(character_get_name(c), "test") == 0);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_get_name.
 * @author Rodrigo
 */
void test2_character_get_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_character_set_name.
 * @author Rodrigo
 */
void test1_character_set_name() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_name(c, "test") == OK);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_set_name.
 * @author Rodrigo
 */
void test2_character_set_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_name(c, "test") == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_character_get_gdesc.
 * @author Rodrigo
 */
void test1_character_get_gdesc() {
  Character *c;
  c = character_create(1);
  character_set_gdesc(c, "gdesc");
  PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), "gdesc") == 0);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_get_gdesc.
 * @author Rodrigo
 */
void test2_character_get_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_character_set_gdesc.
 * @author Rodrigo
 */
void test1_character_set_gdesc() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_gdesc(c, "gdesc") == OK);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_set_gdesc.
 * @author Rodrigo
 */
void test2_character_set_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_gdesc(c, "gdesc") == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_character_get_health.
 * @author Rodrigo
 */
void test1_character_get_health() {
  Character *c;
  c = character_create(1);
  character_set_health(c, 10);
  PRINT_TEST_RESULT(character_get_health(c) == 10);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_get_health.
 * @author Rodrigo
 */
void test2_character_get_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_health(c) == 0);
}

/**
 * @brief Ejecuta la prueba test1_character_set_health.
 * @author Rodrigo
 */
void test1_character_set_health() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_health(c, 10) == OK);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_set_health.
 * @author Rodrigo
 */
void test2_character_set_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_health(c, 10) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_character_get_friendly.
 * @author Rodrigo
 */
void test1_character_get_friendly() {
  Character *c;
  c = character_create(1);
  character_set_friendly(c, 1);
  PRINT_TEST_RESULT(character_get_friendly(c) == 1);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_get_friendly.
 * @author Rodrigo
 */
void test2_character_get_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_friendly(c) == 0);
}

/**
 * @brief Ejecuta la prueba test1_character_set_friendly.
 * @author Rodrigo
 */
void test1_character_set_friendly() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_friendly(c, 1) == OK);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_set_friendly.
 * @author Rodrigo
 */
void test2_character_set_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_friendly(c, 1) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_character_get_message.
 * @author Rodrigo
 */
void test1_character_get_message() {
  Character *c;
  c = character_create(1);
  character_set_message(c, "message");
  PRINT_TEST_RESULT(strcmp(character_get_message(c), "message") == 0);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_get_message.
 * @author Rodrigo
 */
void test2_character_get_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_message(c) == NULL);
}
/**
 * @brief Ejecuta la prueba test1_character_set_message.
 * @author Rodrigo
 */
void test1_character_set_message() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_message(c, "message") == OK);
  character_destroy(c);
}
/**
 * @brief Ejecuta la prueba test2_character_set_message.
 * @author Rodrigo
 */
void test2_character_set_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_message(c, "message") == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_character_get_following.
 * @author Rodrigo
 */
void test1_character_get_following() {
  Character *c;
  c = character_create(1);
  character_set_following(c, 7);
  PRINT_TEST_RESULT(character_get_following(c) == 7);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_get_following.
 * @author Rodrigo
 */
void test2_character_get_following() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_following(c) == NO_ID);
}

/**
 * @brief Ejecuta la prueba test1_character_set_following.
 * @author Rodrigo
 */
void test1_character_set_following() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_following(c, 7) == OK);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_set_following.
 * @author Rodrigo
 */
void test2_character_set_following() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_following(c, 7) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_character_print.
 * @author Rodrigo
 */
void test1_character_print() {
  Character *c;
  c = character_create(1);
  character_print(c);
  PRINT_TEST_RESULT(1);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_print.
 * @author Rodrigo
 */
void test2_character_print() {
  character_print(NULL);
  PRINT_TEST_RESULT(1);
}

/**
 * @brief Ejecuta la prueba test1_character_set_money.
 * @author Rodrigo
 */
void test1_character_set_money() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_money(c, 10) == OK);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_set_money.
 * @author Rodrigo
 */
void test2_character_set_money() {
  PRINT_TEST_RESULT(character_set_money(NULL, 10) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_character_get_money.
 * @author Rodrigo
 */
void test1_character_get_money() {
  Character *c;
  c = character_create(1);
  character_set_money(c, 10);
  PRINT_TEST_RESULT(character_get_money(c) == 10);
  character_destroy(c);
}

/**
 * @brief Ejecuta la prueba test2_character_get_money.
 * @author Rodrigo
 */
void test2_character_get_money() {
  PRINT_TEST_RESULT(character_get_money(NULL) == -1);
}
