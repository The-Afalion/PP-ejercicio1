/**
 * @brief Define la interfaz principal del juego
 *
 * @file game.h
 * @author Unai
 * @version 2.0
 * @date 15-03-2026
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
 * @brief Obtiene la ubicación actual de un objeto concreto.
 * @author Unai
 * @param game Puntero al juego.
 * @param object_id ID del objeto a buscar.
 * @return ID del espacio donde está el objeto, o NO_ID si lo tiene el jugador o hay error.
 */
Id game_get_object_location(Game *game, Id object_id);

/**
 * @brief Establece la ubicación física de un objeto en el mapa.
 * @author Unai
 * @param game Puntero al juego.
 * @param space_id ID del espacio destino (o NO_ID para quitarlo del mapa).
 * @param object_id ID del objeto a mover.
 * @return OK si tiene éxito, ERROR en caso contrario.
 */
Status game_set_object_location(Game *game, Id space_id, Id object_id);

/**
 * @brief Obtiene la ubicación actual de un personaje concreto.
 * @author Unai
 * @param game Puntero al juego.
 * @param character_id ID del personaje a buscar.
 * @return ID del espacio donde está el personaje, o NO_ID si hay error.
 */
Id game_get_character_location(Game *game, Id character_id);

/**
 * @brief Establece la ubicación física de un personaje en el mapa.
 * @author Unai
 * @param game Puntero al juego.
 * @param space_id ID del espacio destino.
 * @param character_id ID del personaje a mover.
 * @return OK si tiene éxito, ERROR en caso contrario.
 */
Status game_set_character_location(Game *game, Id space_id, Id character_id);

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
 * @brief Obtiene el puntero a un objeto específico.
 * @author Unai
 * @param game Puntero al juego.
 * @param id ID del objeto buscado.
 * @return Puntero al objeto, o NULL si no se encuentra.
 */
Object* game_get_object(Game* game, Id id);

/**
 * @brief Obtiene el puntero a un personaje específico.
 * @author Unai
 * @param game Puntero al juego.
 * @param id ID del personaje buscado.
 * @return Puntero al personaje, o NULL si no se encuentra.
 */
Character* game_get_character(Game* game, Id id);

/**
 * @brief Añade un nuevo objeto a la lista general del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @param obj Puntero al objeto a añadir.
 * @return OK si se añade con éxito, ERROR si no hay espacio o hay fallo.
 */
Status game_add_object(Game *game, Object *obj);

/**
 * @brief Añade un nuevo personaje a la lista general del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @param character Puntero al personaje a añadir.
 * @return OK si se añade con éxito, ERROR si no hay espacio o hay fallo.
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief Establece el mensaje de chat actual.
 * @author Unai
 * @param game Puntero al juego.
 * @param message Mensaje a establecer.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status game_set_chat_message(Game *game, char *message);

/**
 * @brief Obtiene el mensaje de chat actual.
 * @author Unai
 * @param game Puntero al juego.
 * @return Cadena con el mensaje de chat.
 */
char *game_get_chat_message(Game *game);

#endif