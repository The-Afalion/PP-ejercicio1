/**
 * @brief Implementa el módulo de espacio
 *
 * @file space.c
 * @author Unai
 * @version 3.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SINGLE_ELEM 1
#define FIRST_CHAR 0
#define MAX_SPACES 100
#define MAX_LINKS 4

/**
 * @brief Estructura de Espacio
 * Contiene la información de un área del juego, sus conexiones, 
 * objetos presentes, personajes y descripción gráfica.
 */
struct Space
{
  Id id;                                     /*!< Identificador del espacio */
  char name[WORD_SIZE + SINGLE_ELEM];        /*!< Nombre del espacio */
  Set *objects;                              /*!< Conjunto de objetos en el espacio */
  Id character;                              /*!< ID del personaje en el espacio */
  char gdesc[GDESC_ROWS][GDESC_COLS];        /*!< Descripción gráfica */
  BOOL discovered;                           /*!< Indica si el espacio ha sido descubierto */
};

Space *space_create(Id id)
{
  Space *newSpace = NULL;
  int i, j;

  if (id == NO_ID)
  {
    return NULL;
  }

  newSpace = (Space *)calloc(SINGLE_ELEM, sizeof(Space));

  if (newSpace == NULL)
  {
    return NULL;
  }

  newSpace->id = id;
  newSpace->name[FIRST_CHAR] = '\0';
  newSpace->objects = set_create(NO_ID);
  newSpace->character = NO_ID;
  newSpace->discovered = FALSE;


  /* Inicialización de la descripción gráfica con espacios en blanco */
  for (i = 0; i < GDESC_ROWS; i++) {
    for (j = 0; j < GDESC_COLS - 1; j++) {
      newSpace->gdesc[i][j] = ' ';
    }
    newSpace->gdesc[i][GDESC_COLS - 1] = '\0';
  }

  return newSpace;
}

Status space_destroy(Space *space)
{
  if (!space)
  {
    return ERROR;
  }

  if (space->objects)
  {
    set_destroy(space->objects);
  }

  free(space);
  return OK;
}

Id space_get_id(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space *space, char *name)
{
  if (!space || !name)
  {
    return ERROR;
  }

  if (!strcpy(space->name, name))
  {
    return ERROR;
  }
  return OK;
}

const char *space_get_name(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return space->name;
}

/* -------------------------------------------------------------------
 * Nuevas funciones de gestión de Links
 * ------------------------------------------------------------------- */

Status space_add_object(Space *space, Id object_id)
{
  if (!space)
  {
    return ERROR;
  }
  return set_add(space->objects, object_id);
}

Status space_remove_object(Space *space, Id object_id)
{
  if (!space)
  {
    return ERROR;
  }
  return set_del(space->objects, object_id);
}

Id* space_get_objects(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return set_get_ids(space->objects);
}

int space_get_number_of_objects(Space *space)
{
  if (!space)
  {
    return -1;
  }
  return set_get_numberid(space->objects);
}

Status space_contains_object(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  if (set_find(space->objects, id) == OK)
  {
    return OK;
  }
  return ERROR;
}

Status space_set_character(Space *space, Id id)
{
  if (!space)
  {
    return ERROR;
  }
  space->character = id;
  return OK;
}

Id space_get_character(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->character;
}

Status space_set_gdesc(Space* space, char gdesc[GDESC_ROWS][GDESC_COLS]) {
  int i;

  if (!space || !gdesc) {
    return ERROR;
  }

  for (i = 0; i < GDESC_ROWS; i++) {
    if (strlen(gdesc[i]) == GDESC_COLS - 1) {
     if( !strcpy(space->gdesc[i],gdesc[i])){
      return ERROR;
     }
    } else {
      strcpy(space->gdesc[i], "         ");
    }
  }

  return OK;
}

char (*space_get_gdesc(Space* space))[GDESC_COLS] {
  if (!space) {
    return NULL;
  }

  return space->gdesc;
}

Status space_set_discovered(Space* space, BOOL discovered)
{
  if (!space)
  {
    return ERROR;
  }
  space->discovered = discovered;
  return OK;
}

BOOL space_get_discovered(Space* space)
{
  if (!space)
  {
    return FALSE;
  }
  return space->discovered;
}

Status space_print(Space *space)
{
  int i, num_objs;
  Id *objs = NULL;

  if (!space)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  if (space->discovered == TRUE) {
    fprintf(stdout, "---> Character in space: %ld.\n", space->character);

    fprintf(stdout, "---> Graphic description:\n");
    for (i = 0; i < GDESC_ROWS; i++) {
      fprintf(stdout, "%s\n", space->gdesc[i]);
    }

    num_objs = space_get_number_of_objects(space);
    if (num_objs > 0)
    {
      objs = space_get_objects(space);
      fprintf(stdout, "---> Objects in the space (Id: ");
      for (i = 0; i < num_objs; i++)
      {
        fprintf(stdout, "%d ", (int) objs[i]);
      }
      fprintf(stdout, ")\n");

      if (objs)
      {
        free(objs);
      }
    }
    else
    {
      fprintf(stdout, "---> No object in the space.\n");
    }
  }

  return OK;
}