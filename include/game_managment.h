
#ifndef GAME_MANAGMENT_H
#define GAME_MANAGMENT_H

#include "game.h"

Status game_managment_save_game(Game *game, char *filename);
/**
 * @brief Carga el juego llamando a las funciones de carga
 * @author Unai
 * @param game Puntero al juego principal donde se añadirán los espacios.
 * @param filename Cadena de caracteres con el nombre del archivo.
 * @return OK si se carga correctamente, ERROR si hay algún fallo.
 */
Status game_managment_load(Game *game, char *filename);







#endif