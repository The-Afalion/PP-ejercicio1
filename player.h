/**
 * @brief Define la interfaz del módulo de jugador
 *
 * @file player.h
 * @author Unai
 * @version 1.0
 * @date 08-02-2026
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

/**
 * @brief Estructura de Jugador (implementación oculta en player.c)
 */
typedef struct Player Player;

/**
 * @brief Crea un nuevo jugador, reservando memoria dinámica e inicializando sus miembros
 * @author Unai
 *
 * @param id el número de identificación para el nuevo jugador
 * @return un nuevo jugador inicializado, o NULL en caso de error
 */
Player* player_create(Id id);

/**
 * @brief Destruye un jugador, liberando la memoria previamente reservada
 * @author Unai
 *
 * @param player puntero al jugador que debe ser destruido
 * @return OK si todo ha ido bien, o ERROR si ha habido algún problema
 */
Status player_destroy(Player* player);

/**
 * @brief Obtiene el id de un jugador
 * @author Unai
 *
 * @param player puntero al jugador
 * @return el id del jugador o NO_ID en caso de error
 */
Id player_get_id(Player* player);

/**
 * @brief Establece el nombre de un jugador
 * @author Unai
 * @param player puntero al jugador
 * @param name cadena con el nombre a asignar
 * @return OK si todo ha ido bien, o ERROR si ha habido algún problema
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief Obtiene el nombre de un jugador
 * @author Unai
 * @param player puntero al jugador
 * @return una cadena con el nombre del jugador
 * @return NULL en caso de error
 */
const char* player_get_name(Player* player);

/**
 * @brief Establece la localización (espacio) donde se encuentra el jugador
 * @author Unai
 * @param player puntero al jugador
 * @param location el id del espacio donde se ubicará
 * @return OK si todo ha ido bien, o ERROR si ha habido algún problema
 */
Status player_set_location(Player* player, Id location);

/**
 * @brief Obtiene la localización actual del jugador
 * @author Unai
 * @param player puntero al jugador
 * @return el id de la ubicación actual o NO_ID en caso de error
 */
Id player_get_location(Player* player);

/**
 * @brief Asigna un objeto al inventario del jugador
 * @author Unai
 * @param player puntero al jugador
 * @param object el id del objeto que el jugador llevará
 * @return OK si todo ha ido bien, o ERROR si ha habido algún problema
 */
Status player_set_object(Player* player, Id object);

/**
 * @brief Obtiene el objeto que tiene el jugador
 * @author Unai
 * @param player puntero al jugador
 * @return el id del objeto que posee o NO_ID si no tiene ninguno
 */
Id player_get_object(Player* player);

/**
 * @brief Imprime la información del jugador por pantalla,muestra el id, el nombre, la localización y el objeto que posee.
 * @author Unai
 * @param player puntero al jugador
 * @return OK si todo ha ido bien, o ERROR si ha habido algún problema
 */
Status player_print(Player* player);

#endif
