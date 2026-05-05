/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Rodrigo
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

/** Numero maximo de pruebas disponibles en este modulo. */
#define MAX_TESTS 47

/** 
 * @brief Main function for SPACE unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
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
  if (all || test == 34) test1_space_add_link();
  if (all || test == 35) test2_space_add_link();
  if (all || test == 36) test1_space_get_link();
  if (all || test == 37) test2_space_get_link();
  if (all || test == 38) test1_space_get_number_of_links();
  if (all || test == 39) test2_space_get_number_of_links();
  if (all || test == 40) test1_space_remove_character();
  if (all || test == 41) test2_space_remove_character();
  if (all || test == 42) test1_space_print();
  if (all || test == 43) test2_space_print();
  if (all || test == 44) test1_space_get_n_characters();
  if (all || test == 45) test2_space_get_n_characters();
  if (all || test == 46) test1_space_get_gdes_from_index();
  if (all || test == 47) test2_space_get_gdes_from_index();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/**
 * @brief Ejecuta la prueba test1_space_create.
 * @author Rodrigo
 */
void test1_space_create() {
  int result;
  Space *s;
  s = space_create(5);
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_create.
 * @author Rodrigo
 */
void test2_space_create() {
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test1_space_set_name.
 * @author Rodrigo
 */
void test1_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_set_name.
 * @author Rodrigo
 */
void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

/**
 * @brief Ejecuta la prueba test3_space_set_name.
 * @author Rodrigo
 */
void test3_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test1_space_get_name.
 * @author Rodrigo
 */
void test1_space_get_name() {
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
  space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_name.
 * @author Rodrigo
 */
void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_space_get_id.
 * @author Rodrigo
 */
void test1_space_get_id() {
  Space *s;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
  space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_id.
 * @author Rodrigo
 */
void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

/**
 * @brief Ejecuta la prueba test1_space_add_object.
 * @author Rodrigo
 */
void test1_space_add_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_add_object(s, 10) == OK);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_add_object.
 * @author Rodrigo
 */
void test2_space_add_object() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_add_object(s, 10) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_space_get_objects.
 * @author Rodrigo
 */
void test1_space_get_objects() {
    Space *s;
    s = space_create(1);
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_get_objects(s)[0] == 10);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_objects.
 * @author Rodrigo
 */
void test2_space_get_objects() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_get_objects(s) == NULL);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test1_space_get_number_of_objects.
 * @author Rodrigo
 */
void test1_space_get_number_of_objects() {
    Space *s;
    s = space_create(1);
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_get_number_of_objects(s) == 1);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_number_of_objects.
 * @author Rodrigo
 */
void test2_space_get_number_of_objects() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_get_number_of_objects(s) == 0);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test1_space_remove_object.
 * @author Rodrigo
 */
void test1_space_remove_object() {
    Space *s;
    s = space_create(1);
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_remove_object(s, 10) == OK);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_remove_object.
 * @author Rodrigo
 */
void test2_space_remove_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_remove_object(s, 10) == ERROR);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test1_space_contains_object.
 * @author Rodrigo
 */
void test1_space_contains_object() {
    Space *s;
    s = space_create(1);
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_contains_object(s, 10) == OK);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_contains_object.
 * @author Rodrigo
 */
void test2_space_contains_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_contains_object(s, 10) == ERROR);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test1_space_set_character.
 * @author Rodrigo
 */
void test1_space_set_character() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_set_character(s, 20) == OK);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_set_character.
 * @author Rodrigo
 */
void test2_space_set_character() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_character(s, 20) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_space_get_character.
 * @author Rodrigo
 */
void test1_space_get_character() {
    Space *s;
    s = space_create(1);
    space_set_character(s, 20);
    PRINT_TEST_RESULT(space_get_character(s, 0) == 20);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_character.
 * @author Rodrigo
 */
void test2_space_get_character() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_get_character(s, 0) == NO_ID);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test1_space_set_discovered.
 * @author Rodrigo
 */
void test1_space_set_discovered()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == OK);
  space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_set_discovered.
 * @author Rodrigo
 */
void test2_space_set_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_space_get_discovered.
 * @author Rodrigo
 */
void test1_space_get_discovered() {
  Space *s = space_create(5);
  space_set_discovered(s, TRUE);
  PRINT_TEST_RESULT(space_get_discovered(s) == TRUE);
  space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_discovered.
 * @author Rodrigo
 */
void test2_space_get_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_discovered(s) == FALSE);
}

/**
 * @brief Ejecuta la prueba test1_space_destroy.
 * @author Rodrigo
 */
void test1_space_destroy() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_destroy(s) == OK);
}

/**
 * @brief Ejecuta la prueba test2_space_destroy.
 * @author Rodrigo
 */
void test2_space_destroy() {
    Space *s;
    s = NULL;
    PRINT_TEST_RESULT(space_destroy(s) == ERROR);
}


/**
 * @brief Ejecuta la prueba test1_space_set_gdesc.
 * @author Rodrigo
 */
void test1_space_set_gdesc() {
    Space *s;
    char gdesc[GDESC_ROWS][GDESC_COLS] = { "line1", "line2", "line3", "line4", "line5" };
    s = space_create(1);
    PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == OK);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_set_gdesc.
 * @author Rodrigo
 */
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

/**
 * @brief Ejecuta la prueba test1_space_get_gdesc.
 * @author Rodrigo
 */
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

/**
 * @brief Ejecuta la prueba test2_space_get_gdesc.
 * @author Rodrigo
 */
void test2_space_get_gdesc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_gdesc(s) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_space_add_link.
 * @author Rodrigo
 */
void test1_space_add_link() {
    Space *s = space_create(1);
    Link *l = link_create(10);
    PRINT_TEST_RESULT(space_add_link(s, l) == OK);
    link_destroy(l);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_add_link.
 * @author Rodrigo
 */
void test2_space_add_link() {
    Link *l = link_create(10);
    PRINT_TEST_RESULT(space_add_link(NULL, l) == ERROR);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test1_space_get_link.
 * @author Rodrigo
 */
void test1_space_get_link() {
    Space *s = space_create(1);
    Link *l = link_create(10);
    space_add_link(s, l);
    PRINT_TEST_RESULT(space_get_link(s, 10) == l);
    link_destroy(l);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_link.
 * @author Rodrigo
 */
void test2_space_get_link() {
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_get_link(s, 10) == NULL);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test1_space_get_number_of_links.
 * @author Rodrigo
 */
void test1_space_get_number_of_links() {
    Space *s = space_create(1);
    Link *l = link_create(10);
    space_add_link(s, l);
    PRINT_TEST_RESULT(space_get_number_of_links(s) == 1);
    link_destroy(l);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_number_of_links.
 * @author Rodrigo
 */
void test2_space_get_number_of_links() {
    PRINT_TEST_RESULT(space_get_number_of_links(NULL) == -1);
}

/**
 * @brief Ejecuta la prueba test1_space_remove_character.
 * @author Rodrigo
 */
void test1_space_remove_character() {
    Space *s = space_create(1);
    space_set_character(s, 20);
    PRINT_TEST_RESULT(space_remove_character(s, 20) == OK);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_remove_character.
 * @author Rodrigo
 */
void test2_space_remove_character() {
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_remove_character(s, 20) == ERROR);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test1_space_print.
 * @author Rodrigo
 */
void test1_space_print() {
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_print(s) == OK);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_print.
 * @author Rodrigo
 */
void test2_space_print() {
    PRINT_TEST_RESULT(space_print(NULL) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_space_get_n_characters.
 * @author Rodrigo
 */
void test1_space_get_n_characters() {
    Space *s = space_create(1);
    space_set_character(s, 20);
    space_set_character(s, 21);
    PRINT_TEST_RESULT(space_get_n_characters(s) == 2);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_n_characters.
 * @author Rodrigo
 */
void test2_space_get_n_characters() {
    PRINT_TEST_RESULT(space_get_n_characters(NULL) == -1);
}

/**
 * @brief Ejecuta la prueba test1_space_get_gdes_from_index.
 * @author Rodrigo
 */
void test1_space_get_gdes_from_index() {
    Space *s;
    char gdesc[GDESC_ROWS][GDESC_COLS] = { "line1", "line2", "line3", "line4", "line5" };
    s = space_create(1);
    space_set_gdesc(s, gdesc);
    PRINT_TEST_RESULT(strcmp(space_get_gdes_from_index(s, 2), "line3") == 0);
    space_destroy(s);
}

/**
 * @brief Ejecuta la prueba test2_space_get_gdes_from_index.
 * @author Rodrigo
 */
void test2_space_get_gdes_from_index() {
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_get_gdes_from_index(s, 5) == NULL);
    space_destroy(s);
}



