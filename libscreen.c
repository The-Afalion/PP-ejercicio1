/**
 * @brief Implementa la interfaz de la pantalla
 *
 * @file libscreen.c
 * @author Unai y Rodrigo
 * @version 1.0
 * @date 15-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libscreen.h"

#define CURSOR_START 0

struct _Area {
    int x, y, width, height;
    int cursor_x, cursor_y;
};

static char *__data = NULL;
static int __rows = 0;
static int __columns = 0;

void screen_init(int rows, int columns) {
    if (__data) {
        free(__data);
    }
    
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
    /* Variables declaradas al principio (Estricto ANSI C) */
    int i, j;

    if (!__data) {
        return;
    }

    printf("\033[2J\033[H");

    for (i = 0; i < __rows; i++) {
        for (j = 0; j < __columns; j++) {
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
        area->cursor_x = CURSOR_START;
        area->cursor_y = CURSOR_START;
    }
    return area;
}

void screen_area_destroy(Area *area) {
    if (area) {
        free(area);
    }
}

void screen_area_clear(Area *area) {
    /* Variables declaradas al principio (Estricto ANSI C) */
    int i, j, screen_x, screen_y;

    if (!area || !__data) {
        return;
    }

    for (i = 0; i < area->height; i++) {
        for (j = 0; j < area->width; j++) {
            screen_x = area->x + j;
            screen_y = area->y + i;

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
        area->cursor_x = CURSOR_START;
        area->cursor_y = CURSOR_START;
    }
}

void screen_area_puts(Area *area, char *str) {
    /* Variables declaradas al principio (Estricto ANSI C) */
    int len, screen_y, screen_x, i, curr_x;

    if (!area || !__data || !str) {
        return;
    }

    len = strlen(str);
    
    if (len > area->width) {
        len = area->width;
    }

    if (area->cursor_y >= area->height) {
        return;
    }

    screen_y = area->y + area->cursor_y;
    screen_x = area->x;

    for (i = 0; i < len; i++) {
        curr_x = screen_x + i;

        if (curr_x >= 0 && curr_x < __columns &&
            screen_y >= 0 && screen_y < __rows) {
            __data[screen_y * __columns + curr_x] = str[i];
        }
    }

    area->cursor_y++;
}