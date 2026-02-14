#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/* Carga los espacios desde un fichero de texto */
Status game_reader_load_spaces(Game *game, char *filename);

#endif