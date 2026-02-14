/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Rodrigo & Unai
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"
#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

Status game_add_space(Game *game, Space *space);
Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/

Status game_create(Game *game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  game->player = player_create(0);
  game->object = object_create(0);
  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

Status game_create_from_file(Game *game, char *filename) {
  if(!game||!filename){
    return ERROR;
  }
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_reader_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  if(!player_destroy(game->player)){
    return ERROR;
  }
  if(!object_destroy(game->object)){
    return ERROR;
  }
  if(!command_destroy(game->last_cmd)){
    return ERROR;
  }

  return OK;
}

Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID||!game) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game) {
  if(game==NULL){
    return NO_ID;
  }
  return player_get_location(game->player);
}

Status game_set_player_location(Game *game, Id id) {
  if (id==NO_ID || !game) {
    return ERROR;
  }

  return player_set_location(game->player,id);
}

Id game_get_object_location(Game *game) {
  int i;
  Id id;
  Space *space;
  if(!game){
    return NO_ID;
  }
  for(i=0;i<game->n_spaces;i++){
    id=game_get_space_id_at(game,i);
    space= game_get_space(game,id);
    if(space_get_object(space)!=NO_ID){
      return id;
    }
  }
  return NO_ID;
}

Status game_set_object_location(Game *game, Id id) {
  Id temp;
  if ( !game) {
    return ERROR;
  }
  temp= game_get_object_location(game);
  if(temp!= NO_ID){
    if(space_set_object(game_get_space(game,temp),NO_ID)==ERROR){
      return ERROR;
    }
  }
  if(id!= NO_ID){
    return space_set_object(game_get_space(game,id),object_get_id(game->object));
  }
 return OK;
}

Command* game_get_last_command(Game *game) { 
  if(!game){
    return NULL;
  }
  return game->last_cmd; 
}

Status game_set_last_command(Game *game, Command *command) {
  if(!game||!command){
    return ERROR;
  }
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { 
  if(!game){
    return ERROR;
  }
  return game->finished; 
}

Status game_set_finished(Game *game, Bool finished) {
  if(!game){
    return ERROR;
  }
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  if(!game){
    printf("Ha ocurrido un problema a la hora de cargar el juego");
}
else{
  int i;
  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  player_print(game->player);
  object_print(game->object);
}
}
/**
   Implementation of private functions
*/

Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces||!game) {
    return NO_ID;
  }
  return space_get_id(game->spaces[position]);
}
