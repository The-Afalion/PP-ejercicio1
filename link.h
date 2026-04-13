#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef struct _Link Link;

/**
 * @brief Crea un nuevo enlace con el ID especificado.
 * @author Unai G.
 * @param id ID del enlace a crear.
 * @return Puntero al enlace creado, o NULL si hay error.
 */
Link *link_create(Id id);
/**
 * @brief Destruye un enlace, liberando la memoria asociada.
 * @author Unai G.
 * @param link Puntero al enlace a destruir.
 * @return OK si se destruye con éxito, ERROR en caso contrario.
 */
Status link_destroy(Link *link);
/**
 * @brief Establece el nombre de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @param name Nombre del enlace.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status link_set_name(Link *link, char *name);
/**
 * @brief Establece el nodo de origen de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @param origin ID del nodo de origen.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status link_set_origin(Link *link, Id origin);
/**
 * @brief Establece el nodo de destino de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @param destination ID del nodo de destino.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status link_set_destination(Link *link, Id destination);
/**
 * @brief Establece la dirección de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @param direction Dirección del enlace.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status link_set_direction(Link *link, Directions direction);
/**
 * @brief Establece el estado de apertura de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @param open Estado de apertura del enlace.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status link_set_open(Link *link, BOOL open);
/**
 * @brief Obtiene el ID de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @return ID del enlace.
 */
Id link_get_id(Link *link);
/**
 * @brief Obtiene el nombre de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @return Nombre del enlace.
 */
char *link_get_name(Link *link);
/**
 * @brief Obtiene el ID del nodo de origen de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @return ID del nodo de origen.
 */
Id link_get_origin(Link *link);
/**
 * @brief Obtiene el ID del nodo de destino de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @return ID del nodo de destino.
 */
Id link_get_destination(Link *link);
/**
 * @brief Obtiene la dirección de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @return Dirección del enlace.
 */
Directions link_get_direction(Link *link);
/**
 * @brief Obtiene el estado de apertura de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @return Estado de apertura del enlace.
 */
BOOL link_get_open(Link *link);
/**
 * @brief Imprime la información de un enlaces.
 * @author Unai G.
 * @param link Puntero al enlaces.
 * @return OK si se imprime con éxito, ERROR en caso contrario.
 */
Status link_print(Link *link);
/**
 * @brief Establece el ID de un enlace.
 * @author Unai G.
 * @param link Puntero al enlace.
 * @param id ID a establecer.
 * @return OK si se establece con éxito, ERROR en caso contrario.
 */
Status link_set_id(Link *link, Id id);

#endif