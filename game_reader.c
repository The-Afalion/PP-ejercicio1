/**
 * @brief Implementa la carga de datos del juego desde un fichero.
 * @file game_reader.c
 * @author Rodrigo & Unai
 * @version 2.0
 * @date 12-03-2024
 * @copyright GNU Public License
 */

#include "game_reader.h"
#include "game.h"
#include "space.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Carga los espacios del juego desde un fichero de datos.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Puntero a la estructura del juego donde se cargarán los espacios.
 * @param filename Nombre del fichero de datos a leer.
 * @return OK si la carga se realiza correctamente, ERROR en caso contrario.
 */
Status game_reader_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;

  /* Control de errores de entrada */
  if (!filename || !game) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  /* Lectura del fichero línea por línea */
  while (fgets(line, WORD_SIZE, file)) {
    /* Buscamos líneas que definen un espacio (comienzan con "#s:") */
    if (strncmp("#s:", line, 3) == 0) {
      /* Parseo de la línea para obtener los datos del espacio */
      toks = strtok(line + 3, "|");
      if (toks) id = atol(toks);
      toks = strtok(NULL, "|");
      if (toks) strcpy(name, toks);
      toks = strtok(NULL, "|");
      if (toks) north = atol(toks);
      toks = strtok(NULL, "|");
      if (toks) east = atol(toks);
      toks = strtok(NULL, "|");
      if (toks) south = atol(toks);
      toks = strtok(NULL, "|");
      if (toks) west = atol(toks);

      /* Creación y configuración del espacio */
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_add_space(game, space);
      }
    }
  }

  /* Comprobación de errores de lectura en el fichero */
  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}
