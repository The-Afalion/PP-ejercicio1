/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "space.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SINGLE_ELEM 1
#define FIRST_CHAR 0

struct Space
{
  Id id;
  char name[WORD_SIZE + SINGLE_ELEM];
  Id north;
  Id south;
  Id east;
  Id west;
  Set *objects; 
  Id character;
  char gdesc[GDESC_ROWS][GDESC_COLS];
};

/**
 * @brief It creates a new space
 */
Space *space_create(Id id)
{
  Space *newSpace = NULL;
  int i, j;

  if (id == NO_ID)
  {
    return NULL;
  }

  newSpace = (Space *)calloc(SINGLE_ELEM, sizeof(Space));

  if (newSpace == NULL)
  {
    return NULL;
  }

  newSpace->id = id;
  newSpace->name[FIRST_CHAR] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create(NO_ID);
  newSpace->character = NO_ID;

  for (i = 0; i < GDESC_ROWS; i++) {
    for (j = 0; j < GDESC_COLS - 1; j++) {
      newSpace->gdesc[i][j] = ' ';
    }
    newSpace->gdesc[i][GDESC_COLS - 1] = '\0';
  }

  return newSpace;
}

/**
 * @brief It destroys a space
 */
Status space_destroy(Space *space)
{
  if (!space)
  {
    return ERROR;
  }

  if (space->objects)
  {
    set_destroy(space->objects);
  }

  free(space);
  return OK;
}

/**
 * @brief It gets the id of a space
 */
Id space_get_id(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->id;
}

/**
 * @brief It sets the name of a space
 */
Status space_set_name(Space *space, char *name)
{
  if (!space || !name)
  {
    return ERROR;
  }

  if (!strcpy(space->name, name))
  {
    return ERROR;
  }
  return OK;
}

/**
 * @brief It gets the name of a space
 */
const char *space_get_name(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return space->name;
}

/**
 * @brief It sets the id of the space located at the north
 */
Status space_set_north(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->north = id;
  return OK;
}

/**
 * @brief It gets the id of the space located at the north
 */
Id space_get_north(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->north;
}

/**
 * @brief It sets the id of the space located at the south
 */
Status space_set_south(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->south = id;
  return OK;
}

/**
 * @brief It gets the id of the space located at the south
 */
Id space_get_south(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->south;
}

/**
 * @brief It sets the id of the space located at the east
 */
Status space_set_east(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->east = id;
  return OK;
}

/**
 * @brief It gets the id of the space located at the east
 */
Id space_get_east(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->east;
}

/**
 * @brief It sets the id of the space located at the west
 */
Status space_set_west(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->west = id;
  return OK;
}

/**
 * @brief It gets the id of the space located at the west
 */
Id space_get_west(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->west;
}

/**
 * @brief It adds an object to the space
 */
Status space_add_object(Space *space, Id object_id)
{
  if (!space)
  {
    return ERROR;
  }
  return set_add(space->objects, object_id);
}

/**
 * @brief It removes an object from the space
 */
Status space_remove_object(Space *space, Id object_id)
{
  if (!space)
  {
    return ERROR;
  }
  return set_del(space->objects, object_id);
}

/**
 * @brief It gets the objects in the space
 */
Id* space_get_objects(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return set_get_ids(space->objects);
}

/**
 * @brief It gets the number of objects in the space
 */
int space_get_number_of_objects(Space *space)
{
  if (!space)
  {
    return -1;
  }
  return set_get_numberid(space->objects);
}

/**
 * @brief It checks if the space contains an object
 */
Status space_contains_object(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  if (set_find(space->objects, id) == OK)
  {
    return OK;
  }
  return ERROR;
}

/**
 * @brief It sets the character in the space
 */
Status space_set_character(Space *space, Id id)
{
  if (!space)
  {
    return ERROR;
  }
  space->character = id;
  return OK;
}

/**
 * @brief It gets the character in the space
 */
Id space_get_character(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->character;
}

/**
 * @brief It sets the graphic description of the space
 */
Status space_set_gdesc(Space* space, char gdesc[GDESC_ROWS][GDESC_COLS]) {
  int i;

  if (!space || !gdesc) {
    return ERROR;
  }

  for (i = 0; i < GDESC_ROWS; i++) {
    if (strlen(gdesc[i]) == GDESC_COLS - 1) {
     if( !strcpy(space->gdesc[i],gdesc[i])){
      return ERROR;
     }
    } else {
      strcpy(space->gdesc[i], "         ");
    }
  }

  return OK;
}

/**
 * @brief It gets the graphic description of the space
 */
char (*space_get_gdesc(Space* space))[GDESC_COLS] {
  if (!space) {
    return NULL;
  }

  return space->gdesc;
}

/**
 * @brief It prints the space information
 */
Status space_print(Space *space)
{
  Id idaux = NO_ID;
  int i, num_objs;
  Id *objs = NULL;

  if (!space)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  fprintf(stdout, "---> North link: %ld.\n", idaux);

  idaux = space_get_south(space);
  fprintf(stdout, "---> South link: %ld.\n", idaux);

  idaux = space_get_east(space);
  fprintf(stdout, "---> East link: %ld.\n", idaux);

  idaux = space_get_west(space);
  fprintf(stdout, "---> West link: %ld.\n", idaux);

  fprintf(stdout, "---> Character in space: %ld.\n", space->character);

  fprintf(stdout, "---> Graphic description:\n");
  for (i = 0; i < GDESC_ROWS; i++) {
    fprintf(stdout, "%s\n", space->gdesc[i]);
  }

  num_objs = space_get_number_of_objects(space);
  if (num_objs > 0)
  {
    objs = space_get_objects(space);
    fprintf(stdout, "---> Objects in the space (Id: ");
    for (i = 0; i < num_objs; i++)
    {
      fprintf(stdout, "%d ", (int) objs[i]);
    }
    fprintf(stdout, ")\n");
    
    if (objs)
    {
      free(objs);
    }
  }
  else
  {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}