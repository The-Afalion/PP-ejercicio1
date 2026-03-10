/**
 * @brief Define el módulo del personaje
 *
 * @file character.c
 * @author Rodrigo
 * @version 2.0
 * @date 23-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"

struct _Character {
    Id id;
    char name[CHARACTER_NAME_LEN + 1];
    char gdesc[10];
    int health;
    int friendly;
    char message[100];
};

Character *character_create(Id id) {
    Character *newCharacter = NULL;

    if (id == NO_ID)
        return NULL;

    newCharacter = (Character *) malloc(sizeof (Character));

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

void character_destroy(Character *character) {
    if (character != NULL) {
        free(character);
    }
}

Id character_get_id(Character *character) {
    if (!character) {
        return NO_ID;
    }
    return character->id;
}

char *character_get_name(Character *character) {
    if (!character) {
        return NULL;
    }
    return character->name;
}

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

char *character_get_gdesc(Character *character) {
    if (!character) {
        return NULL;
    }
    return character->gdesc;
}

Status character_set_gdesc(Character *character, char *gdesc) {
    if (!character || !gdesc) {
        return ERROR;
    }

    strcpy(character->gdesc, gdesc);

    return OK;
}

int character_get_health(Character *character) {
    if (!character) {
        return 0;
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

int character_get_friendly(Character *character) {
    if (!character) {
        return 0;
    }
    return character->friendly;
}

Status character_set_friendly(Character *character, int friendly) {
    if (!character) {
        return ERROR;
    }
    character->friendly = friendly;
    return OK;
}

char *character_get_message(Character *character) {
    if (!character) {
        return NULL;
    }
    return character->message;
}

Status character_set_message(Character *character, char *message) {
    if (!character || !message) {
        return ERROR;
    }

    strcpy(character->message, message);

    return OK;
}

void character_print(Character *character) {
    if (character != NULL) {
        printf("--> Character (Id: %ld; Name: %s; Gdesc: %s; Health: %d; Friendly: %d; Message: %s)\n",
               character->id, character->name, character->gdesc, character->health, character->friendly, character->message);
    }
}
