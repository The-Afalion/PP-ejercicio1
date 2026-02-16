/**
 * @brief Implementa la estructura del juego
 *
 * @file game.c
 * @author Unai y Rodrigo
 * @version 1.0
 * @date 15-02-2026
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"
#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLAYER_ID 0
#define OBJECT_ID 0
#define FIRST_POSITION 0

/**
   Funciones privadas
*/
Status game_add_space(Game *game, Space *space);

Id game_get_space_id_at(Game *game, int position);

/**
   Implementación de la interfaz del juego
*/

Status game_create(Game *game) {
  int i;

  /* Inicializamos el array de espacios a NULL */
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  /* Inicializamos el resto de variables por defecto */
  game->n_spaces = 0;
  game->player = player_create(PLAYER_ID);
  game->object = object_create(OBJECT_ID);
  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

Status game_create_from_file(Game *game, char *filename) {
  /* Comprobamos que el juego y el nombre de archivo existan */
  if (!game || !filename) {
    return ERROR;
  }

  /* Inicializamos el juego base y comprobamos errores */
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  /* Cargamos los espacios desde el archivo de texto */
  if (game_reader_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* Colocamos al jugador y al objeto en el primer espacio cargado */
  game_set_player_location(game, game_get_space_id_at(game, FIRST_POSITION));
  game_set_object_location(game, game_get_space_id_at(game, FIRST_POSITION));

  return OK;
}

Status game_destroy(Game *game) {
  int i;

  /* Destruimos todos los espacios creados */
  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  /* Destruimos al jugador y comprobamos error */
  if (!player_destroy(game->player)) {
    return ERROR;
  }

  /* Destruimos el objeto y comprobamos error */
  if (!object_destroy(game->object)) {
    return ERROR;
  }

  /* Destruimos el último comando y comprobamos error */
  if (!command_destroy(game->last_cmd)) {
    return ERROR;
  }

  return OK;
}

Space *game_get_space(Game *game, Id id) {
  int i;

  /* Comprobamos validez de la ID y del juego */
  if (id == NO_ID || !game) {
    return NULL;
  }

  /* Buscamos el espacio que coincida con la ID */
  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game) {
  /* Comprobamos que el juego exista */
  if (game == NULL) {
    return NO_ID;
  }
  return player_get_location(game->player);
}

Status game_set_player_location(Game *game, Id id) {
  /* Comprobamos validez de la ID y del juego */
  if (id == NO_ID || !game) {
    return ERROR;
  }

  return player_set_location(game->player, id);
}

Id game_get_object_location(Game *game) {
  int i;
  Id id;
  Space *space;

  /* Comprobamos que el juego exista */
  if (!game) {
    return NO_ID;
  }

  /* Recorremos todos los espacios buscando el objeto */
  for (i = 0; i < game->n_spaces; i++) {
    id = game_get_space_id_at(game, i);
    space = game_get_space(game, id);

    /* Si el espacio tiene un objeto válido, devolvemos su ID */
    if (space_get_object(space) != NO_ID) {
      return id;
    }
  }
  return NO_ID;
}

Status game_set_object_location(Game *game, Id id) {
  Id temp;

  /* Comprobamos que el juego exista */
  if (!game) {
    return ERROR;
  }

  /* Buscamos dónde está el objeto actualmente */
  temp = game_get_object_location(game);

  /* Si el objeto estaba en el mapa, lo quitamos de esa sala */
  if (temp != NO_ID) {
    if (space_set_object(game_get_space(game, temp), NO_ID) == ERROR) {
      return ERROR;
    }
  }

  /* Si la nueva ID es válida, colocamos el objeto en la nueva sala */
  if (id != NO_ID) {
    return space_set_object(game_get_space(game, id), object_get_id(game->object));
  }
  return OK;
}

Command *game_get_last_command(Game *game) {
  /* Comprobamos validez del puntero */
  if (!game) {
    return NULL;
  }
  return game->last_cmd;
}

Status game_set_last_command(Game *game, Command *command) {
  /* Comprobamos que tanto el juego como el comando existan */
  if (!game || !command) {
    return ERROR;
  }
  /* Guardamos el comando */
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) {
  /* Comprobamos validez del puntero */
  if (!game) {
    return FALSE;
  }
  return game->finished;
}

Status game_set_finished(Game *game, Bool finished) {
  /* Comprobamos validez del puntero */
  if (!game) {
    return ERROR;
  }
  /* Actualizamos el estado del juego */
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  /* Comprobamos si el juego es válido */
  if (!game) {
    printf("Ha ocurrido un problema a la hora de cargar el juego");
  } else {
    int i;
    printf("\n\n-------------\n\n");
    printf("=> Spaces: \n");

    /* Imprimimos todos los espacios cargados */
    for (i = 0; i < game->n_spaces; i++) {
      space_print(game->spaces[i]);
    }

    /* Imprimimos la información del jugador y del objeto */
    player_print(game->player);
    object_print(game->object);
  }
}

/**
   Implementación de funciones privadas
*/

Status game_add_space(Game *game, Space *space) {
  /* Comprobamos que el espacio sea válido y que no superemos el máximo */
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  /* Añadimos el espacio al array y sumamos uno al contador */
  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  /* Comprobamos que la posición sea válida y que el juego exista */
  if (position < 0 || position >= game->n_spaces || !game) {
    return NO_ID;
  }
  return space_get_id(game->spaces[position]);
}
