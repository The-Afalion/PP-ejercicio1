/**
 * @brief Implementa el módulo de espacio, gestionando sus propiedades y conexiones.
 * @file space.c
 * @author Rodrigo & Unai
 * @version 2.0
 * @date 12-03-2024
 * @copyright GNU Public License
 */

#include "space.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estructura de Espacio
 * Almacena la información de un espacio en el juego, incluyendo sus conexiones y objetos.
 */
struct Space {
  Id id;                    /*!< Identificador único del espacio */
  char name[WORD_SIZE + 1]; /*!< Nombre del espacio */
  Id north;                 /*!< ID del espacio al norte */
  Id south;                 /*!< ID del espacio al sur */
  Id east;                  /*!< ID del espacio al este */
  Id west;                  /*!< ID del espacio al oeste */
  Id object;                /*!< ID del objeto en el espacio (NO_ID si no hay ninguno) */
};

/**
 * @brief Crea un nuevo espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param id El identificador para el nuevo espacio.
 * @return Un puntero al espacio recién creado, o NULL si ocurre un error.
 */
Space* space_create(Id id) {
  Space* newSpace = NULL;

  if (id == NO_ID) {
    return NULL;
  }

  newSpace = (Space*)calloc(1, sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->object = NO_ID;

  return newSpace;
}

/**
 * @brief Destruye un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio a destruir.
 * @return OK si el espacio se destruyó correctamente, o ERROR en caso contrario.
 */
Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  free(space);
  return OK;
}

/**
 * @brief Obtiene el ID de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @return El ID del espacio, o NO_ID si el puntero es nulo.
 */
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

/**
 * @brief Establece el nombre de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @param name El nuevo nombre para el espacio.
 * @return OK si el nombre se estableció correctamente, o ERROR en caso contrario.
 */
Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (strcpy(space->name, name) == NULL) {
    return ERROR;
  }
  return OK;
}

/**
 * @brief Obtiene el nombre de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @return El nombre del espacio, o NULL si el puntero es nulo.
 */
const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

/**
 * @brief Establece la conexión norte de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @param id El ID del espacio a conectar al norte.
 * @return OK si la conexión se estableció correctamente, o ERROR en caso contrario.
 */
Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

/**
 * @brief Obtiene la conexión norte de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @return El ID del espacio conectado al norte, o NO_ID si no hay conexión.
 */
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

/**
 * @brief Establece la conexión sur de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @param id El ID del espacio a conectar al sur.
 * @return OK si la conexión se estableció correctamente, o ERROR en caso contrario.
 */
Status space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

/**
 * @brief Obtiene la conexión sur de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @return El ID del espacio conectado al sur, o NO_ID si no hay conexión.
 */
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

/**
 * @brief Establece la conexión este de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @param id El ID del espacio a conectar al este.
 * @return OK si la conexión se estableció correctamente, o ERROR en caso contrario.
 */
Status space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

/**
 * @brief Obtiene la conexión este de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @return El ID del espacio conectado al este, o NO_ID si no hay conexión.
 */
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

/**
 * @brief Establece la conexión oeste de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @param id El ID del espacio a conectar al oeste.
 * @return OK si la conexión se estableció correctamente, o ERROR en caso contrario.
 */
Status space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

/**
 * @brief Obtiene la conexión oeste de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @return El ID del espacio conectado al oeste, o NO_ID si no hay conexión.
 */
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

/**
 * @brief Coloca un objeto en un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @param value El ID del objeto a colocar.
 * @return OK si el objeto se colocó correctamente, o ERROR en caso contrario.
 */
Status space_set_object(Space* space, Id value) {
  if (!space) {
    return ERROR;
  }
  space->object = value;
  return OK;
}

/**
 * @brief Obtiene el objeto de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio.
 * @return El ID del objeto en el espacio, o NO_ID si no hay ninguno.
 */
Id space_get_object(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->object;
}

/**
 * @brief Imprime la información de un espacio.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param space Un puntero al espacio a imprimir.
 * @return OK si la información se imprimió correctamente, o ERROR en caso contrario.
 */
Status space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  /* 1. Imprime el ID y el nombre del espacio */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. Imprime los enlaces para cada dirección */
  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Imprime si hay un objeto en el espacio */
  if (space_get_object(space) != NO_ID) {
    fprintf(stdout, "---> Object in the space (Id: %ld).\n", space->object);
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
