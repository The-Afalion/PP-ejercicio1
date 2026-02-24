/**
 * @brief It implements the character module
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

struct _Character {
  Id id;
  char name[CHARACTER_NAME_LEN + 1];
  char gdesc[6+1];
  int health;
  char friendly;
  char message[1000];
};

/**
  * @brief Crea un nuevo personaje
  * @author Rodrigo
  *
  * @param
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
  newCharacter->friendly = FALSE;
  newCharacter->message[0] = '\0';

  return newCharacter;
}

void character_destroy(Character *character) {
  if (!character) {
    return;
  }

  free(character);
  character = NULL;
}


Id character_get_id(const Character *character) {
  if (!character) {
    return NO_ID;
  }
  return character->id;
}

const char *character_get_name(const Character *character) {
  if (!character) {
    return NULL;
  }
  return character->name;
}

Status character_set_name(Character *character, const char *name) {
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

const char *character_get_gdesc(const Character *character) {
  if (!character) {
    return NULL;
  }
  return character->gdesc;
}
  Status character_set_gdesc(Character *character, const char *gdesc) {
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


int character_get_health(const Character *character) {
  if (!character) {
    return -1;
  }
  return character->health;
}

Status character_set_health(Character *character, int health) {
  if (!character) {
    return ERROR;
  }
  character->health = health;
  return OK;
}

BOOL character_get_friendly(const Character *character) {
  if (!character) {
    return FALSE;
  }
  return character->friendly;
}

Status character_set_friendly(Character *character, BOOL friendly) {
  if (!character) {
    return ERROR;
  }
  character->friendly = friendly;
  return OK;
}

const char *character_get_message(const Character *character) {
  if (!character) {
    return NULL;
  }
  return character->message;
}

Status character_set_message(Character *character, const char *message) {
  if (!character || !message) {
    return ERROR;
  }

  if (strlen(message) >= 100) {
    strncpy(character->message, message, 100);
    character->message[100] = '\0';
  } else {
    strcpy(character->message, message);
  }

  return OK;
}

void character_print(const Character *character) {
  if (!character) {
    return;
  }

  fprintf(stdout, "--> Character (Id: %ld; Name: %s)\n", character->id, character->name);
  fprintf(stdout, "--> Gdesc: %s\n", character->gdesc);
  fprintf(stdout, "--> Health: %d\n", character->health);
  fprintf(stdout, "--> Friendly: %s\n", character->friendly ? "TRUE" : "FALSE");
  fprintf(stdout, "--> Message: %s\n", character->message);
}

