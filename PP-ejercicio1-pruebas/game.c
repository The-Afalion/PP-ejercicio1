#include "game.h"
#include "game_reader.h"
#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLAYER_ID 0
#define FIRST_POSITION 0
#define MAX_OBJECTS 100

struct _Game {
  Player* player;
  Object* objects[MAX_OBJECTS];
  Character* characters[MAX_CHARACTERS];
  Space *spaces[MAX_SPACES];
  int n_spaces;
  Command *last_cmd;
  int finished;
  char chat_message[WORD_SIZE];
};

/* Funciones privadas */
Status game_add_space(Game *game, Space *space);
Id game_get_space_id_at(Game *game, int position);

Status game_create(Game **game)
{
  int i;

  if (!game) {
    return ERROR;
  }

  *game = (Game*) malloc(sizeof(Game));

  if (!*game) {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES; i++) {
    (*game)->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    (*game)->objects[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    (*game)->characters[i] = NULL;
  }

  (*game)->n_spaces = 0;
  (*game)->player = player_create(PLAYER_ID);
  (*game)->last_cmd = command_create();
  (*game)->finished = 0;
  (*game)->chat_message[0] = '\0';

  return OK;
}

Status game_create_from_file(Game **game, char *filename)
{
  if (!game || !filename) {
    return ERROR;
  }

  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_spaces(*game, filename) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_objects(*game, filename) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_characters(*game, filename) == ERROR) {
    return ERROR;
  }
  
  game_set_player_location(*game, game_get_space_id_at(*game, FIRST_POSITION));

  return OK;
}

Status game_destroy(Game *game)
{
  int i;

  if (!game) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  if (game->player) {
    player_destroy(game->player);
  }
  
  for (i = 0; i < MAX_OBJECTS; i++) {
    if (game->objects[i]) {
      object_destroy(game->objects[i]);
    }
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (game->characters[i]) {
      character_destroy(game->characters[i]);
    }
  }

  if (game->last_cmd) {
    command_destroy(game->last_cmd);
  }

  free(game);

  return OK;
}

Space *game_get_space(Game *game, Id id)
{
  int i;

  if (id == NO_ID || !game) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game)
{
  if (!game) {
    return NO_ID;
  }

  return player_get_location(game->player);
}

Status game_set_player_location(Game *game, Id id)
{
  if (id == NO_ID || !game) {
    return ERROR;
  }

  return player_set_location(game->player, id);
}

Id game_get_object_location(Game *game, Id object_id)
{
  int i;

  if (!game || object_id == NO_ID) {
    return NO_ID;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_contains_object(game->spaces[i], object_id) == OK) {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

Status game_set_object_location(Game *game, Id space_id, Id object_id)
{
  Id loc_actual;
  int i;

  if (!game || object_id == NO_ID) {
    return ERROR;
  }

  loc_actual = game_get_object_location(game, object_id);

  if (loc_actual != NO_ID) {
    for (i = 0; i < game->n_spaces; i++) {
      if (space_get_id(game->spaces[i]) == loc_actual) {
        space_remove_object(game->spaces[i], object_id);
        break;
      }
    }
  }

  if (space_id != NO_ID) {
    for (i = 0; i < game->n_spaces; i++) {
      if (space_get_id(game->spaces[i]) == space_id) {
        return space_add_object(game->spaces[i], object_id);
      }
    }
  }

  return OK;
}

Id game_get_character_location(Game *game, Id character_id)
{
  int i;

  if (!game || character_id == NO_ID) {
    return NO_ID;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (space_get_character(game->spaces[i]) == character_id) {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

Status game_set_character_location(Game *game, Id space_id, Id character_id)
{
  Id loc_actual;
  int i;

  if (!game || character_id == NO_ID) {
    return ERROR;
  }

  loc_actual = game_get_character_location(game, character_id);

  if (loc_actual != NO_ID) {
    for (i = 0; i < game->n_spaces; i++) {
      if (space_get_id(game->spaces[i]) == loc_actual) {
        space_set_character(game->spaces[i], NO_ID);
        break;
      }
    }
  }

  if (space_id != NO_ID) {
    for (i = 0; i < game->n_spaces; i++) {
      if (space_get_id(game->spaces[i]) == space_id) {
        return space_set_character(game->spaces[i], character_id);
      }
    }
  }

  return OK;
}

Command *game_get_last_command(Game *game)
{
  if (!game) {
    return NULL;
  }

  return game->last_cmd;
}

Status game_set_last_command(Game *game, Command *command)
{
  if (!game || !command) {
    return ERROR;
  }

  game->last_cmd = command;

  return OK;
}

int game_get_finished(Game *game)
{
  if (!game) {
    return 0;
  }

  return game->finished;
}

Status game_set_finished(Game *game, int finished)
{
  if (!game) {
    return ERROR;
  }

  game->finished = finished;

  return OK;
}

void game_print(Game *game)
{
  int i;

  if (!game) {
    return;
  }

  printf("\n\n-------------\n\n");
  printf("=> Spaces: \n");

  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  player_print(game->player);
  
  for (i = 0; i < MAX_OBJECTS; i++) {
    if (game->objects[i]) {
      object_print(game->objects[i]);
    }
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (game->characters[i]) {
      character_print(game->characters[i]);
    }
  }
}

Player* game_get_player(Game* game) {
  if (!game) {
    return NULL;
  }

  return game->player;
}

Object* game_get_object(Game* game, Id id) {
  int i;

  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (game->objects[i] != NULL && object_get_id(game->objects[i]) == id) {
      return game->objects[i];
    }
  }

  return NULL;
}

Character* game_get_character(Game* game, Id id) {
  int i;

  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (game->characters[i] != NULL && character_get_id(game->characters[i]) == id) {
      return game->characters[i];
    }
  }

  return NULL;
}

Status game_add_object(Game *game, Object *obj) {
  int i;

  if (!game || !obj) {
    return ERROR;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (game->objects[i] == NULL) {
      game->objects[i] = obj;
      return OK;
    }
  }

  return ERROR;
}

Status game_add_character(Game *game, Character *character) {
  int i;

  if (!game || !character) {
    return ERROR;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (game->characters[i] == NULL) {
      game->characters[i] = character;
      return OK;
    }
  }

  return ERROR;
}

Status game_add_space(Game *game, Space *space)
{
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
  if (position < 0 || position >= game->n_spaces || !game) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Status game_set_chat_message(Game *game, char *message) {
  if (!game || !message) {
    return ERROR;
  }

  strncpy(game->chat_message, message, WORD_SIZE - 1);
  game->chat_message[WORD_SIZE - 1] = '\0';

  return OK;
}

char *game_get_chat_message(Game *game) {
  if (!game) {
    return NULL;
  }

  return game->chat_message;
}