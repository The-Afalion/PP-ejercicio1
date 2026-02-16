/**
 * @brief Implementa el módulo de espacio
 *
 * @file space.c
 * @author Unai y Rodrigo
 * @version 1.0
 * @date 15-02-2026
 * @copyright GNU Public License
 */

#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SINGLE_ELEM 1
#define FIRST_CHAR 0

/**
 * @brief Espacio
 * Esta estructura almacena toda la información de un espacio.
 */
struct Space {
  Id id; /*!< Número de Id del espacio, debe ser único */
  char name[WORD_SIZE + SINGLE_ELEM]; /*!< Nombre del espacio */
  Id north; /*!< Id del espacio en el norte */
  Id south; /*!< Id del espacio en el sur */
  Id east; /*!< Id del espacio en el este */
  Id west; /*!< Id del espacio en el oeste */
  Id object; /*!< Id del objeto en el espacio (NO_ID si no hay) */
};

Space *space_create(Id id) {
  Space *newSpace = NULL;

  /* Comprobamos que la ID proporcionada sea válida */
  if (id == NO_ID) {
    return NULL;
  }

  /* Reservamos memoria para el espacio */
  newSpace = (Space *) calloc(SINGLE_ELEM, sizeof(Space));

  /* Comprobamos si la reserva ha fallado */
  if (newSpace == NULL) {
    return NULL;
  }

  /* Inicializamos todos los valores por defecto (vacíos) */
  newSpace->id = id;
  newSpace->name[FIRST_CHAR] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->object = NO_ID;

  return newSpace;
}

Status space_destroy(Space *space) {
  /* Verificamos que el espacio exista */
  if (!space) {
    return ERROR;
  }

  /* Liberamos memoria */
  free(space);
  return OK;
}

Id space_get_id(Space *space) {
  /* Comprobamos que el puntero sea válido */
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space *space, char *name) {
  /* Comprobamos que el espacio y la cadena existan */
  if (!space || !name) {
    return ERROR;
  }

  /* Copiamos el nombre */
  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char *space_get_name(Space *space) {
  /* Comprobamos que el puntero sea válido */
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space *space, Id id) {
  /* Comprobamos validez del espacio y de la nueva ID */
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /* Asignamos enlace norte */
  space->north = id;
  return OK;
}

Id space_get_north(Space *space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space *space, Id id) {
  /* Comprobamos validez del espacio y de la nueva ID */
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /* Asignamos enlace sur */
  space->south = id;
  return OK;
}

Id space_get_south(Space *space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space *space, Id id) {
  /* Comprobamos validez del espacio y de la nueva ID */
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /* Asignamos enlace este */
  space->east = id;
  return OK;
}

Id space_get_east(Space *space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space *space, Id id) {
  /* Comprobamos validez del espacio y de la nueva ID */
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /* Asignamos enlace oeste */
  space->west = id;
  return OK;
}

Id space_get_west(Space *space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Status space_set_object(Space *space, Id value) {
  /* Comprobamos que el puntero sea válido */
  if (!space) {
    return ERROR;
  }
  /* Colocamos el objeto en el espacio */
  space->object = value;
  return OK;
}

Id space_get_object(Space *space) {
  if (!space) {
    return NO_ID;
  }
  return space->object;
}

Status space_print(Space *space) {
  Id idaux = NO_ID;

  /* Comprobamos si el espacio existe */
  if (!space) {
    return ERROR;
  }

  /* Imprimimos ID y nombre */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  return OK;
}
