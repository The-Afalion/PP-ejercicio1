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
#include "link.h"
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
 * @brief Estructura de datos para la interfaz de cada jugador
 */
typedef struct _InterfaceData InterfaceData;
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
Status game_get_last_command_status(Game *game);
Status game_set_last_command_status(Game *game, Status status);

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
 * @brief Obtiene el estado del último comando ejecutado.
 * @author Unai
 * @param game Puntero al juego.
 * @return Estado del último comando.
 */
Status game_get_last_command_status(Game *game);

/**
 * @brief Establece el estado del último comando ejecutado.
 * @author Unai
 * @param game Puntero al juego.
 * @param status Estado a establecer.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status game_set_last_command_status(Game *game, Status status);

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
 * @brief Establece el puntero al jugador.
 * @author Unai
 * @param game Puntero al juego.
 * @param player Puntero al jugador a establecer.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status game_set_player(Game *game, Player *player);

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

/**
 * @brief Obtiene el ID del espacio conectado a un espacio dado en una dirección específica.
 * @author Unai
 * @param game Puntero al juego.
 * @param space_id ID del espacio de partida.
 * @param dir Dirección de la conexión.
 * @return ID del espacio conectado, o NO_ID si no hay conexión.
 */
Id game_get_connection(Game *game, Id space_id, Directions dir);

/**
 * @brief Comprueba si la conexión en una dirección desde un espacio dado está abierta.
 * @author Unai
 * @param game Puntero al juego.
 * @param space_id ID del espacio de partida.
 * @param dir Dirección de la conexión.
 * @return TRUE si la conexión está abierta, FALSE si está cerrada o hay error.
 */
BOOL game_connection_is_open(Game *game, Id space_id, Directions dir);

/**
 * @brief Añade un nuevo enlace a la lista general del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @param link Puntero al enlace a añadir.
 * @return OK si se añade con éxito, ERROR si no hay espacio o hay fallo.
  */
Link* game_get_link(Game* game, Id link_id);
/**
 * @brief Obtiene el número de enlaces actualmente cargados en el juego.
 * @author Unai
 * @param game Puntero al juego.
 * @return Número de enlaces, o -1 si hay error.
 */
int game_get_number_of_links(Game *game);
/**
 * @brief Añade un nuevo enlace al juego.
 * @author Unai
 * @param game Puntero al juego.
 * @param link Puntero al enlace a añadir.
 * @return OK si se añade con éxito, ERROR si no hay espacio o hay fallo.
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief Obtiene el turno actual del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @return Número del turno actual, o -1 si hay error.
 */
int game_get_turn(Game *game);

/**
 * @brief Avanza al siguiente turno del juego.
 * @author Unai
 * @param game Puntero al juego.
 * @return Número del nuevo turno, o -1 si hay error.
 */
int game_next_turn(Game *game);
/**
 * @brief Establece la descripción de un objeto para su inspección.
 * @author Alejandro Dominguez
 * @param game Puntero al juego.
 * @param inspection Descripción a establecer.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status game_set_object_desc(Game *game,const char *inspection);
/**
 * @brief Obtiene la descripción del objeto para su inspección.
 * @author Alejandro Dominguez
 * @param game Puntero al juego.
 * @return Cadena con la descripción del objeto.
 */
char *game_get_object_desc(Game *game);

#endif