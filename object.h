/**
 * @brief Define la interfaz de objeto
 *
 * @file object.h
 * @author Rodrigo & Unai
 * @version 1.0
 * @date (3/2/2026)
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/* Definición de la estructura de datos opaca */
typedef struct Object Object;

/**
 * @brief Crea un nuevo objeto
 * @param id Identificador del objeto
 * @return Puntero al nuevo objeto o NULL si hay error
 */
Object *object_create(Id id);

/**
 * @brief Destruye un objeto y libera memoria
 * @param object Puntero al objeto
 * @return OK o ERROR
 */
Status object_destroy(Object *object);

/**
 * @brief Obtiene el ID de un objeto
 * @param object Puntero al objeto
 * @return El ID del objeto o NO_ID si hay error
 */
Id object_get_id(Object *object);

/**
 * @brief Establece el nombre de un objeto
 * @param object Puntero al objeto
 * @param name Cadena con el nuevo nombre
 * @return OK o ERROR
 */
Status object_set_name(Object *object, char *name);

/**
 * @brief Obtiene el nombre de un objeto
 * @param object Puntero al objeto
 * @return Puntero a la cadena de nombre o NULL si hay error
 */
const char *object_get_name(Object *object);

/**
 * @brief Imprime la información del objeto (para depuración)
 * @param object Puntero al objeto
 * @return OK o ERROR
 */
Status object_print(Object *object);

#endif