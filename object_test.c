#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"
#define MAX_TESTS 14
int main(int argc, char** argv) {
    int test = 0;
    if (argc > 1) test = atoi(argv[1]);
    if (test < 0 || test > MAX_TESTS) {
        printf("Error: unknown test %d\t", test);
        exit(EXIT_SUCCESS);
    }

    if (test == 0 || test == 1) test1_object_create();
    if (test == 0 || test == 2) test2_object_create();
    if (test == 0 || test == 3) test1_object_set_name();
    if (test == 0 || test == 4) test2_object_set_name();
    if (test == 0 || test == 5) test1_object_set_desc();
    if (test == 0 || test == 6) test2_object_set_desc();
    if (test == 0 || test == 7) test1_object_get_id();
    if (test == 0 || test == 8) test2_object_get_id();
    if (test == 0 || test == 9) test1_object_get_name();
    if (test == 0 || test == 10) test2_object_get_name();
    if (test == 0 || test == 11) test1_object_get_desc();
    if (test == 0 || test == 12) test2_object_get_desc();
    if (test == 0 || test == 13) test1_object_destroy();
    if (test == 0 || test == 14) test2_object_destroy();


    PRINT_PASSED_PERCENTAGE;
    return 0;
}

void test1_object_create() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(o != NULL);
    object_destroy(o);
}

void test2_object_create() {
    PRINT_TEST_RESULT(object_create(NO_ID) == NULL);
}

void test1_object_set_name() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_name(o, "Sword") == OK);
    object_destroy(o);
}

void test2_object_set_name() {
    PRINT_TEST_RESULT(object_set_name(NULL, "Sword") == ERROR);
}

void test1_object_set_desc() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_desc(o, "A sharp blade") == OK);
    object_destroy(o);
}

void test2_object_set_desc() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_desc(o, NULL) == ERROR);
    object_destroy(o);
}

void test1_object_get_id() {
    Object *o = object_create(100);
    PRINT_TEST_RESULT(object_get_id(o) == 100);
    object_destroy(o);
}

void test2_object_get_id() {
    PRINT_TEST_RESULT(object_get_id(NULL) == NO_ID);
}

void test1_object_get_name() {
    Object *o = object_create(1);
    object_set_name(o, "Shield");
    PRINT_TEST_RESULT(strcmp(object_get_name(o), "Shield") == 0);
    object_destroy(o);
}

void test2_object_get_name() {
    PRINT_TEST_RESULT(object_get_name(NULL) == NULL);
}

void test1_object_get_desc() {
    Object *o = object_create(1);
    object_set_desc(o, "A sturdy shield");
    PRINT_TEST_RESULT(strcmp(object_get_desc(o), "A sturdy shield") == 0);
    object_destroy(o);
}

void test2_object_get_desc() {
    PRINT_TEST_RESULT(object_get_desc(NULL) == NULL);
}

void test1_object_destroy() {
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_destroy(o) == OK);
}

void test2_object_destroy() {
    PRINT_TEST_RESULT(object_destroy(NULL) == ERROR);
}