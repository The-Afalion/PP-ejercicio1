/**
 * @brief Implementa la actualización del juego a través de las acciones del usuario
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Funciones privadas
*/

void game_actions_unknown(Game * game);
void game_actions_exit(Game * game);
void game_actions_next(Game * game);
void game_actions_back(Game * game);
void game_actions_take(Game * game);
void game_actions_drop(Game * game);

/**
   Implementación de las acciones del juego
*/

Status game_actions_update(Game *game, Command *command) {
    CommandCode cmd;

    game_set_last_command(game, command);

    cmd = command_get_code(command);

    switch (cmd) {
        case UNKNOWN:
            game_actions_unknown(game);
            break;

        case EXIT:
            game_actions_exit(game);
            break;

        case NEXT:
            game_actions_next(game);
            break;

        case BACK:
            game_actions_back(game);
            break;

        case TAKE:
            game_actions_take(game);
            break;

        case DROP:
            game_actions_drop(game);
            break;

        default:
            break;
    }

    return OK;
}

/**
   Implementación de llamadas para cada acción
*/

void game_actions_unknown(Game *game) {
}

void game_actions_exit(Game *game) {
}

void game_actions_next(Game *game) {
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);
    if (space_id == NO_ID) {
        return;
    }

    current_id = space_get_south(game_get_space(game, space_id));
    if (current_id != NO_ID) {
        game_set_player_location(game, current_id);
    }

    return;
}

void game_actions_back(Game *game) {
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);

    if (NO_ID == space_id) {
        return;
    }

    current_id = space_get_north(game_get_space(game, space_id));
    if (current_id != NO_ID) {
        game_set_player_location(game, current_id);
    }

    return;
}

void game_actions_take(Game *game) {
    Id player_loc = NO_ID;
    Id obj_loc = NO_ID;
    Id obj_id = NO_ID;

    if (!game) {
        return;
    }

    player_loc = game_get_player_location(game);
    obj_loc = game_get_object_location(game);

    /* Si el jugador y el objeto están en el mismo espacio */
    if (player_loc != NO_ID && player_loc == obj_loc) {
        /* Cogemos la ID del único objeto que hay en el juego */
        obj_id = object_get_id(game->object);

        /* Le ponemos el objeto al jugador en su inventario */
        player_set_object(game->player, obj_id);

        /* Quitamos el objeto del espacio del mapa (lo ponemos a NO_ID) */
        game_set_object_location(game, NO_ID);
    }
}

void game_actions_drop(Game *game) {
    Id player_loc = NO_ID;
    Id obj_id = NO_ID;

    if (!game) {
        return;
    }

    player_loc = game_get_player_location(game);

    /* Comprobamos qué objeto lleva el jugador encima */
    obj_id = player_get_object(game->player);

    /* Si el jugador TIENE un objeto y su localización es válida */
    if (obj_id != NO_ID && player_loc != NO_ID) {
        /* Le quitamos el objeto al jugador */
        player_set_object(game->player, NO_ID);

        /* Ponemos el objeto en el espacio actual donde está el jugador */
        game_set_object_location(game, player_loc);
    }
}