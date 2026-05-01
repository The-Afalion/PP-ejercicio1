/**
 * @brief It tests character module
 *
 * @file character_test.c
 * @author RAHER
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

#define MAX_TESTS 30

/**
 * @brief Main function for CHARACTER unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
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


  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_character_create() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(c != NULL);
  character_destroy(c);
}

void test2_character_create() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_get_id(c) == 1);
  character_destroy(c);
}

void test1_character_destroy() {
    Character *c = character_create(1);
    character_destroy(c);
    PRINT_TEST_RESULT(1);
}

void test2_character_destroy() {
    character_destroy(NULL);
    PRINT_TEST_RESULT(1);
}


void test1_character_get_id() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_get_id(c) == 1);
  character_destroy(c);
}

void test2_character_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

void test1_character_get_name() {
  Character *c;
  c = character_create(1);
  character_set_name(c, "test");
  PRINT_TEST_RESULT(strcmp(character_get_name(c), "test") == 0);
  character_destroy(c);
}

void test2_character_get_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test1_character_set_name() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_name(c, "test") == OK);
  character_destroy(c);
}

void test2_character_set_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_name(c, "test") == ERROR);
}

void test1_character_get_gdesc() {
  Character *c;
  c = character_create(1);
  character_set_gdesc(c, "gdesc");
  PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), "gdesc") == 0);
  character_destroy(c);
}

void test2_character_get_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}

void test1_character_set_gdesc() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_gdesc(c, "gdesc") == OK);
  character_destroy(c);
}

void test2_character_set_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_gdesc(c, "gdesc") == ERROR);
}

void test1_character_get_health() {
  Character *c;
  c = character_create(1);
  character_set_health(c, 10);
  PRINT_TEST_RESULT(character_get_health(c) == 10);
  character_destroy(c);
}

void test2_character_get_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_health(c) == 0);
}

void test1_character_set_health() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_health(c, 10) == OK);
  character_destroy(c);
}

void test2_character_set_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_health(c, 10) == ERROR);
}

void test1_character_get_friendly() {
  Character *c;
  c = character_create(1);
  character_set_friendly(c, 1);
  PRINT_TEST_RESULT(character_get_friendly(c) == 1);
  character_destroy(c);
}

void test2_character_get_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_friendly(c) == 0);
}

void test1_character_set_friendly() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_friendly(c, 1) == OK);
  character_destroy(c);
}

void test2_character_set_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_friendly(c, 1) == ERROR);
}

void test1_character_get_message() {
  Character *c;
  c = character_create(1);
  character_set_message(c, "message");
  PRINT_TEST_RESULT(strcmp(character_get_message(c), "message") == 0);
  character_destroy(c);
}

void test2_character_get_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_message(c) == NULL);
}
void test1_character_set_message() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_message(c, "message") == OK);
  character_destroy(c);
}
void test2_character_set_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_message(c, "message") == ERROR);
}

void test1_character_get_following() {
  Character *c;
  c = character_create(1);
  character_set_following(c, 7);
  PRINT_TEST_RESULT(character_get_following(c) == 7);
  character_destroy(c);
}

void test2_character_get_following() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_following(c) == NO_ID);
}

void test1_character_set_following() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_following(c, 7) == OK);
  character_destroy(c);
}

void test2_character_set_following() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_following(c, 7) == ERROR);
}
