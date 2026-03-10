/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

#define GDESC_ROWS 5
#define GDESC_COLS 10

typedef struct Space Space;

/**
 * @brief It creates a new space
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the id of the space located at the north
 */
Status space_set_north(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the north
 */
Id space_get_north(Space* space);

/**
 * @brief It sets the id of the space located at the south
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the south
 */
Id space_get_south(Space* space);

/**
 * @brief It sets the id of the space located at the east
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the east
 */
Id space_get_east(Space* space);

/**
 * @brief It sets the id of the space located at the west
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the west
 */
Id space_get_west(Space* space);

/**
 * @brief It sets the object in the space
 */
Status space_set_object(Space* space, Id object_id);

/**
 * @brief It gets the object from the space
 */
Id* space_get_object(Space* space);

/**
 * @brief It prints the space information
 */
Status space_print(Space* space);

/**
 * @brief It adds an object to the space
 */
Status space_add_object(Space* space, Id object_id);

/**
 * @brief It removes an object from the space
 */
Status space_remove_object(Space* space, Id object_id);

/**
 * @brief It gets the objects in the space
 */
int* space_get_objects(Space* space);

/**
 * @brief It gets the number of objects in the space
 */
int space_get_number_of_objects(Space* space);

/**
 * @brief It checks if the space contains an object
 */
Status space_contains_object(Space* space, Id id);

/**
 * @brief It sets the character in the space
 */
Status space_set_character(Space* space, Id id);

/**
 * @brief It gets the character in the space
 */
Id space_get_character(Space* space);

/**
 * @brief It sets the graphic description of the space
 */
Status space_set_gdesc(Space* space, char gdesc[GDESC_ROWS][GDESC_COLS]);

/**
 * @brief It gets the graphic description of the space
 */
char(* space_get_gdesc(Space* space))[GDESC_COLS];

#endif