#include "game_actions.h"
#include "inventory.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Status game_actions_unknown(Game *game);
Status game_actions_exit(Game *game);
Status game_actions_move(Game *game);
Status game_actions_take(Game *game);
Status game_actions_drop(Game *game);
Status game_actions_attack(Game *game);
Status game_actions_chat(Game *game);
Status game_actions_inspect(Game *game);

Status game_actions_update(Game *game, Command *command)
{
  CommandCode cmd;
  Status status = OK;

  game_set_last_command(game, command);
  cmd = command_get_code(command);

  /* Distribucion de la ejecucion segun el codigo del comando */
  switch (cmd)
  {
  case UNKNOWN:
    status = game_actions_unknown(game);
    break;
  case EXIT:
    status = game_actions_exit(game);
    break;
  case TAKE:
    status = game_actions_take(game);
    break;
  case DROP:
    status = game_actions_drop(game);
    break;
  case ATTACK:
    status = game_actions_attack(game);
    break;
  case CHAT:
    status = game_actions_chat(game);
    break;
  case MOVE:
    status = game_actions_move(game);
    break;
  case INSPECT:
    status = game_actions_inspect(game);
    break;
  default:
    break;
  }

  return status;
}

Status game_actions_unknown(Game *game)
{
  return ERROR;
}

Status game_actions_exit(Game *game)
{
  return OK;
}

Status game_actions_move(Game *game)
{
  Id current_space_id = NO_ID, destination_id = NO_ID;
  char *arg = NULL;
  Directions dir = U;
  Command *last_cmd = NULL;
  Space *dest_space = NULL;

  /* Comprueba la validez del puntero */
  if (!game)
  {
    return ERROR;
  }

  /* Obtiene la direccion introducida */
  last_cmd = game_get_last_command(game);
  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0')
  {
    return ERROR;
  }

  /* Traduccion del argumento a la direccion enumerada */
  if (strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0)
  {
    dir = N;
  }
  else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0)
  {
    dir = S;
  }
  else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0)
  {
    dir = W;
  }
  else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0)
  {
    dir = E;
  }

  /* Obtiene la ubicacion actual del jugador activo */
  current_space_id = game_get_player_location(game);
  if (current_space_id == NO_ID)
  {
    return ERROR;
  }

  /* Comprueba la viabilidad del movimiento */
  if (dir == U || game_connection_is_open(game, current_space_id, dir) == FALSE)
  {
    return ERROR;
  }

  destination_id = game_get_connection(game, current_space_id, dir);
  if (destination_id == NO_ID)
  {
    return ERROR;
  }

  /* Aplica el desplazamiento al destino */
  if (destination_id != NO_ID)
  {
    game_set_player_location(game, destination_id);
    dest_space = game_get_space(game, destination_id);
    if (dest_space != NULL)
    {
      space_set_discovered(dest_space, TRUE);
    }
    return OK;
  }

  return ERROR;
}

Status game_actions_take(Game *game)
{
  Id player_loc = NO_ID;
  Id obj_id = NO_ID;
  Space *space = NULL;
  int num_objs = 0;
  int i = 0;
  Id *objs = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;
  Object *obj = NULL;

  /* Comprueba la validez del puntero */
  if (!game)
  {
    return ERROR;
  }

  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID)
  {
    return ERROR;
  }

  space = game_get_space(game, player_loc);
  if (!space)
  {
    return ERROR;
  }

  last_cmd = game_get_last_command(game);
  if (!last_cmd)
  {
    return ERROR;
  }

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0')
  {
    return ERROR;
  }

  /* Comprueba la disponibilidad en el inventario */
  if (inventory_is_full(player_get_backpack(game_get_player(game))) == TRUE)
  {
    return ERROR;
  }

  num_objs = space_get_number_of_objects(space);

  if (num_objs > 0)
  {
    objs = space_get_objects(space);

    if (objs)
    {
      /* Busca el objeto especifico solicitado por nombre */
      for (i = 0; i < num_objs; i++)
      {
        obj = game_get_object(game, objs[i]);

        if (obj != NULL && object_get_name(obj) != NULL)
        {
          if (strcmp(object_get_name(obj), arg) == 0)
          {
            obj_id = objs[i];
            break;
          }
        }
      }

      /* Gestion de la transferencia de objeto */
      if (obj_id != NO_ID)
      {
        player_add_object(game_get_player(game), obj_id);
        game_set_object_location(game, NO_ID, obj_id);
        return OK;
      }
    }
  }

  return ERROR;
}

Status game_actions_drop(Game *game)
{
  Id player_loc = NO_ID;
  Id obj_id = NO_ID;
  Command *last_cmd = NULL;
  Object *obj;
  char *arg = NULL;
  int i, max_objects;

  /* Comprueba la validez del puntero */
  if (!game)
  {
    return ERROR;
  }

  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID)
  {
    return ERROR;
  }

  last_cmd = game_get_last_command(game);
  if (!last_cmd)
  {
    return ERROR;
  }

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0')
  {
    return ERROR;
  }

  max_objects = inventory_get_max_objs(player_get_backpack(game_get_player(game)));

  /* Busqueda secuencial en el inventario del jugador */
  for (i = 0; i < max_objects; i++)
  {
    obj_id = player_get_object(game_get_player(game), i);
    if (obj_id != NO_ID)
    {
      obj = game_get_object(game, obj_id);

      if (obj != NULL && object_get_name(obj) != NULL)
      {
        if (strcmp(object_get_name(obj), arg) == 0)
        {
          /* Eliminacion y reubicacion del objeto */
          player_del_object(game_get_player(game), obj_id);
          game_set_object_location(game, player_loc, obj_id);
          return OK;
        }
      }
    }
  }

  return ERROR;
}

Status game_actions_attack(Game *game)
{
  Id space_id, char_id;
  Space *space;
  Character *character;
  Player *player;
  int random_num;
  int player_health, char_health;

  /* Verificaciones de estado del juego y jugador */
  if (!game)
  {
    return ERROR;
  }

  player = game_get_player(game);
  if (!player)
  {
    return ERROR;
  }

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return ERROR;
  }

  space = game_get_space(game, space_id);
  if (!space)
  {
    return ERROR;
  }

  char_id = space_get_character(space);
  if (char_id == NO_ID)
  {
    return ERROR;
  }

  character = game_get_character(game, char_id);
  if (!character)
  {
    return ERROR;
  }

  /* Evalua el estatus hostil y vital del NPC */
  if (character_get_friendly(character))
  {
    return ERROR;
  }

  char_health = character_get_health(character);
  if (char_health <= 0)
  {
    return ERROR;
  }

  /* Evaluacion matematica del resultado del ataque */
  random_num = rand() % 10;

  if (random_num <= 4)
  {
    player_health = player_get_health(player);
    player_health--;
    player_set_health(player, player_health);

    if (player_health <= 0)
    {
      game_set_finished(game, 1);
    }
  }
  else
  {
    char_health--;
    character_set_health(character, char_health);
  }

  return OK;
}

Status game_actions_chat(Game *game)
{
  Id space_id, char_id;
  Space *space;
  Character *character;

  /* Comprobaciones de integridad en la ubicacion actual */
  if (!game)
  {
    return ERROR;
  }

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return ERROR;
  }

  space = game_get_space(game, space_id);
  if (!space)
  {
    return ERROR;
  }

  char_id = space_get_character(space);
  if (char_id == NO_ID)
  {
    return ERROR;
  }

  character = game_get_character(game, char_id);
  if (!character)
  {
    return ERROR;
  }

  /* Verificacion de estatus conversacional */
  if (character_get_friendly(character) == 0)
  {
    return ERROR;
  }
  if (character_get_health(character) <= 0)
  {
    return ERROR;
  }

  /* Registro del mensaje en la memoria global */
  game_set_chat_message(game, character_get_message(character));
  return OK;
}

Status game_actions_inspect(Game *game)
{
  char *arg;
  int i, max_backpac_obj, num_obj_in_space;
  Space *space = NULL;
  Command *last_cmd = NULL;
  Object *obj = NULL;
  Id player_loc = NO_ID, obj_id = NO_ID, *objs = NULL;
  Player *player = NULL;
  BOOL found = FALSE;

  /* Comprueba validez del comando e identificacion de variable */
  if (!game)
  {
    return ERROR;
  }

  last_cmd = game_get_last_command(game);
  if (!last_cmd)
  {
    return ERROR;
  }

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0')
  {
    return ERROR;
  }

  player = game_get_player(game);
  if (!player)
  {
    return ERROR;
  }

  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID)
  {
    return ERROR;
  }

  space = game_get_space(game, player_loc);
  if (!space)
  {
    return ERROR;
  }

  /* Inspeccion de inventario primario */
  max_backpac_obj = inventory_get_max_objs(player_get_backpack(player));
  for (i = 0; i < max_backpac_obj; i++)
  {
    obj_id = player_get_object(player, i);
    if (obj_id != NO_ID)
    {
      obj = game_get_object(game, obj_id);
      if (obj == NULL)
      {
        return ERROR;
      }

      if (strcmp(object_get_name(obj), arg) == 0)
      {
        found = TRUE;
        break;
      }
    }
  }

  /* Inspeccion secundaria en entorno del espacio activo */
  if (!found && space)
  {
    num_obj_in_space = space_get_number_of_objects(space);
    if (num_obj_in_space == 0)
    {
      return ERROR;
    }

    objs = space_get_objects(space);
    if (objs)
    {
      for (i = 0; i < num_obj_in_space; i++)
      {
        obj = game_get_object(game, objs[i]);
        if (obj && strcmp(object_get_name(obj), arg) == 0)
        {
          found = TRUE;
          break;
        }
      }
    }
  }

  /* Guardado logico para despliegue posterior */
  if (obj && found)
  {
    game_set_object_desc(game, object_get_desc(obj));
    return OK;
  }

  return ERROR;
}
