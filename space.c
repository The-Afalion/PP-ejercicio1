/**
 * @brief It implements the space module
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
 * @brief Space
 * This struct stores all the information of a space.
 */
struct Space
{
  Id id;
  char name[WORD_SIZE + SINGLE_ELEM];
  Id north;
  Id south;
  Id east;
  Id west;
  Id object;
};

Space *space_create(Id id)
{
  Space *newSpace = NULL;

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
  newSpace->object = NO_ID;

  return newSpace;
}

Status space_destroy(Space *space)
{

  if (!space)
  {
    return ERROR;
  }

  free(space);
  return OK;
}

Id space_get_id(Space *space)
{

  if (!space)
  {
    return NO_ID;
  }
  return space->id;
}

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

const char *space_get_name(Space *space)
{

  if (!space)
  {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space *space, Id id)
{

  if (!space || id == NO_ID)
  {
    return ERROR;
  }

  space->east = id;
  return OK;
}

Id space_get_east(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space *space, Id id)
{

  if (!space || id == NO_ID)
  {
    return ERROR;
  }

  space->west = id;
  return OK;
}

Id space_get_west(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->west;
}

Status space_set_object(Space *space, Id value)
{

  if (!space)
  {
    return ERROR;
  }
  space->object = value;
  return OK;
}

Id space_get_object(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->object;
}

Status space_print(Space *space)
{
  Id idaux = NO_ID;

  if (!space)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No west link.\n");
  }

  if (space_get_object(space) != NO_ID)
  {
    fprintf(stdout, "---> Object in the space (Id: %ld).\n", space->object);
  }
  else
  {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
