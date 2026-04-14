#include "test.h"
#include <stdio.h>

static int total_tests = 0;
static int passed_tests = 0;

void test_print_result(int result) {
    if (result) {
        printf("\tPASSED\n");
        passed_tests++;
    } else {
        printf("\tFAILED\n");
    }
    total_tests++;
}

void test_print_summary() {
    printf("\n%d/%d tests passed (%.2f%%)\n", passed_tests, total_tests, (float)passed_tests / total_tests * 100);
}
