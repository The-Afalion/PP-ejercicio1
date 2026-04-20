/**
 * @brief Implementa las acciones del juego
 *
 * @file game_actions.c
 * @author Unai&Rodrigo
 * @version 1.0
 * @date 15-03-2026
 * @copyright GNU Public License
 */

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
Status game_actions_recruit(Game *game);

/**
 * @brief Cuenta los aliados vivos que siguen al jugador activo en su misma sala.
 * @author Rodrigo
 *
 * @param game Puntero al juego.
 * @param attackers_ids Array de ids donde registrar a jugador y followers atacantes.
 * @param max_attackers Tamaño máximo del array attackers_ids.
 * @return Número total de atacantes válidos, incluyendo al jugador.
 */
static int game_actions_collect_attackers(Game *game, Id *attackers_ids, int max_attackers);

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
  case RECRUIT:
    status = game_actions_recruit(game);
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
  Id space_id, enemy_id;
  Space *space;
  char * enemy_name = NULL;
  Character *enemy;
  Player *player;
  int random_num;
  int player_health, char_health, n_attackers = 0, damaged_index, n_characters,i;
  Character *ally;
  Id *attackers_ids[MAX_CHARACTERS+1];
  Command *last_cmd = NULL;

  /* Verificaciones de estado del juego y jugador */
  if (!game)
  {
    return ERROR;
  }
  if (!(last_cmd = game_get_last_command(game)))
  {
    return ERROR;
  }
  enemy_name = command_get_arg(last_cmd);

  if (enemy_name = NULL)
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

  for ( i = 0; i < space_get_n_characters(space); i++)
  {
    if (space_get_character(space, i) != NO_ID)
    {
      enemy = game_get_character(game, space_get_character(space, i));
      if (enemy && strcmp(enemy_get_name(enemy), enemy_name) == 0 && character_get_friendly(enemy) == FALSE)
      {
        enemy_id = space_get_character(space, i);
        break;
      }
    }
  }
  if (enemy_id == NO_ID)
  {
    return ERROR;
  }
  /* Evalua el estatus hostil y vital del NPC */
  if (character_get_friendly(enemy))
  {
    return ERROR;
  }

  char_health = character_get_health(enemy);
  if (char_health <= 0)
  {
    return ERROR;
  }
  if ((n_characters = game_get_number_of_characters(game)) == -1)
  {
    return ERROR;
  }
  if ((*attackers_ids = game_get_players_followers(game)) == NULL)
  {
    return ERROR;
  }
  if ((n_attackers = game_get_number_of_followers_of_player(game)) == -1)
  {
    return ERROR;
  }
  attackers_ids[n_attackers++] = player_get_id(game_get_player(game));
  
  random_num = rand() % 10;

  /* >4 haces daño al enemigo*/
  if (random_num <= 4)
  {
    damaged_index = rand() % n_attackers;

    if (attackers_ids[damaged_index] == player_get_id(player))
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
      ally = game_get_character(game, attackers_ids[damaged_index]);
      if (!ally)
      {
        return ERROR;
      }

      char_health = character_get_health(ally);
      char_health--;
      character_set_health(ally, char_health);
    }
  }
  else
  {
    char_health -= n_attackers;
    character_set_health(enemy, char_health);
  }

  return OK;
}

Status game_actions_chat(Game *game)
{
  Id space_id, char_id;
  Space *space;
  Character *character;
  Command *last_cmd = NULL;
  int i = 0;
  char *arg = NULL;
  

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
  if (!(last_cmd = game_get_last_command(game)))
  {
    return ERROR;
  }
  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0')
  {
    return ERROR;
  }
    for ( i = 0; i < space_get_n_characters(space); i++)
    {
      if (space_get_character(space, i) != NO_ID)
      {
        character = game_get_character(game, space_get_character(space, i));
        if (character && strcmp(character_get_name(character), arg) == 0 && character_get_friendly(character) == TRUE)
        {
          char_id = space_get_character(space, i);
          break;
        }
      }
    }
    
  if (char_id == NO_ID)
  {
    return ERROR;
  }

  character = game_get_character(game, char_id);
  if (!character)
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

Status game_actions_recruit(Game *game)
{
  Id space_id, char_id;
  Space *space = NULL;
  Character *character = NULL;
  Player *player = NULL;
  char *arg = NULL, *name = NULL;
  Command *last_cmd = NULL;
  int i;
  BOOL found = FALSE;

  if (!game)
  {
    return ERROR;
  }
  /*Comprueba la validez del comando */
  if (!(last_cmd = game_get_last_command(game)))
  {
    return ERROR;
  }
  /*Comprueba que haya argumento (personaje a reclutar)*/
  if (!(arg = command_get_arg(last_cmd)))
  {
    return ERROR;
  }

  if (!(player = game_get_player(game)))
  {
    return ERROR;
  }
  if (!(space = player_get_space(player)))
  {
    return ERROR;
  }

  /*Busca personajes en el juego y si tiene el mismo nombre que arg[1] entonces se sale del bucle*/
  for (i = 0; i < game_get_number_of_characters(game); i++)
  {
    if (!(character = game_get_character_from_index(game, i)))
    {
      return ERROR;
    }
    if (!(name = character_get_name(character)))
    {
      return ERROR;
    }
    if (strcmp(name, arg) == 0)
    {
      found = TRUE;
      break;
    }
  }
  /*Comprueba si se encontró el personaje o si no es amigable*/
  if (found == FALSE || character_get_friendly(character) == FALSE)
  {
    return ERROR;
  }

  if (character_set_following(character, player_get_id(game_get_player(game))) == ERROR)
  {

    return ERROR;
  }

  return OK;
}