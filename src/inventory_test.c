/**
 * @brief Pruebas unitarias del modulo Inventory.
 *
 * @file inventory_test.c
 * @author Rodrigo
 * @version 1.0
 * @date 05-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "inventory_test.h"
#include "test.h"
/** Numero maximo de pruebas disponibles en este modulo. */
#define MAX_TESTS 20

/**
 * @brief Funcion principal de las pruebas del modulo Inventory.
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
    if (argc > 1) test = atoi(argv[1]);
    if (test < 0 || test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
        exit(EXIT_SUCCESS);
    }
    
    if (test == 0 || test == 1) test1_inventory_create();
    if (test == 0 || test == 2) test2_inventory_create();
    if (test == 0 || test == 3) test1_inventory_destroy();
    if (test == 0 || test == 4) test2_inventory_destroy();
    if (test == 0 || test == 5) test1_inventory_get_objs();
    if (test == 0 || test == 6) test2_inventory_get_objs();
    if (test == 0 || test == 7) test1_inventory_get_max_objs();
    if (test == 0 || test == 8) test2_inventory_get_max_objs();
    if (test == 0 || test == 9) test1_inventory_set_objs();
    if (test == 0 || test == 10) test2_inventory_set_objs();
    if (test == 0 || test == 11) test1_inventory_set_max_objs();
    if (test == 0 || test == 12) test2_inventory_set_max_objs();
    if (test == 0 || test == 13) test1_inventory_add_object();
    if (test == 0 || test == 14) test2_inventory_add_object();
    if (test == 0 || test == 15) test1_inventory_del_object();
    if (test == 0 || test == 16) test2_inventory_del_object();
    if (test == 0 || test == 17) test1_inventory_is_full();
    if (test == 0 || test == 18) test2_inventory_is_full();
    if (test == 0 || test == 19) test1_inventory_print();
    if (test == 0 || test == 20) test2_inventory_print();


    PRINT_PASSED_PERCENTAGE;
    return 0;
}

/**
 * @brief Ejecuta la prueba test1_inventory_create.
 * @author Rodrigo
 */
void test1_inventory_create() {
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(i != NULL);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test2_inventory_create.
 * @author Rodrigo
 */
void test2_inventory_create() {
    Inventory *i = inventory_create(-1);
    PRINT_TEST_RESULT(i == NULL);
}

/**
 * @brief Ejecuta la prueba test1_inventory_destroy.
 * @author Rodrigo
 */
void test1_inventory_destroy() {
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(inventory_destroy(i) == OK);
}

/**
 * @brief Ejecuta la prueba test2_inventory_destroy.
 * @author Rodrigo
 */
void test2_inventory_destroy() {
    PRINT_TEST_RESULT(inventory_destroy(NULL) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_inventory_get_objs.
 * @author Rodrigo
 */
void test1_inventory_get_objs() {
    Inventory *i = inventory_create(5);
    Set *s = inventory_get_objs(i);
    PRINT_TEST_RESULT(s != NULL);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test2_inventory_get_objs.
 * @author Rodrigo
 */
void test2_inventory_get_objs() {
    PRINT_TEST_RESULT(inventory_get_objs(NULL) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_inventory_get_max_objs.
 * @author Rodrigo
 */
void test1_inventory_get_max_objs() {
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(inventory_get_max_objs(i) == 5);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test2_inventory_get_max_objs.
 * @author Rodrigo
 */
void test2_inventory_get_max_objs() {
    PRINT_TEST_RESULT(inventory_get_max_objs(NULL) == -1);
}

/**
 * @brief Ejecuta la prueba test1_inventory_set_objs.
 * @author Rodrigo
 */
void test1_inventory_set_objs() {
    Inventory *i = inventory_create(5);
    Set *s = set_create(10);
    PRINT_TEST_RESULT(inventory_set_objs(i, s) == OK);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test2_inventory_set_objs.
 * @author Rodrigo
 */
void test2_inventory_set_objs() {
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(inventory_set_objs(i, NULL) == ERROR);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test1_inventory_set_max_objs.
 * @author Rodrigo
 */
void test1_inventory_set_max_objs() {
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(inventory_set_max_objs(i, 10) == OK);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test2_inventory_set_max_objs.
 * @author Rodrigo
 */
void test2_inventory_set_max_objs() {
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(inventory_set_max_objs(i, -1) == ERROR);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test1_inventory_add_object.
 * @author Rodrigo
 */
void test1_inventory_add_object() {
    Inventory *i = inventory_create(1);
    PRINT_TEST_RESULT(inventory_add_object(i, 10) == OK);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test2_inventory_add_object.
 * @author Rodrigo
 */
void test2_inventory_add_object() {
    Inventory *i = inventory_create(1);
    inventory_add_object(i, 10);
    PRINT_TEST_RESULT(inventory_add_object(i, 11) == ERROR);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test1_inventory_del_object.
 * @author Rodrigo
 */
void test1_inventory_del_object() {
    Inventory *i = inventory_create(1);
    inventory_add_object(i, 10);
    PRINT_TEST_RESULT(inventory_del_object(i, 10) == OK);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test2_inventory_del_object.
 * @author Rodrigo
 */
void test2_inventory_del_object() {
    Inventory *i = inventory_create(1);
    PRINT_TEST_RESULT(inventory_del_object(i, 10) == ERROR);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test1_inventory_is_full.
 * @author Rodrigo
 */
void test1_inventory_is_full() {
    Inventory *i = inventory_create(1);
    inventory_add_object(i, 10);
    PRINT_TEST_RESULT(inventory_is_full(i) == TRUE);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test2_inventory_is_full.
 * @author Rodrigo
 */
void test2_inventory_is_full() {
    Inventory *i = inventory_create(1);
    PRINT_TEST_RESULT(inventory_is_full(i) == FALSE);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test1_inventory_print.
 * @author Rodrigo
 */
void test1_inventory_print() {
    Inventory *i = inventory_create(2);
    inventory_add_object(i, 10);
    PRINT_TEST_RESULT(inventory_print(i) == OK);
    inventory_destroy(i);
}

/**
 * @brief Ejecuta la prueba test2_inventory_print.
 * @author Rodrigo
 */
void test2_inventory_print() {
    PRINT_TEST_RESULT(inventory_print(NULL) == ERROR);
}
