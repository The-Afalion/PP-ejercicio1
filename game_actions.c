/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/**
   Private functions
*/

void game_actions_unknown(Game *game);
void game_actions_exit(Game *game);
void game_actions_next(Game *game);
void game_actions_back(Game *game);
void game_actions_take(Game *game);
void game_actions_drop(Game *game);
void game_actions_attack(Game*game);
void game_actions_chat(Game* game);
void game_actions_left(Game *game);
void game_actions_right(Game *game);
/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command)
{
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd)
  {
  case UNKNOWN:
    game_actions_unknown(game);
    break;

  case EXIT:
    game_actions_exit(game);
    break;

  case NEXT:
    game_actions_next(game);
    break;

  case BACK:
    game_actions_back(game);
    break;

  case TAKE:
    game_actions_take(game);
    break;

  case DROP:
    game_actions_drop(game);
    break;
  case ATTACK:
    game_actions_attack(game);
    break;
  case CHAT:
    game_actions_chat(game);
    break;
  case LEFT:
     game_actions_left(game);
     break;
  case RIGHT:
    game_actions_right(game);
    break;
    

  default:
    break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
  }

  return;
}
void game_actions_take(Game *game)
{
  Id player_loc = NO_ID;
  Id obj_id = NO_ID;
  Space *space = NULL;
  int num_objs = 0;
  int i = 0;
  int *objs = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;
  Object *obj = NULL;

  if (!game) {
    return;
  }

  player_loc = game_get_player_location(game);

  if (player_loc == NO_ID) {
    return;
  }

  space = game_get_space(game, player_loc);

  if (!space) {
    return;
  }

  last_cmd = game_get_last_command(game);

  if (!last_cmd) {
    return;
  }

  arg = command_get_arg(last_cmd);

  if (!arg || arg[0] == '\0') {
    return;
  }

  /* Si el jugador ya lleva un objeto, no puede coger otro */
  if (player_get_object(game_get_player(game)) != NO_ID) {
    return;
  }

  num_objs = space_get_number_of_objects(space);

  if (num_objs > 0) {
    objs = space_get_objects(space);

    if (objs) {
      for (i = 0; i < num_objs; i++) {
        obj = game_get_object(game, objs[i]);

        if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0) {
          obj_id = objs[i];
          break;
        }
      }

      if (obj_id != NO_ID) {
        player_set_object(game_get_player(game), obj_id);
        space_remove_object(space, obj_id);
      }

      free(objs);
    }
  }
}

void game_actions_drop(Game *game)
{
  Id player_loc = NO_ID;
  Id obj_id = NO_ID;
  Space *space = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;
  Object *obj = NULL;

  if (!game) {
    return;
  }

  player_loc = game_get_player_location(game);

  if (player_loc == NO_ID) {
    return;
  }

  space = game_get_space(game, player_loc);

  if (!space) {
    return;
  }

  last_cmd = game_get_last_command(game);

  if (!last_cmd) {
    return;
  }

  arg = command_get_arg(last_cmd);

  if (!arg || arg[0] == '\0') {
    return;
  }

  obj_id = player_get_object(game_get_player(game));

  if (obj_id != NO_ID) {
    obj = game_get_object(game, obj_id);

    /* Comprobamos que el nombre del objeto que lleva coincide con lo que ha escrito */
    if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0) {
      player_set_object(game_get_player(game), NO_ID);
      space_add_object(space, obj_id);
    }
  }
}
void game_actions_attack(Game *game)
{
  Id space_id, char_id;
  Space *space;
  Character *character;
  Player *player;
  int random_num;
  int player_health, char_health;

  if (!game) {
    return;
  }

  player = game_get_player(game);
  if (!player) {
    return;
  }

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  space = game_get_space(game, space_id);
  if (!space) {
    return;
  }

  char_id = space_get_character(space);
  if (char_id == NO_ID) {
    return;
  }

  character = game_get_character(game, char_id);
  if (!character) {
    return;
  }

  /* No se puede atacar si es amigo */
  if (character_get_friendly(character)) {
    return;
  }

  char_health = character_get_health(character);
  
  /* Si la salud es 0 o menos, ya está muerto, no se le ataca */
  if (char_health <= 0) {
    return;
  }
  random_num = rand() % 10;

  if (random_num <= 4) {
    /* Gana el adversario: el jugador pierde 1 punto de vida */
    player_health = player_get_health(player);
    player_health--;
    player_set_heatlh(player, player_health); /* Ojo al typo que tienes en player.h */

    /* Si el jugador se queda sin vida, termina el juego */
    if (player_health <= 0) {
      game_set_finished(game, 1);
    }
  } else {
    /* Gana el jugador: el personaje pierde 1 punto de vida */
    char_health--;
    character_set_health(character, char_health);
  }
}
void game_actions_chat(Game* game) {
  Id space_id;
  Id char_id;
  Space *space;
  Character *character;

  if (!game) {
    return;
  }

  space_id = game_get_player_location(game);

  if (space_id == NO_ID) {
    return;
  }

  space = game_get_space(game, space_id);

  if (!space) {
    return;
  }

  char_id = space_get_character(space);

  if (char_id == NO_ID) {
    return;
  }

  character = game_get_character(game, char_id);

  if (!character) {
    return;
  }

  if (character_get_friendly(character) == 0) {
    return;
  }

  if (character_get_health(character) <= 0) {
    return;
  }

  game_set_chat_message(game, character_get_message(character));
}
void game_actions_left(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);

    if (NO_ID == space_id)
    {
        return;
    }

    current_id = space_get_west(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        game_set_player_location(game, current_id);
    }

    return;
}

void game_actions_right(Game *game)
{
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);

    if (NO_ID == space_id)
    {
        return;
    }

    current_id = space_get_east(game_get_space(game, space_id));
    if (current_id != NO_ID)
    {
        game_set_player_location(game, current_id);
    }

    return;
}