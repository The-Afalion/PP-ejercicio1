/**
 * @brief Implementa el módulo de espacio
 *
 * @file space.c
 * @author Unai
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "space.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SINGLE_ELEM 1
#define FIRST_CHAR 0

/**
 * @brief Estructura de Espacio
 * Contiene la información de un área del juego, sus conexiones, 
 * objetos presentes, personajes y descripción gráfica.
 */
struct Space
{
  Id id;                                     /*!< Identificador del espacio */
  char name[WORD_SIZE + SINGLE_ELEM];        /*!< Nombre del espacio */
  Id north;                                  /*!< ID del espacio al norte */
  Id south;                                  /*!< ID del espacio al sur */
  Id east;                                   /*!< ID del espacio al este */
  Id west;                                   /*!< ID del espacio al oeste */
  Set *objects;                              /*!< Conjunto de objetos en el espacio */
  Id character;                              /*!< ID del personaje en el espacio */
  char gdesc[GDESC_ROWS][GDESC_COLS];        /*!< Descripción gráfica */
};

/**
 * @brief Crea un nuevo espacio e inicializa sus campos
 * @author Unai
 * @param id Identificador único para el nuevo espacio
 * @return Un nuevo espacio inicializado, o NULL en caso de error
 */
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
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create(NO_ID);
  newSpace->character = NO_ID;

  /* Inicialización de la descripción gráfica con espacios en blanco */
  for (i = 0; i < GDESC_ROWS; i++) {
    for (j = 0; j < GDESC_COLS - 1; j++) {
      newSpace->gdesc[i][j] = ' ';
    }
    newSpace->gdesc[i][GDESC_COLS - 1] = '\0';
  }

  return newSpace;
}

/**
 * @brief Destruye un espacio y libera la memoria de sus componentes
 * @author Unai
 * @param space Puntero al espacio que debe ser destruido
 * @return OK si tiene éxito, ERROR en caso contrario
 */
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

/**
 * @brief Obtiene el ID de un espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return El ID del espacio o NO_ID en caso de error
 */
Id space_get_id(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->id;
}

/**
 * @brief Establece el nombre de un espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param name Cadena con el nombre a asignar
 * @return OK si tiene éxito, ERROR en caso contrario
 */
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

/**
 * @brief Obtiene el nombre de un espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return Puntero a la cadena de nombre o NULL en caso de error
 */
const char *space_get_name(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return space->name;
}

/**
 * @brief Establece la conexión norte del espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del espacio al norte
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status space_set_north(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->north = id;
  return OK;
}

/**
 * @brief Obtiene el ID del espacio al norte
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del espacio al norte o NO_ID en caso de error
 */
Id space_get_north(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->north;
}

/**
 * @brief Establece la conexión sur del espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del espacio al sur
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status space_set_south(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->south = id;
  return OK;
}

/**
 * @brief Obtiene el ID del espacio al sur
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del espacio al sur o NO_ID en caso de error
 */
Id space_get_south(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->south;
}

/**
 * @brief Establece la conexión este del espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del espacio al este
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status space_set_east(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->east = id;
  return OK;
}

/**
 * @brief Obtiene el ID del espacio al este
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del espacio al este o NO_ID en caso de error
 */
Id space_get_east(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->east;
}

/**
 * @brief Establece la conexión oeste del espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del espacio al oeste
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status space_set_west(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->west = id;
  return OK;
}

/**
 * @brief Obtiene el ID del espacio al oeste
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del espacio al oeste o NO_ID en caso de error
 */
Id space_get_west(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->west;
}

/**
 * @brief Añade un objeto al conjunto de objetos del espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param object_id ID del objeto a añadir
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status space_add_object(Space *space, Id object_id)
{
  if (!space)
  {
    return ERROR;
  }
  return set_add(space->objects, object_id);
}

/**
 * @brief Elimina un objeto del conjunto de objetos del espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param object_id ID del objeto a eliminar
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status space_remove_object(Space *space, Id object_id)
{
  if (!space)
  {
    return ERROR;
  }
  return set_del(space->objects, object_id);
}

/**
 * @brief Obtiene el conjunto de objetos presentes en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return Array de IDs de objetos o NULL en caso de error
 */
Id* space_get_objects(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return set_get_ids(space->objects);
}

/**
 * @brief Obtiene el número de objetos que hay en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return El número de objetos o -1 en caso de error
 */
int space_get_number_of_objects(Space *space)
{
  if (!space)
  {
    return -1;
  }
  return set_get_numberid(space->objects);
}

/**
 * @brief Comprueba si un objeto determinado está en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del objeto a buscar
 * @return OK si el objeto existe, ERROR en caso contrario
 */
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

/**
 * @brief Establece el personaje que se encuentra en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del personaje a asignar
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status space_set_character(Space *space, Id id)
{
  if (!space)
  {
    return ERROR;
  }
  space->character = id;
  return OK;
}

/**
 * @brief Obtiene el personaje que se encuentra en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del personaje o NO_ID en caso de error
 */
Id space_get_character(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->character;
}

/**
 * @brief Establece la descripción gráfica de un espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param gdesc Matriz de caracteres con el nuevo arte gráfico
 * @return OK si tiene éxito, ERROR en caso contrario
 */
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

/**
 * @brief Obtiene la descripción gráfica de un espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return Puntero a la matriz de descripción gráfica o NULL en caso de error
 */
char (*space_get_gdesc(Space* space))[GDESC_COLS] {
  if (!space) {
    return NULL;
  }

  return space->gdesc;
}

/**
 * @brief Imprime la información del espacio por salida estándar
 * @author Unai
 * @param space Puntero al espacio a imprimir
 * @return OK si tiene éxito, ERROR en caso contrario
 */
Status space_print(Space *space)
{
  Id idaux = NO_ID;
  int i, num_objs;
  Id *objs = NULL;

  if (!space)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  fprintf(stdout, "---> North link: %ld.\n", idaux);

  idaux = space_get_south(space);
  fprintf(stdout, "---> South link: %ld.\n", idaux);

  idaux = space_get_east(space);
  fprintf(stdout, "---> East link: %ld.\n", idaux);

  idaux = space_get_west(space);
  fprintf(stdout, "---> West link: %ld.\n", idaux);

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

  return OK;
}