/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Rodrigo & Unai
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
 * This struct stores all the information of an object.
 */
struct Object
{
  Id id;                              /*!< La ID del objeto */
  char name[WORD_SIZE + SINGLE_ELEM]; /*!< Nombre del objeto */
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