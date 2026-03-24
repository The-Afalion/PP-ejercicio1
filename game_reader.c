/**
 * @brief Implementación del módulo de carga de juegos
 * @file game_reader.c
 * @author Unai
 * @version 1.0
 * @date 16-03-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"
#include "game.h"
#include "space.h"
#include "character.h"
#include "object.h"

/**
 * @brief Carga los espacios desde un archivo de datos
 * @author Unai
 */
Status game_reader_load_spaces(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
    Space *space = NULL;
    Status status = OK;
    char *endptr;
    char gdesc[GDESC_ROWS][GDESC_COLS];
    int i;
    Status des;

    if (!filename) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#s:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            north = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            east = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            south = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            west = strtol(toks, &endptr, 10);

            for (i = 0, des = OK; i < GDESC_ROWS; i++) {
                toks = strtok(NULL, "|");
                if (toks) {
                    if (strlen(toks) != GDESC_COLS - 1) des = ERROR;
                    else strcpy(gdesc[i], toks);
                } else {
                    strcpy(gdesc[i], "         ");
                }
            }

            space = space_create(id);
            if (space != NULL) {
                space_set_name(space, name);
                space_set_north(space, north);
                space_set_east(space, east);
                space_set_south(space, south);
                space_set_west(space, west);
                if (des != ERROR) space_set_gdesc(space, gdesc);
                
                /* ASIGNACIÓN: Añadimos el objeto de tipo espacio a la lista general del juego */
                game_add_space(game, space);
            }
        }
    }

    if (ferror(file)) status = ERROR;
    fclose(file);
    return status;
}

/**
 * @brief Carga los objetos desde un archivo de datos
 * @author Unai
 */
Status game_reader_load_objects(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID, location_id = NO_ID;
    Object *object = NULL;
    Status status = OK;
    char *endptr;
    char description[WORD_SIZE] = "";

    if (!filename) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#o:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            location_id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            if (toks) strcpy(description, toks);

            object = object_create(id);
            if (object != NULL) {
                object_set_name(object, name);
                object_set_desc(object, description);

                /* ASIGNACIÓN: Guardamos el puntero del objeto en el array global de objetos del juego */
                game_add_object(game, object);
                
                /* ASIGNACIÓN: Metemos el ID del objeto dentro del Set de objetos del espacio indicado */
                game_set_object_location(game, location_id, id);
            }
        }
    }

    if (ferror(file)) status = ERROR;
    fclose(file);
    return status;
}

/**
 * @brief Carga los personajes desde un archivo de datos
 * @author Unai
 */
Status game_reader_load_characters(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char gdesc[7] = "";
    char message[101] = "";
    char *toks = NULL;
    Id id = NO_ID, location_id = NO_ID;
    int health = 0;
    int friendly = 0;
    Character *character = NULL;
    Status status = OK;
    char *endptr;

    if (!filename) return ERROR;

    file = fopen(filename, "r");
    if (file == NULL) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#c:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            strcpy(gdesc, toks);
            toks = strtok(NULL, "|");
            health = (int) strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            friendly = (int) strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            location_id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(message, toks);

            character = character_create(id);
            if (character != NULL) {
                character_set_name(character, name);
                character_set_gdesc(character, gdesc);
                character_set_health(character, health);
                character_set_friendly(character, friendly);
                character_set_message(character, message);
                
                /* ASIGNACIÓN: Guardamos el puntero del personaje en el registro general del juego */
                game_add_character(game, character);
                
                /* ASIGNACIÓN : Vinculamos el ID del personaje al campo 'character' del espacio correspondiente */
                game_set_character_location(game, location_id, id);
            }
        }
    }

    if (ferror(file)) status = ERROR;
    fclose(file);
    return status;
}