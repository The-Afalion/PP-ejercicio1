/**
 * @brief Implementa el módulo de objetos, permitiendo su creación, destrucción y gestión.
 * @file object.c
 * @author Rodrigo & Unai
 * @version 2.0
 * @date 12-03-2024
 * @copyright GNU Public License
 */

#include "object.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estructura de Objeto
 * Almacena la información de un objeto en el juego.
 */
struct Object {
  Id id;                    /*!< Identificador único del objeto */
  char name[WORD_SIZE + 1]; /*!< Nombre del objeto */
};

/**
 * @brief Crea un nuevo objeto.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param id Es el identificador para el nuevo objeto.
 * @return Un puntero al objeto recién creado, o NULL si ocurre un error.
 */
Object* object_create(Id id) {
  Object* newObject = NULL;

  if (id == NO_ID) {
    return NULL;
  }

  newObject = (Object*)calloc(1, sizeof(Object));
  if (newObject == NULL) {
    return NULL;
  }

  newObject->id = id;
  newObject->name[0] = '\0';

  return newObject;
}

/**
 * @brief Destruye un objeto.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param object Un puntero al objeto a destruir.
 * @return OK si el objeto se destruyó correctamente, o ERROR en caso contrario.
 */
Status object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  return OK;
}

/**
 * @brief Obtiene el ID de un objeto.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param object Un puntero al objeto.
 * @return El ID del objeto, o NO_ID si el puntero es nulo.
 */
Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

/**
 * @brief Establece el nombre de un objeto.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param object Un puntero al objeto.
 * @param name El nuevo nombre para el objeto.
 * @return OK si el nombre se estableció correctamente, o ERROR en caso contrario.
 */
Status object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (strcpy(object->name, name) == NULL) {
    return ERROR;
  }
  return OK;
}

/**
 * @brief Obtiene el nombre de un objeto.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param object Un puntero al objeto.
 * @return El nombre del objeto, or NULL si el puntero es nulo.
 */
const char* object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

/**
 * @brief Imprime la información de un objeto.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param object Un puntero al objeto a imprimir.
 * @return OK si la información se imprimió correctamente, o ERROR en caso contrario.
 */
Status object_print(Object* object) {
  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}
