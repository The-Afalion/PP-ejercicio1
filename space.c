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
  newSpace->objects = set_create(NO_ID);
  newSpace->character = NO_ID;

  return newSpace;
}

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

Status space_add_object(Space *space, Id object_id)
{
  if (!space)
  {
    return ERROR;
  }
  return set_add(space->objects, object_id);
}

Status space_remove_object(Space *space, Id object_id)
{
  if (!space)
  {
    return ERROR;
  }
  return set_del(space->objects, object_id);
}

int* space_get_objects(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return set_get_ids(space->objects);
}

int space_get_number_of_objects(Space *space)
{
  if (!space)
  {
    return -1;
  }
  return set_get_numberid(space->objects);
}

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

Status space_set_character(Space *space, Id id)
{
  if (!space)
  {
    return ERROR;
  }
  space->character = id;
  return OK;
}

Id space_get_character(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->character;
}

Status space_print(Space *space)
{
  Id idaux = NO_ID;
  int i, num_objs;
  int *objs = NULL;

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

  num_objs = space_get_number_of_objects(space);
  if (num_objs > 0)
  {
    objs = space_get_objects(space);
    fprintf(stdout, "---> Objects in the space (Id: ");
    for (i = 0; i < num_objs; i++)
    {
      fprintf(stdout, "%d ", objs[i]);
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