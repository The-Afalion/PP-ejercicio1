/**
 * @brief Define la interfaz principal del juego
 *
 * @file game.h
 * @author Unai
 * @version 2.0
 * @date 15-03-2026
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/**
 * @brief Estructura opaca para manejar un conjunto (set).
 */
typedef struct Set Set;

/**
 * @brief Crea un nuevo conjunto e inicializa sus parámetros.
 * @return Puntero al nuevo conjunto o NULL en caso de error.
 */
Set* set_create();

/**
 * @brief Libera la memoria reservada para un conjunto.
 * @param s Puntero al conjunto a eliminar.
 * @return OK si tiene éxito, ERROR en caso contrario.
 */
Status set_destroy(Set* s);

/**
 * @brief Añade un nuevo elemento (Id) al conjunto.
 * @param s Puntero al conjunto.
 * @param id Identificador que se desea añadir.
 * @return OK si tiene éxito, ERROR en caso contrario.
 */
Status set_add(Set* s, Id id);

/**
 * @brief Elimina un elemento específico del conjunto.
 * @param s Puntero al conjunto.
 * @param id Identificador que se desea eliminar.
 * @return OK si tiene éxito, ERROR en caso contrario.
 */
Status set_del(Set* s, Id id);

/**
 * @brief Comprueba si un identificador existe dentro del conjunto.
 * @param s Puntero al conjunto.
 * @param id Identificador a buscar.
 * @return OK si el elemento existe, ERROR en caso contrario.
 */
Status set_find(Set* s, Id id);

/**
 * @brief Imprime el contenido del conjunto por pantalla (útil para depuración).
 * @param s Puntero al conjunto.
 */
void set_print(Set* s);

/**
 * @brief Obtiene el identificador almacenado en un índice específico.
 * @param s Puntero al conjunto.
 * @param indx Posición del identificador en el conjunto.
 * @return El ID correspondiente o NO_ID en caso de error.
 */
Id set_get_id(Set* s, int indx);

/**
 * @brief Obtiene el número total de identificadores almacenados actualmente.
 * @param s Puntero al conjunto.
 * @return El número de elementos (int).
 */
int set_get_numberid(Set* s);

/**
 * @brief Obtiene el array completo de identificadores del conjunto.
 * @param s Puntero al conjunto.
 * @return Puntero al array de Ids o NULL en caso de error.
 */
Id* set_get_ids(Set* s);

#endif