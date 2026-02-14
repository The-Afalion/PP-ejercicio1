/**
 * @brief Implementa la actualización del juego basada en las acciones del usuario.
 * @file game_actions.c
 * @author Rodrigo & Unai
 * @version 2.0
 * @date 12-03-2024
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include "game.h"
#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Prototipos de funciones privadas para manejar cada acción del juego.
 */
void game_actions_unknown(Game *game);
void game_actions_exit(Game *game);
void game_actions_next(Game *game);
void game_actions_back(Game *game);
void game_actions_take(Game *game);
void game_actions_drop(Game *game);

/**
 * @brief Actualiza el estado del juego según el último comando.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Puntero a la estructura del juego.
 * @param command Puntero al último comando introducido.
 * @return OK si la actualización se realiza correctamente, ERROR en caso contrario.
 */
Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  if (!game || !command) {
    return ERROR;
  }

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
 * @brief Maneja la acción de un comando desconocido.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Puntero a la estructura del juego.
 */
void game_actions_unknown(Game *game) {
  /* No se realiza ninguna acción */
}

/**
 * @brief Maneja la acción de salir del juego.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Puntero a la estructura del juego.
 */
void game_actions_exit(Game *game) {
  /* La lógica de salida se maneja en el bucle principal del juego */
}

/**
 * @brief Mueve al jugador al espacio sur (siguiente).
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Puntero a la estructura del juego.
 */
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
}

/**
 * @brief Mueve al jugador al espacio norte (anterior).
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Puntero a la estructura del juego.
 */
void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }
}

/**
 * @brief El jugador coge un objeto del espacio actual.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Puntero a la estructura del juego.
 */
void game_actions_take(Game *game) {
  Id player_loc = NO_ID;
  Id obj_loc = NO_ID;
  Id obj_id = NO_ID;

  if (!game) {
    return;
  }

  player_loc = game_get_player_location(game);
  obj_loc = game_get_object_location(game);

  /* El jugador solo puede coger el objeto si está en el mismo espacio */
  if (player_loc != NO_ID && player_loc == obj_loc) {
    obj_id = object_get_id(game->object);
    
    /* Asigna el objeto al inventario del jugador */
    player_set_object(game->player, obj_id);
    
    /* Elimina el objeto del espacio */
    game_set_object_location(game, NO_ID);
  }
}

/**
 * @brief El jugador deja un objeto en el espacio actual.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Puntero a la estructura del juego.
 */
void game_actions_drop(Game *game) {
  Id player_loc = NO_ID;
  Id obj_id = NO_ID;

  if (!game) {
    return;
  }

  player_loc = game_get_player_location(game);
  obj_id = player_get_object(game->player);

  /* El jugador solo puede dejar un objeto si tiene uno y está en una ubicación válida */
  if (obj_id != NO_ID && player_loc != NO_ID) {
    /* Elimina el objeto del inventario del jugador */
    player_set_object(game->player, NO_ID);
    
    /* Coloca el objeto en el espacio actual del jugador */
    game_set_object_location(game, player_loc);
  }
}
