/**
 * @brief Implementa el módulo de jugador, gestionando sus datos y estado.
 * @file player.c
 * @author Unai y Rodrigo
 * @version 2.0
 * @date 12-03-2024
 * @copyright GNU Public License
 */

#include "player.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estructura de Jugador
 * Almacena la información de un jugador, incluyendo su ID, nombre, ubicación y el objeto que transporta.
 */
struct Player{
  Id id;                      /*!< Identificador único del jugador */
  char name[WORD_SIZE + 1];   /*!< Nombre del jugador */
  Id location;                /*!< ID del espacio donde se encuentra el jugador */
  Id object;                  /*!< ID del objeto que transporta el jugador */
};

/**
 * @brief Crea un nuevo jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param id El identificador para el nuevo jugador.
 * @return Un puntero al jugador recién creado, o NULL si ocurre un error.
 */
Player* player_create(Id id) {
  Player* newPlayer = NULL;

  if (id == NO_ID) {
    return NULL;
  }

  newPlayer = (Player*)calloc(1, sizeof(Player));
  if (newPlayer == NULL) {
    return NULL;
  }

  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->object = NO_ID;

  return newPlayer;
}

/**
 * @brief Destruye un jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param player Un puntero al jugador a destruir.
 * @return OK si el jugador se destruyó correctamente, o ERROR en caso contrario.
 */
Status player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  free(player);
  return OK;
}

/**
 * @brief Obtiene el ID de un jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param player Un puntero al jugador.
 * @return El ID del jugador, o NO_ID si el puntero es nulo.
 */
Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

/**
 * @brief Establece el nombre de un jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param player Un puntero al jugador.
 * @param name El nuevo nombre para el jugador.
 * @return OK si el nombre se estableció correctamente, o ERROR en caso contrario.
 */
Status player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (strcpy(player->name, name) == NULL) {
    return ERROR;
  }
  return OK;
}

/**
 * @brief Obtiene el nombre de un jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param player Un puntero al jugador.
 * @return El nombre del jugador, o NULL si el puntero es nulo.
 */
const char* player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

/**
 * @brief Establece la ubicación de un jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param player Un puntero al jugador.
 * @param location El ID del nuevo espacio de ubicación.
 * @return OK si la ubicación se estableció correctamente, o ERROR en caso contrario.
 */
Status player_set_location(Player* player, Id location) {
  if (!player) {
    return ERROR;
  }
  player->location = location;
  return OK;
}

/**
 * @brief Obtiene la ubicación de un jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param player Un puntero al jugador.
 * @return El ID del espacio donde se encuentra el jugador, o NO_ID si el puntero es nulo.
 */
Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

/**
 * @brief Asigna un objeto a un jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param player Un puntero al jugador.
 * @param object El ID del objeto a asignar.
 * @return OK si el objeto se asignó correctamente, o ERROR en caso contrario.
 */
Status player_set_object(Player* player, Id object) {
  if (!player) {
    return ERROR;
  }
  player->object = object;
  return OK;
}

/**
 * @brief Obtiene el objeto que transporta un jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param player Un puntero al jugador.
 * @return El ID del objeto que transporta el jugador, o NO_ID si el puntero es nulo.
 */
Id player_get_object(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->object;
}

/**
 * @brief Imprime la información de un jugador.
 * @author Unai y Rodrigo
 * @date 12-03-2024
 * @param player Un puntero al jugador a imprimir.
 * @return OK si la información se imprimió correctamente, o ERROR en caso contrario.
 */
Status player_print(Player* player) {
  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Jugador (Id: %ld; Nombre: %s)\n", player->id, player->name);
  fprintf(stdout, "--> Localización: %ld\n", player->location);
  fprintf(stdout, "--> Objeto: %ld\n", player->object);

  return OK;
}
