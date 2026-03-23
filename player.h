/**
 * @brief Define la interfaz del módulo de jugador
 *
 * @file player.h
 * @author Unai
 * @version 1.0
 * @date 15-03-2026
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
 * @return una cadena con el nombre del jugador o NULL en caso de error
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
 * @param object el id del objeto que se añade al inventario del jugador
 * @return OK si todo ha ido bien, o ERROR si ha habido algún problema
 */
Status player_set_object(Player* player, Id object);

/**
 * @brief Obtiene el id de un objeto del inventario del jugador
 * @author Unai
 * @param player puntero al jugador
 * @param index posición del objeto en el inventario
 * @return el id del objeto que posee en ese índice O NO_ID si hay algun error
 */
Id player_get_object(Player* player, int index);

/**
 * @brief Elimina el objeto del inventario del jugador
 * @author Unai
 * @param player puntero al jugador
 * @param object el id del objeto a eliminar
 * @return OK si el objeto fue eliminado, ERROR si no se encontró o en caso de error
 */
Status player_del_object(Player *player, Id object);

/**
 * @brief Verifica si el jugador posee un objeto específico en su inventario
 * @author Unai
 * @param player puntero al jugador
 * @param object el id del objeto a verificar
 * @return TRUE si el jugador tiene el objeto, FALSE si no lo tiene o en caso de error
 */
BOOL player_has_object(Player *player, Id object);

/**
 * @brief Imprime la información del jugador por pantalla (id, nombre, localización, objeto, etc.)
 * @author Unai
 * @param player puntero al jugador
 * @return OK si todo ha ido bien, o ERROR si ha habido algún problema
 */
Status player_print(Player* player);

/**
 * @brief Establece los puntos de salud del jugador
 * @author Unai
 * @param player puntero al jugador
 * @param h valor entero que representa la salud
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status player_set_heatlh(Player *player, int h);

/**
 * @brief Obtiene los puntos de salud actuales del jugador
 * @author Unai
 * @param player puntero al jugador
 * @return un entero con el valor de salud o -1 en caso de error
 */
int player_get_health(Player* player);

/**
 * @brief Establece la descripción gráfica (gdesc) del jugador
 * @author Unai
 * @param player puntero al jugador
 * @param des cadena con la descripción gráfica
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status player_set_gdesc(Player* player, char* des);

/**
 * @brief Obtiene la descripción gráfica (gdesc) del jugador
 * @author Unai
 * @param player puntero al jugador
 * @return puntero a la cadena de texto de la descripción o NULL en caso de error
 */
char* player_get_gdesc(Player* player);

#endif
