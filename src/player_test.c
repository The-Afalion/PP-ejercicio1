/**
 * @brief Pruebas unitarias del modulo Player.
 *
 * @file player_test.c
 * @author Rodrigo
 * @version 1.0
 * @date 05-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "player_test.h"
#include "test.h"
/** Numero maximo de pruebas disponibles en este modulo. */
#define MAX_TESTS 46

/**
 * @brief Funcion principal de las pruebas del modulo Player.
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

    if (test == 0 || test == 1) test1_player_create();
    if (test == 0 || test == 2) test2_player_create();
    if (test == 0 || test == 3) test1_player_set_name();
    if (test == 0 || test == 4) test2_player_set_name();
    if (test == 0 || test == 5) test1_player_set_location();
    if (test == 0 || test == 6) test2_player_set_location();
    if (test == 0 || test == 7) test1_player_set_health();
    if (test == 0 || test == 8) test2_player_set_health();
    if (test == 0 || test == 9) test1_player_add_object();
    if (test == 0 || test == 10) test2_player_add_object();
    if (test == 0 || test == 11) test1_player_del_object();
    if (test == 0 || test == 12) test2_player_del_object();
    if (test == 0 || test == 13) test1_player_has_object();
    if (test == 0 || test == 14) test2_player_has_object();
    if (test == 0 || test == 15) test1_player_get_backpack();
    if (test == 0 || test == 16) test2_player_get_backpack();
    if (test == 0 || test == 17) test1_player_get_name();
    if (test == 0 || test == 18) test2_player_get_name();
    if (test == 0 || test == 19) test1_player_get_location();
    if (test == 0 || test == 20) test2_player_get_location();
    if (test == 0 || test == 21) test1_player_get_health();
    if (test == 0 || test == 22) test2_player_get_health();
    if (test == 0 || test == 23) test1_player_get_gdesc();
    if (test == 0 || test == 24) test2_player_get_gdesc();
    if (test == 0 || test == 25) test1_player_set_gdesc();
    if (test == 0 || test == 26) test2_player_set_gdesc();
    if (test == 0 || test == 27) test1_player_destroy();
    if (test == 0 || test == 28) test2_player_destroy();
    if (test == 0 || test == 29) test1_player_get_id();
    if (test == 0 || test == 30) test2_player_get_id();
    if (test == 0 || test == 31) test1_player_get_object();
    if (test == 0 || test == 32) test2_player_get_object();
    if (test == 0 || test == 33) test1_player_print();
    if (test == 0 || test == 34) test2_player_print();
    if (test == 0 || test == 35) test1_player_get_number_of_backpack();
    if (test == 0 || test == 36) test2_player_get_number_of_backpack();
    if (test == 0 || test == 37) test1_player_set_team();
    if (test == 0 || test == 38) test2_player_set_team();
    if (test == 0 || test == 39) test1_player_get_team();
    if (test == 0 || test == 40) test2_player_get_team();
    if (test == 0 || test == 41) test1_player_set_money();
    if (test == 0 || test == 42) test2_player_set_money();
    if (test == 0 || test == 43) test1_player_get_money();
    if (test == 0 || test == 44) test2_player_get_money();
    if (test == 0 || test == 45) test1_player_has_money();
    if (test == 0 || test == 46) test2_player_has_money();

    PRINT_PASSED_PERCENTAGE;
    return 0;
}

/**
 * @brief Ejecuta la prueba test1_player_create.
 * @author Rodrigo
 */
void test1_player_create() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(p != NULL);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_create.
 * @author Rodrigo
 */
void test2_player_create() {
    PRINT_TEST_RESULT(player_create(NO_ID) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_player_set_name.
 * @author Rodrigo
 */
void test1_player_set_name() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_set_name(p, "Hero") == OK);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_set_name.
 * @author Rodrigo
 */
void test2_player_set_name() {
    PRINT_TEST_RESULT(player_set_name(NULL, "Hero") == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_player_set_location.
 * @author Rodrigo
 */
void test1_player_set_location() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_set_location(p, 100) == OK);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_set_location.
 * @author Rodrigo
 */
void test2_player_set_location() {
    PRINT_TEST_RESULT(player_set_location(NULL, 100) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_player_set_health.
 * @author Rodrigo
 */
void test1_player_set_health() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_set_health(p, 5) == OK);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_set_health.
 * @author Rodrigo
 */
void test2_player_set_health() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_set_health(p, -1) == ERROR);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test1_player_add_object.
 * @author Rodrigo
 */
void test1_player_add_object() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_add_object(p, 20) == OK);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_add_object.
 * @author Rodrigo
 */
void test2_player_add_object() {
    Player *p = player_create(1);
    player_add_object(p, 20); /* Supongamos max_objs = 1 para el test */
    inventory_set_max_objs(player_get_backpack(p), 1);
    PRINT_TEST_RESULT(player_add_object(p, 21) == ERROR);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test1_player_del_object.
 * @author Rodrigo
 */
void test1_player_del_object() {
    Player *p = player_create(1);
    player_add_object(p, 20);
    PRINT_TEST_RESULT(player_del_object(p, 20) == OK);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_del_object.
 * @author Rodrigo
 */
void test2_player_del_object() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_del_object(p, 20) == ERROR);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test1_player_has_object.
 * @author Rodrigo
 */
void test1_player_has_object() {
    Player *p = player_create(1);
    player_add_object(p, 20);
    PRINT_TEST_RESULT(player_has_object(p, 20) == TRUE);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_has_object.
 * @author Rodrigo
 */
void test2_player_has_object() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_has_object(p, 20) == FALSE);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test1_player_get_backpack.
 * @author Rodrigo
 */
void test1_player_get_backpack() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_get_backpack(p) != NULL);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_backpack.
 * @author Rodrigo
 */
void test2_player_get_backpack() {
    PRINT_TEST_RESULT(player_get_backpack(NULL) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_player_get_name.
 * @author Rodrigo
 */
void test1_player_get_name() {
    Player *p = player_create(1);
    player_set_name(p, "Hero");
    PRINT_TEST_RESULT(strcmp(player_get_name(p), "Hero") == 0);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_name.
 * @author Rodrigo
 */
void test2_player_get_name() {
    PRINT_TEST_RESULT(player_get_name(NULL) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_player_get_location.
 * @author Rodrigo
 */
void test1_player_get_location() {
    Player *p = player_create(1);
    player_set_location(p, 100);
    PRINT_TEST_RESULT(player_get_location(p) == 100);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_location.
 * @author Rodrigo
 */
void test2_player_get_location() {
    PRINT_TEST_RESULT(player_get_location(NULL) == NO_ID);
}

/**
 * @brief Ejecuta la prueba test1_player_get_health.
 * @author Rodrigo
 */
void test1_player_get_health() {
    Player *p = player_create(1);
    player_set_health(p, 5);
    PRINT_TEST_RESULT(player_get_health(p) == 5);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_health.
 * @author Rodrigo
 */
void test2_player_get_health() {
    PRINT_TEST_RESULT(player_get_health(NULL) == -1);
}

/**
 * @brief Ejecuta la prueba test1_player_set_gdesc.
 * @author Rodrigo
 */
void test1_player_set_gdesc() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_set_gdesc(p, "A brave hero") == OK);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_set_gdesc.
 * @author Rodrigo
 */
void test2_player_set_gdesc() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_set_gdesc(p, NULL) == ERROR);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test1_player_get_gdesc.
 * @author Rodrigo
 */
void test1_player_get_gdesc() {
    Player *p = player_create(1);
    player_set_gdesc(p, "A brave hero");
    PRINT_TEST_RESULT(strcmp(player_get_gdesc(p), "A brave hero") == 0);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_gdesc.
 * @author Rodrigo
 */
void test2_player_get_gdesc() {
    PRINT_TEST_RESULT(player_get_gdesc(NULL) == NULL);
}

/**
 * @brief Ejecuta la prueba test1_player_destroy.
 * @author Rodrigo
 */
void test1_player_destroy() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_destroy(p) == OK);
}

/**
 * @brief Ejecuta la prueba test2_player_destroy.
 * @author Rodrigo
 */
void test2_player_destroy() {
    PRINT_TEST_RESULT(player_destroy(NULL) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_player_get_id.
 * @author Rodrigo
 */
void test1_player_get_id() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_get_id(p) == 1);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_id.
 * @author Rodrigo
 */
void test2_player_get_id() {
    PRINT_TEST_RESULT(player_get_id(NULL) == NO_ID);
}

/**
 * @brief Ejecuta la prueba test1_player_get_object.
 * @author Rodrigo
 */
void test1_player_get_object() {
    Player *p = player_create(1);
    player_add_object(p, 20);
    PRINT_TEST_RESULT(player_get_object(p, 0) == 20);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_object.
 * @author Rodrigo
 */
void test2_player_get_object() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_get_object(p, 0) == NO_ID);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test1_player_print.
 * @author Rodrigo
 */
void test1_player_print() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_print(p) == OK);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_print.
 * @author Rodrigo
 */
void test2_player_print() {
    PRINT_TEST_RESULT(player_print(NULL) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_player_get_number_of_backpack.
 * @author Rodrigo
 */
void test1_player_get_number_of_backpack() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_get_number_of_backpack(p) == INVENTORY_SIZE);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_number_of_backpack.
 * @author Rodrigo
 */
void test2_player_get_number_of_backpack() {
    PRINT_TEST_RESULT(player_get_number_of_backpack(NULL) == -1);
}

/**
 * @brief Ejecuta la prueba test1_player_set_team.
 * @author Rodrigo
 */
void test1_player_set_team() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_set_team(p, 4) == OK);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_set_team.
 * @author Rodrigo
 */
void test2_player_set_team() {
    PRINT_TEST_RESULT(player_set_team(NULL, 4) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_player_get_team.
 * @author Rodrigo
 */
void test1_player_get_team() {
    Player *p = player_create(1);
    player_set_team(p, 4);
    PRINT_TEST_RESULT(player_get_team(p) == 4);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_team.
 * @author Rodrigo
 */
void test2_player_get_team() {
    PRINT_TEST_RESULT(player_get_team(NULL) == NO_ID);
}

/**
 * @brief Ejecuta la prueba test1_player_set_money.
 * @author Rodrigo
 */
void test1_player_set_money() {
    Player *p = player_create(1);
    PRINT_TEST_RESULT(player_set_money(p, 10) == OK);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_set_money.
 * @author Rodrigo
 */
void test2_player_set_money() {
    PRINT_TEST_RESULT(player_set_money(NULL, 10) == ERROR);
}

/**
 * @brief Ejecuta la prueba test1_player_get_money.
 * @author Rodrigo
 */
void test1_player_get_money() {
    Player *p = player_create(1);
    player_set_money(p, 10);
    PRINT_TEST_RESULT(player_get_money(p) == 10);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_get_money.
 * @author Rodrigo
 */
void test2_player_get_money() {
    PRINT_TEST_RESULT(player_get_money(NULL) == -1);
}

/**
 * @brief Ejecuta la prueba test1_player_has_money.
 * @author Rodrigo
 */
void test1_player_has_money() {
    Player *p = player_create(1);
    player_set_money(p, 10);
    PRINT_TEST_RESULT(player_has_money(p, 5) == TRUE);
    player_destroy(p);
}

/**
 * @brief Ejecuta la prueba test2_player_has_money.
 * @author Rodrigo
 */
void test2_player_has_money() {
    Player *p = player_create(1);
    player_set_money(p, 10);
    PRINT_TEST_RESULT(player_has_money(p, 20) == FALSE);
    player_destroy(p);
}
