/**
 * @brief Implementa la estructura del juego
 *
 * @file game.c
 * @author Unai
 * @version 2.0
 * @date 15-02-2026
 * @copyright GNU Public License
 */

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
#define CHARACTER_ID 0
#define FIRST_POSITION 0

/**
 * @brief Estructura principal de Game
 */
struct _Game {
  Player* player;
  Object* objects[MAX_OBJECTS];
  Character* character[MAX_CHARACTERS];
  Space *spaces[MAX_SPACES];
  int n_spaces;
  int n_objects;
  int n_characters;
  Command *last_cmd;
  int finished;
};

/**
   Funciones privadas
*/
Status game_add_space(Game *game, Space *space);
Id game_get_space_id_at(Game *game, int position);

/**
   Implementación de la interfaz del juego
*/

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


  for (i = 0; i < MAX_SPACES; i++)
  {
    (*game)->spaces[i] = NULL;
  }
    for (i = 0; i < MAX_OBJECTS; i++)
  {
    (*game)->objects[i] = NULL;
  }

  (*game)->n_spaces = 0;
  (*game)->n_objects = 0;
  (*game)->n_characters = 0;
  (*game)->player = player_create(PLAYER_ID);
  for(i=0;i<MAX_CHARACTERS;i++){
    (*game)->character[i] = NULL;
  }
  (*game)->last_cmd = command_create();
  (*game)->finished = 0;

  return OK;
}

Status game_create_from_file(Game **game, char *filename)
{
  if (!game || !filename)
  {
    return ERROR;
  }

  if (game_create(game) == ERROR)
  {
    return ERROR;
  }

  if (game_reader_load_spaces(*game, filename) == ERROR)
  {
    return ERROR;
  }

  if (game_reader_load_objects(*game, filename) == ERROR)
  {
    return ERROR;
  }

  if (game_reader_load_characters(*game, filename) == ERROR)
  {
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

  for (i = 0; i < game->n_spaces; i++)
  {
    space_destroy(game->spaces[i]);
  }

    for (i = 0; i < game->n_objects; i++)
  {
    object_destroy(game->objects[i]);
  }

  for (i = 0; i < game->n_characters; i++)
  {
    character_destroy(game->character[i]);
  }

  if (game->player && player_destroy(game->player) != OK)
  {
    return ERROR;
  }

  if (game->last_cmd && command_destroy(game->last_cmd) != OK)
  {
    return ERROR;
  }

  free(game);

  return OK;
}

Status game_add_object(Game *game, Object *object) {
    if ((object == NULL) || (game->n_objects >= MAX_OBJECTS)) {
        return ERROR;
    }
    game->objects[game->n_objects] = object;
    game->n_objects++;
    return OK;
}

Status game_add_character(Game *game, Character *character) {
    if ((character == NULL) || (game->n_characters >= MAX_CHARACTERS)) {
        return ERROR;
    }
    game->character[game->n_characters] = character;
    game->n_characters++;
    return OK;
}

Space *game_get_space(Game *game, Id id)
{
  int i;

  if (id == NO_ID || !game)
  {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game)
{
  if (game == NULL)
  {
    return NO_ID;
  }
  return player_get_location(game->player);
}

Status game_set_player_location(Game *game, Id id)
{
  if (id == NO_ID || !game)
  {
    return ERROR;
  }

  return player_set_location(game->player, id);
}

Id game_get_object_location(Game *game, Id object_id) {
    int i;
    if (!game) {
        return NO_ID;
    }
    for (i = 0; i < game->n_spaces; i++) {
        if (space_has_object(game->spaces[i], object_id)) {
            return space_get_id(game->spaces[i]);
        }
    }
    return NO_ID;
}

Status game_set_object_location(Game *game, Id space_id, Id object_id) {
    Id old_loc_id;
    Space *old_space, *new_space;

    if (!game) {
        return ERROR;
    }

    old_loc_id = game_get_object_location(game, object_id);
    if (old_loc_id != NO_ID) {
        old_space = game_get_space(game, old_loc_id);
        space_del_object(old_space, object_id);
    }

    if (space_id != NO_ID) {
        new_space = game_get_space(game, space_id);
        space_add_object(new_space, object_id);
    }

    return OK;
}

Command *game_get_last_command(Game *game)
{
  if (!game)
  {
    return NULL;
  }
  return game->last_cmd;
}

Status game_set_last_command(Game *game, Command *command)
{
  if (!game || !command)
  {
    return ERROR;
  }
  game->last_cmd = command;

  return OK;
}

int game_get_finished(Game *game)
{
  if (!game)
  {
    return 0;
  }
  return game->finished;
}

Status game_set_finished(Game *game, int finished)
{
  if (!game)
  {
    return ERROR;
  }
  game->finished = finished;

  return OK;
}

void game_print(Game *game)
{
  if (!game)
  {
    printf("Ha ocurrido un problema a la hora de cargar el juego");
  }
  else
  {
    int i;
    printf("\n\n-------------\n\n");
    printf("=> Spaces: \n");

    for (i = 0; i < game->n_spaces; i++)
    {
      space_print(game->spaces[i]);
    }

    player_print(game->player);
    for (i = 0; i < game->n_objects; i++) {
        object_print(game->objects[i]);
    }
    for (i = 0; i < game->n_characters; i++) {
        character_print(game->character[i]);
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
    for (i = 0; i < game->n_objects; i++) {
        if (object_get_id(game->objects[i]) == id) {
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
    for (i = 0; i < game->n_characters; i++) {
        if (character_get_id(game->character[i]) == id) {
            return game->character[i];
        }
    }
    return NULL;
}

Status game_add_space(Game *game, Space *space)
{
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES))
  {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
  if (position < 0 || position >= game->n_spaces || !game)
  {
    return NO_ID;
  }
  return space_get_id(game->spaces[position]);
}
