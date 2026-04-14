/**
 * @brief Define la interfaz del módulo de enlaces
 *
 * @file link.h
 * @author Unai.G
 * @version 1.0
 * @date 24-03-2026
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

/**
 * @brief Estructura opaca que representa un enlace entre espacios
 */
typedef struct _Link Link;

/**
 * @brief Crea un nuevo enlace
 * @author Unai.G
 * @param id Identificador único del enlace
 * @return Puntero al enlace creado o NULL si hay error
 */
Link* link_create(Id id);

/**
 * @brief Destruye un enlace y libera su memoria
 * @author Unai.G
 * @param link Puntero al enlace
 * @return OK si se destruye correctamente, ERROR en caso contrario
 */
Status link_destroy(Link* link);

/**
 * @brief Establece el nombre de un enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @param name Cadena con el nombre a asignar
 * @return OK si se establece correctamente, ERROR en caso contrario
 */
Status link_set_name(Link* link, char* name);

/**
 * @brief Establece el espacio de origen del enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @param origin ID del espacio de origen
 * @return OK si se establece correctamente, ERROR en caso contrario
 */
Status link_set_origin(Link* link, Id origin);

/**
 * @brief Establece el espacio de destino del enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @param destination ID del espacio de destino
 * @return OK si se establece correctamente, ERROR en caso contrario
 */
Status link_set_destination(Link* link, Id destination);

/**
 * @brief Establece la dirección asociada al enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @param direction Dirección del enlace
 * @return OK si se establece correctamente, ERROR en caso contrario
 */
Status link_set_direction(Link* link, Directions direction);

/**
 * @brief Establece si el enlace está abierto o cerrado
 * @author Unai.G
 * @param link Puntero al enlace
 * @param open TRUE si está abierto, FALSE si está cerrado
 * @return OK si se establece correctamente, ERROR en caso contrario
 */
Status link_set_open(Link* link, BOOL open);

/**
 * @brief Obtiene el ID de un enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @return El ID del enlace o NO_ID en caso de error
 */
Id link_get_id(Link* link);

/**
 * @brief Obtiene el nombre de un enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @return Cadena con el nombre del enlace o NULL en caso de error
 */
char* link_get_name(Link* link);

/**
 * @brief Obtiene el espacio de origen de un enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @return ID del espacio de origen o NO_ID en caso de error
 */
Id link_get_origin(Link* link);

/**
 * @brief Obtiene el espacio de destino de un enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @return ID del espacio de destino o NO_ID en caso de error
 */
Id link_get_destination(Link* link);

/**
 * @brief Obtiene la dirección de un enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @return Dirección del enlace o U en caso de error
 */
Directions link_get_direction(Link* link);

/**
 * @brief Comprueba si un enlace está abierto
 * @author Unai.G
 * @param link Puntero al enlace
 * @return TRUE si está abierto, FALSE en caso contrario o si hay error
 */
BOOL link_get_open(Link* link);

/**
 * @brief Imprime la información de un enlace por pantalla
 * @author Unai.G
 * @param link Puntero al enlace
 * @return OK si se imprime correctamente, ERROR en caso contrario
 */
Status link_print(Link *link);

/**
 * @brief Establece el identificador de un enlace
 * @author Unai.G
 * @param link Puntero al enlace
 * @param id Nuevo identificador del enlace
 * @return OK si se establece correctamente, ERROR en caso contrario
 */
Status link_set_id(Link* link, Id id);

#endif
