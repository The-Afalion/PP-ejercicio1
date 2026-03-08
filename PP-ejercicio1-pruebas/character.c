/**
 * @brief Implementa el módulo del personaje
 *
 * @file character.c
 * @author Rodrigo
 * @version 2.0
 * @date 23-02-2026
 * @copyright GNU Public License
 */

#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#define DESC 7
/**
 * @brief Estructura que define un personaje
 */
struct _Character {
  Id id;
  char name[CHARACTER_NAME_LEN + 1];
  char gdesc[DESC];
  int health;
  int friendly;
  char message[WORD_SIZE];
};

/**
 * @brief Crea un nuevo personaje
 */
Character *character_create(Id id) {
  Character *newCharacter = NULL;

  if (id == NO_ID)
    return NULL;

  newCharacter = (Character *)malloc(sizeof(Character));

  if (newCharacter == NULL) {
    return NULL;
  }
  newCharacter->id = id;

  newCharacter->name[0] = '\0';
  newCharacter->gdesc[0] = '\0';
  newCharacter->health = 0;
  newCharacter->friendly = 0;
  newCharacter->message[0] = '\0';

  return newCharacter;
}

/**
 * @brief Destruye un personaje
 */
void character_destroy(Character *character) {
  if (!character) {
    return;
  }

  free(character);
  character = NULL;
}

/**
 * @brief Obtiene el id de un personaje
 */
Id character_get_id(Character *character) {
  if (!character) {
    return NO_ID;
  }
  return character->id;
}

/**
 * @brief Obtiene el nombre de un personaje
 */
char *character_get_name(Character *character) {
  if (!character) {
    return NULL;
  }
  return character->name;
}

/**
 * @brief Establece el nombre de un personaje
 */
Status character_set_name(Character *character, char *name) {
  if (!character || !name) {
    return ERROR;
  }

  if (strlen(name) >= CHARACTER_NAME_LEN) {
    strncpy(character->name, name, CHARACTER_NAME_LEN);
    character->name[CHARACTER_NAME_LEN] = '\0';
  } else {
    strcpy(character->name, name);
  }

  return OK;
}

/**
 * @brief Obtiene la descripción gráfica de un personaje
 */
 char *character_get_gdesc(Character *character) {
  if (!character) {
    return NULL;
  }
  return character->gdesc;
}

/**
 * @brief Establece la descripción gráfica de un personaje
 */
Status character_set_gdesc(Character *character, char *gdesc) {
  if (!character || !gdesc) {
    return ERROR;
  }

  if (strlen(gdesc) >= 6) {
    strncpy(character->gdesc, gdesc, 6);
    character->gdesc[6] = '\0';
  } else {
    strcpy(character->gdesc, gdesc);
  }

  return OK;
}

/**
 * @brief Obtiene la salud de un personaje
 */
int character_get_health( Character *character) {
  if (!character) {
    return -1;
  }
  return character->health;
}

/**
 * @brief Establece la salud de un personaje
 */
Status character_set_health(Character *character, int health) {
  if (!character) {
    return ERROR;
  }
  character->health = health;
  return OK;
}

/**
 * @brief Obtiene el estado de amistad de un personaje
 */
int character_get_friendly( Character *character) {
  if (!character) {
    return 0;
  }
  return character->friendly;
}

/**
 * @brief Establece el estado de amistad de un personaje
 */
Status character_set_friendly(Character *character, int friendly) {
  if (!character) {
    return ERROR;
  }
  character->friendly = friendly;
  return OK;
}

/**
 * @brief Obtiene el mensaje de un personaje
 */
 char *character_get_message( Character *character) {
  if (!character) {
    return NULL;
  }
  return character->message;
}

/**
 * @brief Establece el mensaje de un personaje
 */
Status character_set_message(Character *character, char *message) {
  if (!character || !message) {
    return ERROR;
  }

  if (strlen(message) >= 999) {
    strncpy(character->message, message, 999);
    character->message[999] = '\0';
  } else {
    strcpy(character->message, message);
  }

  return OK;
}

/**
 * @brief Imprime la información de un personaje
 */
void character_print( Character *character) {
  if (!character) {
    return;
  }

  fprintf(stdout, "--> Personaje (Id: %ld; Nombre: %s)\n", character->id,
          character->name);
  fprintf(stdout, "--> Gdesc: %s\n", character->gdesc);
  fprintf(stdout, "--> Salud: %d\n", character->health);
  fprintf(stdout, "--> Amistoso: %s\n",
          character->friendly ? "SI" : "NO");
  fprintf(stdout, "--> Mensaje: %s\n", character->message);
}
