/**
 * @brief Define la interfaz de lectura de datos del juego
 *
 * @file game_reader.h
 * @author Unai y Rodrigo
 * @version 1.0
 * @date 15-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief Carga los espacios del mapa desde un archivo de texto.
 * @author Unai y Rodrigo
 * @param game Puntero al juego principal donde se añadirán los espacios.
 * @param filename Cadena de caracteres con el nombre del archivo.
 * @return OK si se lee correctamente, ERROR si hay algún fallo.
 */
Status game_reader_load_spaces(Game *game, char *filename);

#endif