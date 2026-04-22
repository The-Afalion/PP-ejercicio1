/**
 * @brief It defines the object interface
 *
 * @file object.h
 * @author Rodrigo
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
Object* object_create(Id id);

/**
 * @brief Destruye un objeto y libera memoria
 * @param object Puntero al objeto
 * @return OK o ERROR
 */
Status object_destroy(Object* object);

/**
 * @brief Obtiene el ID de un objeto
 * @param object Puntero al objeto
 * @return El ID del objeto o NO_ID si hay error
 */
Id object_get_id(Object* object);

/**
 * @brief Establece el nombre de un objeto
 * @param object Puntero al objeto
 * @param name Cadena con el nuevo nombre
 * @return OK o ERROR
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief Obtiene el nombre de un objeto
 * @param object Puntero al objeto
 * @return Puntero a la cadena de nombre o NULL si hay error
 */
const char* object_get_name(Object* object);

/**
 * @brief Imprime la información del objeto (para depuración)
 * @param object Puntero al objeto
 * @return OK o ERROR
 */
Status object_print(Object* object);

/**
 * @brief Establece la descripcion de un objeto
 * @param object Puntero a objeto
 * @param desc descripcion del objeto
 * @return Ok o ERROR
 */
 Status object_set_desc(Object *object, char *desc);

 /**
 * @brief Obtiene la descripcion de un objeto
 * @param object Puntero al objeto
 * @return Puntero a la cadena de descripcion o NULL si hay error
 */
 const char* object_get_desc(Object* object);
/**
 * @brief Establece la vida que aporta o quita un objeto
 * @param object Puntero al objeto
 * @param health Cantidad de vida a modificar
 * @return OK o ERROR
 */
Status object_set_health(Object* object, int health);

/**
 * @brief Obtiene la vida que aporta o quita un objeto
 * @param object Puntero al objeto
 * @return El valor de la vida del objeto, o un código de error (ej. -1) si el puntero es NULL
 */
int object_get_health(Object* object);

/**
 * @brief Establece si un objeto es movible o no
 * @param object Puntero al objeto
 * @param movable TRUE si se puede mover, FALSE en caso contrario
 * @return OK o ERROR
 */
Status object_set_movable(Object* object, BOOL movable);

/**
 * @brief Obtiene si un objeto se puede mover
 * @param object Puntero al objeto
 * @return TRUE si es movible, FALSE si no lo es o si hay error
 */
BOOL object_get_movable(Object* object);

/**
 * @brief Establece la dependencia de un objeto (de quién depende)
 * @param object Puntero al objeto
 * @param dependency Id del objeto del que depende
 * @return OK o ERROR
 */
Status object_set_dependency(Object* object, Id dependency);

/**
 * @brief Obtiene la dependencia de un objeto
 * @param object Puntero al objeto
 * @return El Id de la dependencia, o NO_ID si hay error
 */
Id object_get_dependency(Object* object);

/**
 * @brief Establece el Id de lo que este objeto puede abrir
 * @param object Puntero al objeto
 * @param open Id de lo que puede abrir
 * @return OK o ERROR
 */
Status object_set_open(Object* object, Id open);

/**
 * @brief Obtiene el Id de lo que este objeto puede abrir
 * @param object Puntero al objeto
 * @return El Id de lo que abre, o NO_ID si hay error
 */
Id object_get_open(Object* object);


#endif