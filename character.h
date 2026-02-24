/**
 * @brief It defines the character module
 *
 * @file character.h
 * @author Rodrigo
 * @version 2.0
 * @date 23-02-2026
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

#define MAX_CHARACTERS 100
#define CHARACTER_NAME_LEN 30

typedef struct _Character Character;

/**
  * @brief Crea un nuevo personaje
  * @author Rodrigo
  *
  * @param
  */
Character *character_create(Id id);

/**
  * @brief Destruye al personaje
  * @author Rodrigo
  *
  */
void character_destroy(Character *character);

/**
  * @brief Obetiene la ID del personaje
  * @author Rodrigo
  *
  */
Id character_get_id(const Character *character);

/**
  * @brief It gets the character's name
  * @Rodrigo
  *
  */
const char *character_get_name(const Character *character);

/**
  * @brief It sets the character's name
  * @author Rodrigo
  *
  * @param puntero de personaje a personaje
  */
Status character_set_name(Character *character, const char *name);

/**
  * @brief It gets the character's graphical description
  * @author Profesores PPROG
  *
  * @param character a pointer to the character
  * @return the character's graphical description
  */
const char *character_get_gdesc(const Character *character);

/**
  * @brief It sets the character's graphical description
  * @author Profesores PPROG
  *
  * @param character a pointer to the character
  * @param gdesc a string with the new graphical description
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status character_set_gdesc(Character *character, const char *gdesc);

/**
  * @brief It gets the character's health
  * @author Profesores PPROG
  *
  * @param character a pointer to the character
  * @return the character's health
  */
int character_get_health(const Character *character);

/**
  * @brief It sets the character's health
  * @author Profesores PPROG
  *
  * @param character a pointer to the character
  * @param health the new health
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status character_set_health(Character *character, int health);

/**
  * @brief It gets the character's friendly status
  * @author Profesores PPROG
  *
  * @param character a pointer to the character
  * @return the character's friendly status
  */
BOOL character_get_friendly(const Character *character);

/**
  * @brief It sets the character's friendly status
  * @author Profesores PPROG
  *
  * @param character a pointer to the character
  * @param friendly the new friendly status
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status character_set_friendly(Character *character, BOOL friendly);

/**
  * @brief It gets the character's message
  * @author Profesores PPROG
  *
  * @param character a pointer to the character
  * @return the character's message
  */
const char *character_get_message(const Character *character);

/**
  * @brief It sets the character's message
  * @author Profesores PPROG
  *
  * @param character a pointer to the character
  * @param message a string with the new message
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status character_set_message(Character *character, const char *message);

/**
  * @brief It prints the character's information
  * @author Profesores PPROG
  *
  * This function shows the character's id, name, graphical description, health, friendly status and message.
  * @param character a pointer to the character
  */
void character_print(const Character *character);

#endif
