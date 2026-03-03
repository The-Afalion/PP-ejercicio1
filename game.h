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
#include "character.h"
#include "types.h"

/** @brief Número máximo de espacios en el juego */
#define MAX_SPACES 100
#define MAX_OBJECTS 100

/**
 * @brief Estructura principal de Game (opaca)
 */
typedef struct _Game Game;

/**
 * @brief Inicializa las variables del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @return OK si se inicializa con éxito, ERROR en caso contrario.
 */
Status game_create(Game **game);

/**
 * @brief Crea el juego y carga el mapa desde un archivo.
 * @author Unai
 * @param game Puntero al juego.
 * @param filename Nombre del archivo a leer.
 * @return OK si tiene éxito, ERROR en caso contrario.
 */
Status game_create_from_file(Game **game, char *filename);

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
 * @brief Añade un nuevo objeto al array del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @param object Puntero al objeto a añadir.
 * @return OK si se añade con éxito, ERROR si no cabe o falla.
 */
Status game_add_object(Game *game, Object *object);

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
 * @return 1 si ha terminado, 0 si sigue activo.
 */
int game_get_finished(Game *game);

/**
 * @brief Modifica el estado de finalización del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @param finished 1 para terminar, 0 para continuar.
 * @return OK si se cambia con éxito, ERROR en caso contrario.
 */
Status game_set_finished(Game *game, int finished);

/**
 * @brief Imprime por pantalla el estado actual del juego (Depuración).
 * @author Unai
 * @param game Puntero al juego.
 */
void game_print(Game *game);

/**
 * @brief Obtiene el puntero al jugador.
 * @author Unai
 * @param game Puntero al juego.
 * @return Puntero al jugador.
 */
Player* game_get_player(Game* game);

/**
 * @brief Obtiene el puntero al objeto.
 * @author Unai
 * @param game Puntero al juego.
 * @return Puntero al objeto.
 */
Object* game_get_object(Game* game);

/**
 * @brief Obtiene el puntero al personaje.
 * @author Unai
 * @param game Puntero al juego.
 * @return Puntero al personaje.
 */
Character* game_get_character(Game* game);


#endif
