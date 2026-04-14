/**
 * @brief Define la interfaz del módulo de espacios
 *
 * @file space.h
 * @author Unai
 * @version 3.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"
#include "link.h" /* Necesario para usar la estructura Link */

#define GDESC_ROWS 5
#define GDESC_COLS 10

typedef struct Space Space;

/**
 * @brief Crea un nuevo espacio con un ID determinado
 * @param id Identificador único del espacio
 * @return Puntero al nuevo espacio o NULL en caso de error
 */
Space* space_create(Id id);

/**
 * @brief Destruye un espacio y libera su memoria
 * @param space Puntero al espacio a destruir
 * @return OK si se destruye con éxito, ERROR en caso contrario
 */
Status space_destroy(Space* space);

/**
 * @brief Obtiene el ID de un espacio
 * @param space Puntero al espacio
 * @return El ID del espacio o NO_ID en caso de error
 */
Id space_get_id(Space* space);

/**
 * @brief Establece el nombre de un espacio
 * @param space Puntero al espacio
 * @param name Cadena de texto con el nombre
 * @return OK si se establece correctamente, ERROR en caso contrario
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief Obtiene el nombre de un espacio
 * @param space Puntero al espacio
 * @return Cadena con el nombre del espacio o NULL en caso de error
 */
const char* space_get_name(Space* space);


/**
 * @brief Añade un nuevo enlace al espacio buscando el primer hueco disponible
 * @param space Puntero al espacio
 * @param link Puntero al enlace que se desea añadir
 * @return OK si se añade con éxito, ERROR si no hay espacio o los parámetros son nulos
 */
Status space_add_link(Space* space, Link* link);

/**
 * @brief Busca y devuelve un enlace del espacio a partir de su ID
 * @param space Puntero al espacio
 * @param link_id ID del enlace a buscar
 * @return Puntero al enlace si lo encuentra, o NULL en caso de error/no encontrado
 */
Link* space_get_link(Space* space, Id link_id);



/**
 * @brief Añade un objeto al conjunto de objetos del espacio
 * @param space Puntero al espacio
 * @param object_id ID del objeto a añadir
 * @return OK si se añade con éxito, ERROR en caso contrario
 */
Status space_add_object(Space* space, Id object_id);

/**
 * @brief Elimina un objeto del conjunto de objetos del espacio
 * @param space Puntero al espacio
 * @param object_id ID del objeto a eliminar
 * @return OK si se elimina con éxito, ERROR en caso contrario
 */
Status space_remove_object(Space* space, Id object_id);

/**
 * @brief Obtiene la lista de IDs de objetos presentes en el espacio
 * @param space Puntero al espacio
 * @return Array de IDs de objetos
 */
Id* space_get_objects(Space* space);

/**
 * @brief Obtiene el número total de objetos en el espacio
 * @param space Puntero al espacio
 * @return Número entero de objetos
 */
int space_get_number_of_objects(Space* space);

/**
 * @brief Comprueba si un objeto específico está en el espacio
 * @param space Puntero al espacio
 * @param id ID del objeto a buscar
 * @return OK si el objeto está presente, ERROR si no lo está
 */
Status space_contains_object(Space* space, Id id);

/**
 * @brief Establece el personaje presente en el espacio
 * @param space Puntero al espacio
 * @param id ID del personaje
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_character(Space* space, Id id);

/**
 * @brief Obtiene el personaje presente en el espacio
 * @param space Puntero al espacio
 * @return ID del personaje o NO_ID en caso de error
 */
Id space_get_character(Space* space);

/**
 * @brief Establece la descripción gráfica del espacio (gdesc)
 * @param space Puntero al espacio
 * @param gdesc Array de caracteres con la descripción gráfica
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_gdesc(Space* space, char gdesc[GDESC_ROWS][GDESC_COLS]);

/**
 * @brief Obtiene la descripción gráfica del espacio (gdesc)
 * @param space Puntero al espacio
 * @return Puntero a la descripción gráfica (matriz de caracteres)
 */
char(* space_get_gdesc(Space* space))[GDESC_COLS];

/**
 * @brief Imprime la información del espacio por pantalla
 * @param space Puntero al espacio
 * @return OK si se imprime con éxito, ERROR en caso contrario
 */
Status space_print(Space* space);

/**
 * @brief Obtiene el número total de enlaces asociados a un espacio
 * @param space Puntero al espacio
 * @return Número de enlaces del espacio o -1 en caso de error
 */
int space_get_number_of_links(Space *space);

/**
 * @brief Establece si el espacio ha sido descubierto o no
 * @param space Puntero al espacio
 * @param discovered TRUE si fue descubierto, FALSE si no
 * @return OK si se establece con éxito, ERROR en caso contrario
 */
Status space_set_discovered(Space* space, BOOL discovered);

/**
 * @brief Comprueba si el espacio ha sido descubierto
 * @param space Puntero al espacio
 * @return TRUE si fue descubierto, FALSE si no
 */
BOOL space_get_discovered(Space* space);

#endif
