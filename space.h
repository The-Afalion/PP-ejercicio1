/**
 * @brief Define la interfaz del módulo de espacios
 *
 * @file space.h
 * @author Unai
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

#define GDESC_ROWS 5
#define GDESC_COLS 10

typedef struct Space Space;

/**
 * @brief Crea un nuevo espacio con un ID determinado
 * @author Unai
 * @param id Identificador único del espacio
 * @return Puntero al nuevo espacio o NULL en caso de error
 */
Space* space_create(Id id);

/**
 * @brief Destruye un espacio y libera su memoria
 * @author Unai
 * @param space Puntero al espacio a destruir
 * @return OK si se destruye con éxito, ERROR en caso contrario
 */
Status space_destroy(Space* space);

/**
 * @brief Obtiene el ID de un espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return El ID del espacio o NO_ID en caso de error
 */
Id space_get_id(Space* space);

/**
 * @brief Establece el nombre de un espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param name Cadena de texto con el nombre
 * @return OK si se establece correctamente, ERROR en caso contrario
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief Obtiene el nombre de un espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return Cadena con el nombre del espacio o NULL en caso de error
 */
const char* space_get_name(Space* space);

/**
 * @brief Establece el ID del espacio situado al norte
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del espacio al norte
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_north(Space* space, Id id);

/**
 * @brief Obtiene el ID del espacio situado al norte
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del espacio al norte o NO_ID en caso de error
 */
Id space_get_north(Space* space);

/**
 * @brief Establece el ID del espacio situado al sur
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del espacio al sur
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief Obtiene el ID del espacio situado al sur
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del espacio al sur o NO_ID en caso de error
 */
Id space_get_south(Space* space);

/**
 * @brief Establece el ID del espacio situado al este
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del espacio al este
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief Obtiene el ID del espacio situado al este
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del espacio al este o NO_ID en caso de error
 */
Id space_get_east(Space* space);

/**
 * @brief Establece el ID del espacio situado al oeste
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del espacio al oeste
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief Obtiene el ID del espacio situado al oeste
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del espacio al oeste o NO_ID en caso de error
 */
Id space_get_west(Space* space);

/**
 * @brief Establece un objeto en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param object_id ID del objeto
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_object(Space* space, Id object_id);

/**
 * @brief Obtiene el array de objetos del espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return Puntero al array de IDs de objetos
 */
Id* space_get_object(Space* space);

/**
 * @brief Imprime la información del espacio por pantalla
 * @author Unai
 * @param space Puntero al espacio
 * @return OK si se imprime con éxito, ERROR en caso contrario
 */
Status space_print(Space* space);

/**
 * @brief Añade un objeto al conjunto de objetos del espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param object_id ID del objeto a añadir
 * @return OK si se añade con éxito, ERROR en caso contrario
 */
Status space_add_object(Space* space, Id object_id);

/**
 * @brief Elimina un objeto del conjunto de objetos del espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param object_id ID del objeto a eliminar
 * @return OK si se elimina con éxito, ERROR en caso contrario
 */
Status space_remove_object(Space* space, Id object_id);

/**
 * @brief Obtiene la lista de IDs de objetos presentes en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return Array de IDs de objetos
 */
Id* space_get_objects(Space* space);

/**
 * @brief Obtiene el número total de objetos en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return Número entero de objetos
 */
int space_get_number_of_objects(Space* space);

/**
 * @brief Comprueba si un objeto específico está en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del objeto a buscar
 * @return OK si el objeto está presente, ERROR si no lo está
 */
Status space_contains_object(Space* space, Id id);

/**
 * @brief Establece el personaje presente en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @param id ID del personaje
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_character(Space* space, Id id);

/**
 * @brief Obtiene el personaje presente en el espacio
 * @author Unai
 * @param space Puntero al espacio
 * @return ID del personaje o NO_ID en caso de error
 */
Id space_get_character(Space* space);

/**
 * @brief Establece la descripción gráfica del espacio (gdesc)
 * @author Unai
 * @param space Puntero al espacio
 * @param gdesc Array de caracteres con la descripción gráfica
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_gdesc(Space* space, char gdesc[GDESC_ROWS][GDESC_COLS]);

/**
 * @brief Obtiene la descripción gráfica del espacio (gdesc)
 * @author Unai
 * @param space Puntero al espacio
 * @return Puntero a la descripción gráfica (matriz de caracteres)
 */
char(* space_get_gdesc(Space* space))[GDESC_COLS];

#endif