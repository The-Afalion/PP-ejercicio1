/**
 * @brief Define la interfaz del módulo de espacio
 *
 * @file space.h
 * @author (Unai & Rodrigo)
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"

typedef struct Space Space;

/**
 * @brief Crea un nuevo espacio, reservando memoria e inicializando sus miembros
 * @author Profesores PPROG
 *
 * @param id el número de identificación para el nuevo espacio
 * @return un nuevo espacio, inicializado
 */
Space *space_create(Id id);

/**
 * @brief Destruye un espacio, liberando la memoria asignada
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio que debe ser destruido
 * @return OK, si todo va bien o ERROR si hubo algún error
 */
Status space_destroy(Space *space);

/**
 * @brief Obtiene el id de un espacio
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @return el id del espacio
 */
Id space_get_id(Space *space);

/**
 * @brief Establece el nombre de un espacio
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @param name una cadena con el nombre a almacenar
 * @return OK, si todo va bien o ERROR si hubo algún error
 */
Status space_set_name(Space *space, char *name);

/**
 * @brief Obtiene el nombre de un espacio
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @return una cadena con el nombre del espacio
 */
const char *space_get_name(Space *space);

/**
 * @brief Establece el id del espacio ubicado al norte
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @param id el número de id del espacio ubicado al norte
 * @return OK, si todo va bien o ERROR si hubo algún error
 */

Status space_set_north(Space *space, Id id);

/**
 * @brief Obtiene el id del espacio ubicado al norte
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @return el número de id del espacio ubicado al norte
 */
Id space_get_north(Space *space);

/**
 * @brief Establece el id del espacio ubicado al sur
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @param id el número de id del espacio ubicado al sur
 * @return OK, si todo va bien o ERROR si hubo algún error
 */
Status space_set_south(Space *space, Id id);

/**
 * @brief Obtiene el id del espacio ubicado al sur
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @return el número de id del espacio ubicado al sur
 */
Id space_get_south(Space *space);

/**
 * @brief Establece el id del espacio ubicado al este
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @param id el número de id del espacio ubicado al este
 * @return OK, si todo va bien o ERROR si hubo algún error
 */
Status space_set_east(Space *space, Id id);

/**
 * @brief Obtiene el id del espacio ubicado al este
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @return el número de id del espacio ubicado al este
 */
Id space_get_east(Space *space);

/**
 * @brief Establece el id del espacio ubicado al oeste
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @param id el número de id del espacio ubicado al oeste
 * @return OK, si todo va bien o ERROR si hubo algún error
 */
Status space_set_west(Space *space, Id id);

/**
 * @brief Obtiene el id del espacio ubicado al oeste
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @return el número de id del espacio ubicado al oeste
 */
Id space_get_west(Space *space);

/**
 * @brief Establece el objeto en el espacio
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @param object_id el id del objeto a establecer
 * @return OK, si todo va bien o ERROR si hubo algún error
 */
Status space_set_object(Space *space, Id object_id);

/**
 * @brief Obtiene el objeto del espacio
 * @author Profesores PPROG
 *
 * @param space un puntero al espacio
 * @return el id del objeto en el espacio
 */
Id space_get_object(Space *space);

/**
 * @brief Imprime la información del espacio
 * @author Profesores PPROG
 *
 * Esta función muestra el id y el nombre del espacio, los espacios que lo rodean y si tiene un objeto o no.
 * @param space un puntero al espacio
 * @return OK, si todo va bien o ERROR si hubo algún error
 */
Status space_print(Space *space);

#endif