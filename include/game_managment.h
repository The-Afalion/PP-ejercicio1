
#ifndef GAME_MANAGMENT_H
#define GAME_MANAGMENT_H

#include "game.h"

/**
 * @brief Carga los enlaces desde un archivo de texto.
 * @author Unai
 * @param game Puntero al juego principal donde se añadirán los enlaces.
 * @param filename Cadena de caracteres con el nombre del archivo.
 * @return OK si se lee correctamente, ERROR si hay algún fallo.
 */

Status game_managment_load_links(Game *game, char *filename);
/**
 * @brief Carga los jugadores desde un archivo de texto.
 * @author Unai
 * @param game Puntero al juego principal donde se añadirá el jugador.
 * @param filename Cadena de caracteres con el nombre del archivo.
 * @return OK si se lee correctamente, ERROR si hay algún fallo.
 */
Status game_managment_load_players(Game *game, char *filename);
/**
 * @brief Carga los personajes desde un archivo de texto.
 * @author Unai
 * @param game Puntero al juego principal donde se añadirán los personajes.
 * @param filename Cadena de caracteres con el nombre del archivo.
 * @return OK si se lee correctamente, ERROR si hay algún fallo.
 */
Status game_managment_load_characters(Game *game, char *filename);
/**
 * @brief Carga los objetos desde un archivo de texto.
 * @author Unai
 * @param game Puntero al juego principal donde se añadirán los objetos.
 * @param filename Cadena de caracteres con el nombre del archivo.
 * @return OK si se lee correctamente, ERROR si hay algún fallo.
 */
Status game_managment_load_objects(Game *game, char *filename);
/**
 * @brief Carga los espacios del mapa desde un archivo de texto.
 * @author Unai
 * @param game Puntero al juego principal donde se añadirán los espacios.
 * @param filename Cadena de caracteres con el nombre del archivo.
 * @return OK si se lee correctamente, ERROR si hay algún fallo.
 */
Status game_managment_load_spaces(Game *game, char *filename);
Status game_managment_save_game(Game *game, char *filename);








#endif