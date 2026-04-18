/**
 * @brief Implementa el módulo del personaje
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

struct _Character
{
    Id id;                             /*!< Id del personaje */
    char name[CHARACTER_NAME_LEN + 1]; /*!< Nombre del personaje */
    char gdesc[10];                    /*!< Descripción gráfica */
    int health;                        /*!< Puntos de salud */
    int friendly;                      /*!< Indica si es amistoso */
    char message[100];                 /*!< Mensaje asociado al personaje */
    Id following;                      /*!< Id de la entidad a la que sigue */
};

Character *character_create(Id id)
{
    Character *newCharacter = NULL;

    /* Comprueba si el id es válido */
    if (id == NO_ID)
        return NULL;

    newCharacter = (Character *)malloc(sizeof(Character));

    /* Comprueba si falla la reserva de memoria */
    if (newCharacter == NULL)
    {
        return NULL;
    }

    /* Inicializa los datos del personaje */
    newCharacter->id = id;

    newCharacter->name[0] = '\0';
    newCharacter->gdesc[0] = '\0';
    newCharacter->health = 0;
    newCharacter->friendly = 0;
    newCharacter->message[0] = '\0';
    newCharacter->following = NO_ID;

    return newCharacter;
}

void character_destroy(Character *character)
{
    /* Libera la memoria del personaje si existe */
    if (character != NULL)
    {
        free(character);
    }
}

Id character_get_id(Character *character)
{
    /* Devuelve el id o NO_ID si hay error */
    if (!character)
    {
        return NO_ID;
    }
    return character->id;
}

char *character_get_name(Character *character)
{
    /* Devuelve el nombre del personaje */
    if (!character)
    {
        return NULL;
    }
    return character->name;
}

Status character_set_name(Character *character, char *name)
{
    /* Comprueba que los datos de entrada sean válidos */
    if (!character || !name)
    {
        return ERROR;
    }

    /* Si el nombre es demasiado largo, se recorta para evitar desbordamientos */
    if (strlen(name) >= CHARACTER_NAME_LEN)
    {
        strncpy(character->name, name, CHARACTER_NAME_LEN);
        character->name[CHARACTER_NAME_LEN] = '\0';
    }
    else
    {
        strcpy(character->name, name);
    }

    return OK;
}

char *character_get_gdesc(Character *character)
{
    /* Devuelve la descripción gráfica del personaje */
    if (!character)
    {
        return NULL;
    }
    return character->gdesc;
}

Status character_set_gdesc(Character *character, char *gdesc)
{
    /* Comprueba que el personaje y la descripción existan */
    if (!character || !gdesc)
    {
        return ERROR;
    }

    /* Copia la descripción gráfica */
    strcpy(character->gdesc, gdesc);

    return OK;
}

int character_get_health(Character *character)
{
    /* Devuelve la salud del personaje */
    if (!character)
    {
        return 0;
    }
    return character->health;
}

Status character_set_health(Character *character, int health)
{
    /* Actualiza la salud del personaje */
    if (!character)
    {
        return ERROR;
    }
    character->health = health;
    return OK;
}

int character_get_friendly(Character *character)
{
    /* Devuelve si el personaje es amistoso */
    if (!character)
    {
        return 0;
    }
    return character->friendly;
}

Status character_set_friendly(Character *character, int friendly)
{
    /* Actualiza el estado de amistad */
    if (!character)
    {
        return ERROR;
    }
    character->friendly = friendly;
    return OK;
}

char *character_get_message(Character *character)
{
    /* Devuelve el mensaje almacenado */
    if (!character)
    {
        return NULL;
    }
    return character->message;
}

Status character_set_message(Character *character, char *message)
{
    /* Comprueba que el personaje y el mensaje existan */
    if (!character || !message)
    {
        return ERROR;
    }

    /* Copia el mensaje del personaje */
    strcpy(character->message, message);
    return OK;
}
Id character_get_following(Character* character)
{
    /* Comprueba que el personaje exista antes de devolver el seguimiento */
    if (!character)
    {
        return NO_ID;
    }
    return character->following;
}
Status character_set_following(Character* character, Id id)
{
    /* Comprueba que el personaje exista antes de actualizar el seguimiento */
    if (!character)
    {
        return ERROR;
    }
    character->following = id;
    return OK;
}
void character_print(Character *character)
{
    /* Muestra toda la información del personaje */
    if (character != NULL)
    {
        printf("--> Character (Id: %ld; Name: %s; Gdesc: %s; Health: %d; Friendly: %d; Message: %s; Following:%ld)\n",
               character->id, character->name, character->gdesc, character->health, character->friendly, character->message, character->following);
    }
}
