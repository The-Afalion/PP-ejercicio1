/**
 * @brief Pruebas unitarias del modulo Link.
 *
 * @file link_test.c
 * @author Rodrigo
 * @version 1.0
 * @date 05-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "link_test.h"
#include "test.h"
/** Numero maximo de pruebas disponibles en este modulo. */
#define MAX_TESTS 30

/**
 * @brief Funcion principal de las pruebas del modulo Link.
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

    if (test == 0 || test == 1) test1_link_create();
    if (test == 0 || test == 2) test2_link_create();
    if (test == 0 || test == 3) test1_link_set_name();
    if (test == 0 || test == 4) test2_link_set_name();
    if (test == 0 || test == 5) test1_link_set_origin();
    if (test == 0 || test == 6) test2_link_set_origin();
    if (test == 0 || test == 7) test1_link_set_destination();
    if (test == 0 || test == 8) test2_link_set_destination();
    if (test == 0 || test == 9) test1_link_set_direction();
    if (test == 0 || test == 10) test2_link_set_direction();
    if (test == 0 || test == 11) test1_link_set_open();
    if (test == 0 || test == 12) test2_link_set_open();
    if (test == 0 || test == 13) test1_link_set_id();
    if (test == 0 || test == 14) test2_link_set_id();
    if (test == 0 || test == 15) test1_link_destroy();
    if (test == 0 || test == 16) test2_link_destroy();
    if (test == 0 || test == 17) test1_link_get_id();
    if (test == 0 || test == 18) test2_link_get_id();
    if (test == 0 || test == 19) test1_link_get_name();
    if (test == 0 || test == 20) test2_link_get_name();
    if (test == 0 || test == 21) test1_link_get_origin();
    if (test == 0 || test == 22) test2_link_get_origin();
    if (test == 0 || test == 23) test1_link_get_destination();
    if (test == 0 || test == 24) test2_link_get_destination();
    if (test == 0 || test == 25) test1_link_get_direction();
    if (test == 0 || test == 26) test2_link_get_direction();
    if (test == 0 || test == 27) test1_link_get_open();
    if (test == 0 || test == 28) test2_link_get_open();
    if (test == 0 || test == 29) test1_link_print();
    if (test == 0 || test == 30) test2_link_print();


    PRINT_PASSED_PERCENTAGE;
    return 0;
}

/**
 * @brief Ejecuta la prueba test1_link_create.
 * @author Rodrigo
 */
void test1_link_create() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(l != NULL);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_create.
 * @author Rodrigo
 */
void test2_link_create() {
    PRINT_TEST_RESULT(link_create(NO_ID) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_link_set_name.
 * @author Rodrigo
 */
void test1_link_set_name() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_name(l, "norte") == OK);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_set_name.
 * @author Rodrigo
 */
void test2_link_set_name() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_name(l, NULL) == ERROR);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test1_link_set_origin.
 * @author Rodrigo
 */
void test1_link_set_origin() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_origin(l, 10) == OK);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_set_origin.
 * @author Rodrigo
 */
void test2_link_set_origin() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_origin(l, 10) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_link_set_destination.
 * @author Rodrigo
 */
void test1_link_set_destination() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_destination(l, 20) == OK);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_set_destination.
 * @author Rodrigo
 */
void test2_link_set_destination() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_destination(l, 20) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_link_set_direction.
 * @author Rodrigo
 */
void test1_link_set_direction() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_direction(l, N) == OK); /* Cambiado 'norte' por 'N' */
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_set_direction.
 * @author Rodrigo
 */
void test2_link_set_direction() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_direction(l, S) == ERROR); /* Cambiado 'sur' por 'S' */
}

/**
 * @brief Ejecuta la prueba test1_link_set_open.
 * @author Rodrigo
 */
void test1_link_set_open() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_open(l, TRUE) == OK);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_set_open.
 * @author Rodrigo
 */
void test2_link_set_open() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_open(l, FALSE) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_link_set_id.
 * @author Rodrigo
 */
void test1_link_set_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_id(l, 10) == OK);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_set_id.
 * @author Rodrigo
 */
void test2_link_set_id() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_id(l, 10) == ERROR);
}


/**
 * @brief Ejecuta la prueba test1_link_destroy.
 * @author Rodrigo
 */
void test1_link_destroy() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_destroy(l) == OK);
}

/**
 * @brief Ejecuta la prueba test2_link_destroy.
 * @author Rodrigo
 */
void test2_link_destroy() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_destroy(l) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_link_get_id.
 * @author Rodrigo
 */
void test1_link_get_id() {
    Link *l = link_create(100);
    PRINT_TEST_RESULT(link_get_id(l) == 100);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_get_id.
 * @author Rodrigo
 */
void test2_link_get_id() {
    PRINT_TEST_RESULT(link_get_id(NULL) == NO_ID);
}

/**
 * @brief Ejecuta la prueba test1_link_get_name.
 * @author Rodrigo
 */
void test1_link_get_name() {
    Link *l = link_create(1);
    link_set_name(l, "norte");
    PRINT_TEST_RESULT(strcmp(link_get_name(l), "norte") == 0);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_get_name.
 * @author Rodrigo
 */
void test2_link_get_name() {
    PRINT_TEST_RESULT(link_get_name(NULL) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_link_get_origin.
 * @author Rodrigo
 */
void test1_link_get_origin() {
    Link *l = link_create(1);
    link_set_origin(l, 10);
    PRINT_TEST_RESULT(link_get_origin(l) == 10);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_get_origin.
 * @author Rodrigo
 */
void test2_link_get_origin() {
    PRINT_TEST_RESULT(link_get_origin(NULL) == NO_ID);
}

/**
 * @brief Ejecuta la prueba test1_link_get_destination.
 * @author Rodrigo
 */
void test1_link_get_destination() {
    Link *l = link_create(1);
    link_set_destination(l, 20);
    PRINT_TEST_RESULT(link_get_destination(l) == 20);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_get_destination.
 * @author Rodrigo
 */
void test2_link_get_destination() {
    PRINT_TEST_RESULT(link_get_destination(NULL) == NO_ID);
}

/**
 * @brief Ejecuta la prueba test1_link_get_direction.
 * @author Rodrigo
 */
void test1_link_get_direction() {
    Link *l = link_create(1);
    link_set_direction(l, E); /* Cambiado 'este' por 'E' */
    PRINT_TEST_RESULT(link_get_direction(l) == E); /* Cambiado 'este' por 'E' */
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_get_direction.
 * @author Rodrigo
 */
void test2_link_get_direction() {
    PRINT_TEST_RESULT(link_get_direction(NULL) == NO_DIRECTION);
}

/**
 * @brief Ejecuta la prueba test1_link_get_open.
 * @author Rodrigo
 */
void test1_link_get_open() {
    Link *l = link_create(1);
    link_set_open(l, TRUE);
    PRINT_TEST_RESULT(link_get_open(l) == TRUE);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_get_open.
 * @author Rodrigo
 */
void test2_link_get_open() {
    PRINT_TEST_RESULT(link_get_open(NULL) == FALSE);
}

/**
 * @brief Ejecuta la prueba test1_link_print.
 * @author Rodrigo
 */
void test1_link_print() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_print(l) == OK);
    link_destroy(l);
}

/**
 * @brief Ejecuta la prueba test2_link_print.
 * @author Rodrigo
 */
void test2_link_print() {
    PRINT_TEST_RESULT(link_print(NULL) == ERROR);
}
