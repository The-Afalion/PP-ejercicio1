/**
 * @brief Define la interfaz principal del juego
 *
 * @file game.h
 * @author Unai
 * @version 1.0
 * @date 15-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "types.h"

/** @brief Número máximo de espacios en el juego */
#define MAX_SPACES 100

/**
 * @brief Estructura principal de Game
 * Almacena todo el estado del juego.
 */
typedef struct _Game {
  Player* player;           /*!< Puntero al jugador */
  Object* object;           /*!< Puntero al objeto principal */
  Space *spaces[MAX_SPACES];/*!< Array de punteros a los espacios del mapa */
  int n_spaces;             /*!< Número actual de espacios cargados */
  Command *last_cmd;        /*!< Puntero al último comando ejecutado */
  Bool finished;            /*!< Indica si el juego ha terminado  */
} Game;

/**
 * @brief Inicializa las variables del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @return OK si se inicializa con éxito, ERROR en caso contrario.
 */
Status game_create(Game *game);

/**
 * @brief Crea el juego y carga el mapa desde un archivo.
 * @author Unai
 * @param game Puntero al juego.
 * @param filename Nombre del archivo a leer.
 * @return OK si tiene éxito, ERROR en caso contrario.
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief Libera toda la memoria reservada por el juego.
 * @author Unai
 * @param game Puntero al juego.
 * @return OK si se destruye con éxito, ERROR en caso contrario.
 */
Status game_destroy(Game *game);

/**
 * @brief Añade un nuevo espacio al array del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @param space Puntero al espacio a añadir.
 * @return OK si se añade con éxito, ERROR si no cabe o falla.
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief Busca un espacio en el juego por su ID.
 * @author Unai
 * @param game Puntero al juego.
 * @param id ID del espacio a buscar.
 * @return Puntero al espacio encontrado, o NULL si no existe.
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief Obtiene la ubicación actual del jugador.
 * @author Unai
 * @param game Puntero al juego.
 * @return ID del espacio donde está el jugador, o NO_ID si hay error.
 */
Id game_get_player_location(Game *game);

/**
 * @brief Establece la ubicación del jugador.
 * @author Unai
 * @param game Puntero al juego.
 * @param id ID del nuevo espacio.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief Obtiene la ubicación actual del objeto.
 * @author Unai
 * @param game Puntero al juego.
 * @return ID del espacio donde está el objeto, o NO_ID si lo tiene el jugador o hay error.
 */
Id game_get_object_location(Game *game);

/**
 * @brief Establece la ubicación física del objeto en el mapa.
 * @author Unai
 * @param game Puntero al juego.
 * @param id ID del espacio destino (o NO_ID para quitarlo del mapa).
 * @return OK si tiene éxito, ERROR en caso contrario.
 */
Status game_set_object_location(Game *game, Id id);

/**
 * @brief Obtiene el último comando ejecutado.
 * @author Unai
 * @param game Puntero al juego.
 * @return Puntero al último comando, o NULL si hay error.
 */
Command* game_get_last_command(Game *game);

/**
 * @brief Guarda el último comando introducido.
 * @author Unai
 * @param game Puntero al juego.
 * @param command Puntero al comando a guardar.
 * @return OK si se guarda con éxito, ERROR en caso contrario.
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief Comprueba si el juego ha terminado.
 * @author Unai
 * @param game Puntero al juego.
 * @return TRUE si ha terminado, FALSE si sigue activo.
 */
Bool game_get_finished(Game *game);

/**
 * @brief Modifica el estado de finalización del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @param finished TRUE para terminar, FALSE para continuar.
 * @return OK si se cambia con éxito, ERROR en caso contrario.
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Imprime por pantalla el estado actual del juego (Depuración).
 * @author Unai
 * @param game Puntero al juego.
 */
void game_print(Game *game);

#endif