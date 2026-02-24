/**
 * @brief Define el módulo del personaje
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
  * @param id El id del personaje a crear
  * @return Un puntero al personaje creado, o NULL si hubo un error
  */
Character *character_create(Id id);

/**
  * @brief Destruye un personaje
  * @author Rodrigo
  *
  * @param character Un puntero al personaje a destruir
  */
void character_destroy(Character *character);

/**
  * @brief Obtiene el id de un personaje
  * @author Rodrigo
  *
  * @param character Un puntero al personaje
  * @return El id del personaje
  */
Id character_get_id(const Character *character);

/**
  * @brief Obtiene el nombre de un personaje
  * @author Rodrigo
  *
  * @param character Un puntero al personaje
  * @return El nombre del personaje
  */
const char *character_get_name(const Character *character);

/**
  * @brief Establece el nombre de un personaje
  * @author Rodrigo
  *
  * @param character Un puntero al personaje
  * @param name Una cadena con el nuevo nombre
  * @return OK si todo fue bien, o ERROR si hubo algún error
  */
Status character_set_name(Character *character, const char *name);

/**
  * @brief Obtiene la descripción gráfica de un personaje
  * @author Profesores PPROG
  *
  * @param character Un puntero al personaje
  * @return La descripción gráfica del personaje
  */
const char *character_get_gdesc(const Character *character);

/**
  * @brief Establece la descripción gráfica de un personaje
  * @author Profesores PPROG
  *
  * @param character Un puntero al personaje
  * @param gdesc Una cadena con la nueva descripción gráfica
  * @return OK si todo fue bien, o ERROR si hubo algún error
  */
Status character_set_gdesc(Character *character, const char *gdesc);

/**
  * @brief Obtiene la salud de un personaje
  * @author Profesores PPROG
  *
  * @param character Un puntero al personaje
  * @return La salud del personaje
  */
int character_get_health(const Character *character);

/**
  * @brief Establece la salud de un personaje
  * @author Profesores PPROG
  *
  * @param character Un puntero al personaje
  * @param health La nueva salud
  * @return OK si todo fue bien, o ERROR si hubo algún error
  */
Status character_set_health(Character *character, int health);

/**
  * @brief Obtiene el estado de amistad de un personaje
  * @author Profesores PPROG
  *
  * @param character Un puntero al personaje
  * @return El estado de amistad del personaje
  */
BOOL character_get_friendly(const Character *character);

/**
  * @brief Establece el estado de amistad de un personaje
  * @author Profesores PPROG
  *
  * @param character Un puntero al personaje
  * @param friendly El nuevo estado de amistad
  * @return OK si todo fue bien, o ERROR si hubo algún error
  */
Status character_set_friendly(Character *character, BOOL friendly);

/**
  * @brief Obtiene el mensaje de un personaje
  * @author Profesores PPROG
  *
  * @param character Un puntero al personaje
  * @return El mensaje del personaje
  */
const char *character_get_message(const Character *character);

/**
  * @brief Establece el mensaje de un personaje
  * @author Profesores PPROG
  *
  * @param character Un puntero al personaje
  * @param message Una cadena con el nuevo mensaje
  * @return OK si todo fue bien, o ERROR si hubo algún error
  */
Status character_set_message(Character *character, const char *message);

/**
  * @brief Imprime la información de un personaje
  * @author Profesores PPROG
  *
  * Esta función muestra el id, nombre, descripción gráfica, salud, estado de amistad y mensaje del personaje.
  * @param character Un puntero al personaje
  */
void character_print(const Character *character);

#endif
