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

/**
   Private functions
*/

void game_actions_unknown(Game *game);
void game_actions_exit(Game *game);
void game_actions_next(Game *game);
void game_actions_back(Game *game);
void game_actions_take(Game *game);
void game_actions_drop(Game *game);
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

void game_actions_take(Game *game) {
  Id player_loc = NO_ID;
  Id obj_id = NO_ID;

  if (!game) {
    return;
  }

  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID) {
    return;
  }

  for (obj_id = 1; obj_id < 100; obj_id++) {
    if (game_get_object(game, obj_id) != NULL) {
      if (game_get_object_location(game, obj_id) == player_loc) {
        player_set_object(game_get_player(game), obj_id);
        game_set_object_location(game, NO_ID, obj_id);
        return;
      }
    }
  }
}

void game_actions_drop(Game *game)
{
  /*Author:Unai*/
  Id player_loc = NO_ID;
  Id obj_id = NO_ID;

  if (!game)
  {
    return;
  }

  player_loc = game_get_player_location(game);

  /* Obtenemos el  objeto que lleva el jugador  */
  obj_id = player_get_object(game_get_player(game));

  /* Comprobamos que el jugador lleva un objeto */
  if (obj_id != NO_ID )
  {

    /* Le quitamos al jugador el objeto */
    player_set_object(game_get_player(game), NO_ID);

    /* Ponemos el objeto en el espacio actual donde esta el jugador */
    game_set_object_location(game, player_loc, obj_id);
  }
}