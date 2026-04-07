/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Profesores Pprog
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "space.h"
#include "space_test.h"
#include "test.h"
#include "link.h"

#define MAX_TESTS 33

/** 
 * @brief Main function for SPACE unit tests. 
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
    printf("Running all test for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_space_create();
  if (all || test == 2) test2_space_create();
  if (all || test == 3) test1_space_destroy();
  if (all || test == 4) test2_space_destroy();
  if (all || test == 5) test1_space_set_name();
  if (all || test == 6) test2_space_set_name();
  if (all || test == 7) test3_space_set_name();
  if (all || test == 8) test1_space_get_id();
  if (all || test == 9) test2_space_get_id();
  if (all || test == 10) test1_space_get_name();
  if (all || test == 11) test2_space_get_name();
  if (all || test == 12) test1_space_add_object();
  if (all || test == 13) test2_space_add_object();
  if (all || test == 14) test1_space_get_objects();
  if (all || test == 15) test2_space_get_objects();
  if (all || test == 16) test1_space_get_number_of_objects();
  if (all || test == 17) test2_space_get_number_of_objects();
  if (all || test == 18) test1_space_remove_object();
  if (all || test == 19) test2_space_remove_object();
  if (all || test == 20) test1_space_contains_object();
  if (all || test == 21) test2_space_contains_object();
  if (all || test == 22) test1_space_set_character();
  if (all || test == 23) test2_space_set_character();
  if (all || test == 24) test1_space_get_character();
  if (all || test == 25) test2_space_get_character();
  if (all || test == 26) test1_space_set_discovered();
  if (all || test == 27) test2_space_set_discovered();
  if (all || test == 28) test1_space_get_discovered();
  if (all || test == 29) test2_space_get_discovered();
  if (all || test == 30) test1_space_set_gdesc();
  if (all || test == 31) test2_space_set_gdesc();
  if (all || test == 32) test1_space_get_gdesc();
  if (all || test == 33) test2_space_get_gdesc();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_space_create() {
  int result;
  Space *s;
  s = space_create(5);
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

void test2_space_create() {
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

void test1_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}

void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

void test3_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

void test1_space_get_name() {
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
  space_destroy(s);
}

void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

void test1_space_get_id() {
  Space *s;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
  space_destroy(s);
}

void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_add_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_add_object(s, 10) == OK);
    space_destroy(s);
}

void test2_space_add_object() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_add_object(s, 10) == ERROR);
}

void test1_space_get_objects() {
    Space *s;
    s = space_create(1);
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_get_objects(s)[0] == 10);
    space_destroy(s);
}

void test2_space_get_objects() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_get_objects(s) == NULL);
    space_destroy(s);
}

void test1_space_get_number_of_objects() {
    Space *s;
    s = space_create(1);
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_get_number_of_objects(s) == 1);
    space_destroy(s);
}

void test2_space_get_number_of_objects() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_get_number_of_objects(s) == 0);
    space_destroy(s);
}

void test1_space_remove_object() {
    Space *s;
    s = space_create(1);
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_remove_object(s, 10) == OK);
    space_destroy(s);
}

void test2_space_remove_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_remove_object(s, 10) == ERROR);
    space_destroy(s);
}

void test1_space_contains_object() {
    Space *s;
    s = space_create(1);
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_contains_object(s, 10) == OK);
    space_destroy(s);
}

void test2_space_contains_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_contains_object(s, 10) == ERROR);
    space_destroy(s);
}

void test1_space_set_character() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_set_character(s, 20) == OK);
    space_destroy(s);
}

void test2_space_set_character() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_character(s, 20) == ERROR);
}

void test1_space_get_character() {
    Space *s;
    s = space_create(1);
    space_set_character(s, 20);
    PRINT_TEST_RESULT(space_get_character(s) == 20);
    space_destroy(s);
}

void test2_space_get_character() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_get_character(s) == NO_ID);
    space_destroy(s);
}

void test1_space_set_discovered()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == OK);
  space_destroy(s);
}

void test2_space_set_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == ERROR);
}

void test1_space_get_discovered() {
  Space *s = space_create(5);
  space_set_discovered(s, TRUE);
  PRINT_TEST_RESULT(space_get_discovered(s) == TRUE);
  space_destroy(s);
}

void test2_space_get_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_discovered(s) == FALSE);
}

void test1_space_destroy() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_destroy(s) == OK);
}

void test2_space_destroy() {
    Space *s;
    s = NULL;
    PRINT_TEST_RESULT(space_destroy(s) == ERROR);
}


void test1_space_set_gdesc() {
    Space *s;
    char gdesc[GDESC_ROWS][GDESC_COLS] = { "line1", "line2", "line3", "line4", "line5" };
    s = space_create(1);
    PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == OK);
    space_destroy(s);
}

void test2_space_set_gdesc() {
    Space *s;
    char gdesc[GDESC_ROWS][GDESC_COLS];
    s = NULL;
    strcpy(gdesc[0], "line1");
    strcpy(gdesc[1], "line2");
    strcpy(gdesc[2], "line3");
    strcpy(gdesc[3], "line4");
    strcpy(gdesc[4], "line5");
    PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
}

void test1_space_get_gdesc() {
    Space *s;
    char gdesc[GDESC_ROWS][GDESC_COLS];
    char (*retrieved_gdesc)[GDESC_COLS];
    s = space_create(1);
    strcpy(gdesc[0], "line1");
    strcpy(gdesc[1], "line2");
    strcpy(gdesc[2], "line3");
    strcpy(gdesc[3], "line4");
    strcpy(gdesc[4], "line5");
    space_set_gdesc(s, gdesc);
    retrieved_gdesc = space_get_gdesc(s);
    PRINT_TEST_RESULT(retrieved_gdesc != NULL && strcmp(retrieved_gdesc[0], "line1") == 0);
    space_destroy(s);
}

void test2_space_get_gdesc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_gdesc(s) == NULL);
}





