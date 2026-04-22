/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Rodrigo
 * @version 1.0
 * @date 15-02-2026
 */

#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SINGLE_ELEM 1
#define FIRST_CHAR 0

/**
 * @brief Object
 * Estructura de datos que representa un objeto.
 */
struct Object
{
  Id id;                                     /*!< La ID del objeto */
  char name[WORD_SIZE + SINGLE_ELEM];        /*!< Nombre del objeto */
  char description[WORD_SIZE + SINGLE_ELEM]; /*!< Descripcion del objeto*/
  int health;                                /*!<vida queaporta o quita*/
  BOOL movable;                              /*!<Si se puede mover o no*/
  Id dependency;                             /*!<Indica el id del que depende*/
  Id open;                                   /*!<Indica el id de lo que puede abrir*/
};

Object *object_create(Id id)
{
  Object *newObject = NULL;

  /* Comprobamos si la ID enviada es válida */
  if (id == NO_ID)
  {
    return NULL;
  }

  /* Reservamos memoria dinámica */
  newObject = (Object *)calloc(SINGLE_ELEM, sizeof(Object));

  /* Control de error de memoria */
  if (newObject == NULL)
  {
    return NULL;
  }

  /* Inicializamos los campos del objeto nuevo */
  newObject->id = id;
  newObject->name[FIRST_CHAR] = '\0';
  newObject->description[FIRST_CHAR] = '\0';
  newObject->dependency = NO_ID;
  newObject->health = 0;
  newObject->open = NO_ID;
  newObject->movable = FALSE;

  return newObject;
}

Status object_destroy(Object *object)
{
  /* Comprobamos que el objeto existe */
  if (!object)
  {
    return ERROR;
  }

  /* Liberamos la memoria */
  free(object);
  return OK;
}

Id object_get_id(Object *object)
{
  /* Verificamos si hay objeto */
  if (!object)
  {
    return NO_ID;
  }
  return object->id;
}

Status object_set_name(Object *object, char *name)
{
  /* Comprobamos que los punteros sean válidos */
  if (!object || !name)
  {
    return ERROR;
  }

  /* Copiamos la cadena de texto */
  if (!strcpy(object->name, name))
  {
    return ERROR;
  }
  return OK;
}

const char *object_get_name(Object *object)
{
  /* Verificamos si hay objeto */
  if (!object)
  {
    return NULL;
  }
  return object->name;
}

Status object_print(Object *object)
{
  /* Comprobamos si el objeto es válido antes de imprimir */
  if (!object)
  {
    return ERROR;
  }

  /* Imprimimos datos por salida estándar */
  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}

Status object_set_desc(Object *object, char *desc)
{
  /*Compruebo que no sean NULL*/
  if (!object || !desc)
    return ERROR;
  /*Copio las descripcion*/
  if (!strcpy(object->description, desc))
    return ERROR;

  return OK;
}

const char *object_get_desc(Object *object)
{ /*compruebo que no sea NULL*/
  if (!object)
  {
    return NULL;
  } /*Devuelco la descripcion*/
  return object->description;
}
#include <stdio.h>
#include <stdlib.h>

Status object_set_health(Object *obj, int health)
{
  if (obj == NULL)
  {
    return ERROR;
  }
  obj->health = health;
  return OK;
}

Status object_set_movable(Object *obj, BOOL movable)
{
  if (obj == NULL)
  {
    return ERROR;
  }
  obj->movable = movable;
  return OK;
}

Status object_set_dependency(Object *obj, Id dependency)
{
  if (obj == NULL)
  {
    return ERROR;
  }
  obj->dependency = dependency;
  return OK;
}

Status object_set_open(Object *obj, Id open)
{
  if (obj == NULL)
  {
    return ERROR;
  }
  obj->open = open;
  return OK;
}

int object_get_health(Object *obj)
{
  if (obj == NULL)
  {
    return -1;
  }
  return obj->health;
}

BOOL object_get_movable(Object *obj)
{
  if (obj == NULL)
  {
    return FALSE;
  }
  return obj->movable;
}

Id object_get_dependency(Object *obj)
{
  if (obj == NULL)
  {
    return -1;
  }
  return obj->dependency;
}

Id object_get_open(Object *obj)
{
  if (obj == NULL)
  {
    return -1;
  }
  return obj->open;
}


