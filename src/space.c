/**
 * @brief Implementa el módulo de espacios
 *
 * @file space.c
 * @author Unai
 * @version 3.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "space.h"
#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SINGLE_ELEM 1
#define FIRST_CHAR 0
#define MAX_SPACES 100
#define MAX_LINKS 4

/**
 * @brief Space
 * Estructura de datos que representa un espacio en el juego.
 */
struct Space
{
  Id id;                              /*!< identificador de espacio*/
  char name[WORD_SIZE + SINGLE_ELEM]; /*!< nombre del espacio*/
  Set *objects;                       /*!< conjunto de los id de los objetos que contiene*/
  Set *characters;                   /*!< conjunto de los id de los caracteres*/
  char gdesc[GDESC_ROWS][GDESC_COLS]; /*!< Lo que hay que pintar el espacio*/
  BOOL discovered;                    /*!< Si esta descubierto o no*/
};

Space *space_create(Id id)
{
  Space *newSpace = NULL;
  int i, j;

  /* Si nos pasan una ID inválida */
  if (id == NO_ID)
  {
    return NULL;
  }

  newSpace = (Space *)calloc(SINGLE_ELEM, sizeof(Space));

  /* ccomprobacion por si es null  */
  if (newSpace == NULL)
  {
    return NULL;
  }

  /* Rellenamos los datos básicos */
  newSpace->id = id;
  newSpace->name[FIRST_CHAR] = '\0';
  newSpace->objects = set_create();
  newSpace->characters = set_create();
  newSpace->discovered = FALSE;

  /* Limpiamos el dibujo del espacio dejándolo en blanco para empezar de cero */
  for (i = 0; i < GDESC_ROWS; i++)
  {
    for (j = 0; j < GDESC_COLS - 1; j++)
    {
      newSpace->gdesc[i][j] = ' ';
    }
    newSpace->gdesc[i][GDESC_COLS - 1] = '\0';
  }

  return newSpace;
}

Status space_destroy(Space *space)
{
  /* Si nos pasan un espacio NULL */
  if (!space)
  {
    return ERROR;
  }

  if (space->objects)
  {
    set_destroy(space->objects);
  }

  if (space->characters)
  {
    set_destroy(space->characters);
  }

  /*Liberamos el espacio*/
  free(space);
  return OK;
}

Id space_get_id(Space *space)
{
  /* Comprueba si la sala existe y te devuelve su ID */
  if (!space)
  {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space *space, char *name)
{
  /* Nos aseguramos de que ni la sala ni el nombre que le queremos poner NULL */
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
  /* Comprobamos si es NULL y devolvemos nombre*/
  if (!space)
  {
    return NULL;
  }
  return space->name;
}

Status space_add_object(Space *space, Id object_id)
{
  /* Revisa que haya sala y mete el objeto  */
  if (!space)
  {
    return ERROR;
  }
  return set_add(space->objects, object_id);
}

Status space_remove_object(Space *space, Id object_id)
{
  /* Si la sala existe, busca el objeto y lo borra de ahí */
  if (!space)
  {
    return ERROR;
  }
  return set_del(space->objects, object_id);
}

Id *space_get_objects(Space *space)
{
  /* Te devuelve la lista entera con las IDs  */
  if (!space)
  {
    return NULL;
  }
  return set_get_ids(space->objects);
}

int space_get_number_of_objects(Space *space)
{
  /* Cuenta cuántos objetos hay  */
  if (!space)
  {
    return -1;
  }
  return set_get_numberid(space->objects);
}

Status space_contains_object(Space *space, Id id)
{
  /* Revisa si un objeto  está en el espacio */
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
  /* Mete a un personaje en el espacio */
  if (!space)
  {
    return ERROR;
  }
  if (set_add(space->characters, id) == ERROR)
  {
    return ERROR;
  }
  return OK;
}

Status space_remove_character(Space *space, Id id)
{
  /* Elimina a un personaje del espacio */
  if (!space)
  {
    return ERROR;
  }

  return set_del(space->characters, id);
}

Id space_get_character(Space *space, int index)
{
  /* devuelve id del personaje de la sala o NO_ID si no hay*/
  if (!space || index < 0 || index >= set_get_numberid(space->characters))
  {
    return NO_ID;
  }
  return set_get_id(space->characters, index);
}

Status space_set_gdesc(Space *space, char gdesc[GDESC_ROWS][GDESC_COLS])
{
  int i;

  /* Comprueba que todo no sea NULL */
  if (!space || !gdesc)
  {
    return ERROR;
  }

  /* Copia el dibujo ASCII de la sala línea por línea */
  for (i = 0; i < GDESC_ROWS; i++)
  {
    strncpy(space->gdesc[i], gdesc[i], GDESC_COLS - 1);
    space->gdesc[i][GDESC_COLS - 1] = '\0'; /* Aseguramos que la línea termine bien */
  }

  return OK;
}

char (*space_get_gdesc(Space *space)) [GDESC_COLS]
{
  /* Te devuelve el dibujo del espacio */
  if (!space)
  {
    return NULL;
  }

  return space->gdesc;
}

Status space_set_discovered(Space *space, BOOL discovered)
{
  /* la marca como visitado o no el espacio */
  if (!space)
  {
    return ERROR;
  }
  space->discovered = discovered;
  return OK;
}

BOOL space_get_discovered(Space *space)
{
  /* Comprueba el estado del espacio */
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

  /* Solo imprimimos los detalles internos si la sala ya fue descubierta */
  if (space->discovered == TRUE)
  {
    fprintf(stdout, "---> Characters in space: ");
    set_print(space->characters);
    fprintf(stdout, "\n");


   

    fprintf(stdout, "---> Graphic description:\n");
    for (i = 0; i < GDESC_ROWS; i++)
    {
      fprintf(stdout, "%s\n", space->gdesc[i]);
    }

    /* Vemos cuántos objetos hay y los listamos uno a uno */
    num_objs = space_get_number_of_objects(space);
    if (num_objs > 0)
    {
      objs = space_get_objects(space);
      fprintf(stdout, "---> Objects in the space (Id: ");
      for (i = 0; i < num_objs; i++)
      {
        fprintf(stdout, "%d ", (int)objs[i]);
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

int space_get_n_characters(Space *space)
{
  if (!space)
  {
    return -1;
  }
  return set_get_numberid(space->characters);
}
