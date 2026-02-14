/**
 * @brief Implementation of the screen interface
 *
 * @file libscreen.c
 * @author AI Assistant
 * @version 1.0
 * @date 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libscreen.h"

struct _Area {
    int x, y, width, height;
    int cursor_x, cursor_y;
};

static char *__data = NULL;
static int __rows = 0;
static int __columns = 0;

void screen_init(int rows, int columns) {
    if (__data) free(__data);
    __rows = rows;
    __columns = columns;
    __data = (char *)malloc(rows * columns * sizeof(char));
    if (__data) {
        memset(__data, ' ', rows * columns);
    }
}

void screen_destroy() {
    if (__data) {
        free(__data);
        __data = NULL;
    }
}

void screen_paint() {
    if (!__data) return;

    /* Clear terminal using ANSI escape codes */
    printf("\033[2J\033[H");

    for (int i = 0; i < __rows; i++) {
        for (int j = 0; j < __columns; j++) {
            putchar(__data[i * __columns + j]);
        }
        putchar('\n');
    }
}

Area *screen_area_init(int x, int y, int width, int height) {
    Area *area = (Area *)malloc(sizeof(Area));
    if (area) {
        area->x = x;
        area->y = y;
        area->width = width;
        area->height = height;
        area->cursor_x = 0;
        area->cursor_y = 0;
    }
    return area;
}

void screen_area_destroy(Area *area) {
    if (area) free(area);
}

void screen_area_clear(Area *area) {
    if (!area || !__data) return;

    for (int i = 0; i < area->height; i++) {
        for (int j = 0; j < area->width; j++) {
            int screen_x = area->x + j;
            int screen_y = area->y + i;

            /* Boundary check */
            if (screen_x >= 0 && screen_x < __columns &&
                screen_y >= 0 && screen_y < __rows) {
                __data[screen_y * __columns + screen_x] = ' ';
            }
        }
    }
    screen_area_reset_cursor(area);
}

void screen_area_reset_cursor(Area *area) {
    if (area) {
        area->cursor_x = 0;
        area->cursor_y = 0;
    }
}

void screen_area_puts(Area *area, char *str) {
    if (!area || !__data || !str) return;

    int len = strlen(str);
    /* Truncate if string is wider than area */
    if (len > area->width) len = area->width;

    /* Check if we have vertical space */
    if (area->cursor_y >= area->height) return;

    int screen_y = area->y + area->cursor_y;
    int screen_x = area->x;

    for (int i = 0; i < len; i++) {
        int curr_x = screen_x + i;

        /* Boundary check */
        if (curr_x >= 0 && curr_x < __columns &&
            screen_y >= 0 && screen_y < __rows) {
            __data[screen_y * __columns + curr_x] = str[i];
        }
    }

    /* Move cursor to next line */
    area->cursor_y++;
}