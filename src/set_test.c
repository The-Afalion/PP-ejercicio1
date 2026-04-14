/**
 * @brief It tests set module
 *
 * @file set_test.c
 * @author RAHER
 * @version 0.0
 * @date 17-03-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 16

/**
 * @brief Main function for SET unit tests.
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
    printf("Running all test for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_set_create();
  if (all || test == 2) test2_set_create();
  if (all || test == 3) test1_set_add();
  if (all || test == 4) test2_set_add();
  if (all || test == 5) test1_set_del();
  if (all || test == 6) test2_set_del();
  if (all || test == 7) test1_set_find();
  if (all || test == 8) test2_set_find();
  if (all || test == 9) test1_set_get_id();
  if (all || test == 10) test2_set_get_id();
  if (all || test == 11) test1_set_get_numberid();
  if (all || test == 12) test2_set_get_numberid();
  if (all || test == 13) test1_set_get_ids();
  if (all || test == 14) test2_set_get_ids();
  if (all || test == 15) test1_set_destroy();
  if (all || test == 16) test2_set_destroy();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_set_create() {
  Set *s;
  s = set_create(1);
  PRINT_TEST_RESULT(s != NULL);
  set_destroy(s);
}

void test2_set_create() {
  Set *s;
  s = set_create(1);
  PRINT_TEST_RESULT(set_get_numberid(s) == 0);
  set_destroy(s);
}

void test1_set_add() {
  Set *s;
  s = set_create(1);
  PRINT_TEST_RESULT(set_add(s, 10) == OK);
  set_destroy(s);
}

void test2_set_add() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_add(s, 10) == ERROR);
}

void test1_set_del() {
  Set *s;
  s = set_create(1);
  set_add(s, 10);
  PRINT_TEST_RESULT(set_del(s, 10) == OK);
  set_destroy(s);
}

void test2_set_del() {
  Set *s;
  s = set_create(1);
  PRINT_TEST_RESULT(set_del(s, 10) == ERROR);
  set_destroy(s);
}

void test1_set_find() {
  Set *s;
  s = set_create(1);
  set_add(s, 10);
  PRINT_TEST_RESULT(set_find(s, 10) == OK);
  set_destroy(s);
}

void test2_set_find() {
  Set *s;
  s = set_create(1);
  PRINT_TEST_RESULT(set_find(s, 10) == ERROR);
  set_destroy(s);
}

void test1_set_get_id() {
  Set *s;
  s = set_create(1);
  set_add(s, 10);
  PRINT_TEST_RESULT(set_get_id(s, 0) == 10);
  set_destroy(s);
}

void test2_set_get_id() {
  Set *s;
  s = set_create(1);
  PRINT_TEST_RESULT(set_get_id(s, 0) == NO_ID);
  set_destroy(s);
}

void test1_set_get_numberid() {
  Set *s;
  s = set_create(1);
  set_add(s, 10);
  PRINT_TEST_RESULT(set_get_numberid(s) == 1);
  set_destroy(s);
}

void test2_set_get_numberid() {
  Set *s;
  s = set_create(1);
  PRINT_TEST_RESULT(set_get_numberid(s) == 0);
  set_destroy(s);
}

void test1_set_get_ids() {
  Set *s;
  s = set_create(1);
  set_add(s, 10);
  PRINT_TEST_RESULT(set_get_ids(s)[0] == 10);
  set_destroy(s);
}

void test2_set_get_ids() {
  Set *s;
  s = set_create(1);
  PRINT_TEST_RESULT(set_get_ids(s) == NULL);
  set_destroy(s);
}

void test1_set_destroy() {
  Set *s;
  s = set_create(1);
  PRINT_TEST_RESULT(set_destroy(s) == OK);
}

void test2_set_destroy() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_destroy(s) == ERROR);
}
