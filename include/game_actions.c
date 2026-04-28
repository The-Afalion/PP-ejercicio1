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
#include  "game_managment.h"
#include "inventory.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
Status game_actions_abandon(Game *game);
Status game_actions_use(Game *game);
Status game_actions_open(Game *game);
Status game_actions_save(Game *game);
Status game_actions_load(Game *game);

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
  case ABANDON:
    status = game_actions_abandon(game);
    break;
  case USE:
    status = game_actions_use(game);
    break;
  case OPEN:
    status = game_actions_open(game);
    break;
  case LOAD:
   status = game_actions_load(game);
   break;
  case SAVE:
  status= game_actions_save(game);
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
  Id player_id = NO_ID;
  char **arg = NULL;
  Directions dir = NO_DIRECTION;
  Command *last_cmd = NULL;
  Space *dest_space = NULL;
  Character *character = NULL;
  int i = 0;

  /* Comprueba la validez del puntero */
  if (!game)
  {
    return ERROR;
  }

  /* Obtiene la direccion introducida */
  last_cmd = game_get_last_command(game);
  arg = command_get_arg(last_cmd);

  if (arg == NULL || arg[0][0] == '\0')
  {
    return ERROR;
  }

  /* Traduccion del argumento a la direccion enumerada */
  if (strcasecmp(arg[0], "north") == 0 || strcasecmp(arg[0], "n") == 0)
  {
    dir = N;
  }
  else if (strcasecmp(arg[0], "south") == 0 || strcasecmp(arg[0], "s") == 0)
  {
    dir = S;
  }
  else if (strcasecmp(arg[0], "west") == 0 || strcasecmp(arg[0], "w") == 0)
  {
    dir = W;
  }
  else if (strcasecmp(arg[0], "east") == 0 || strcasecmp(arg[0], "e") == 0)
  {
    dir = E;
  }
  else if (strcasecmp(arg[0], "up") == 0 || strcasecmp(arg[0], "u") == 0)
  {
    dir = U;
  }
  else if (strcasecmp(arg[0], "down") == 0 || strcasecmp(arg[0], "d") == 0)
  {
    dir = D;
  }

  /* Obtiene la ubicacion actual del jugador activo */
  current_space_id = game_get_player_location(game);
  if (current_space_id == NO_ID)
  {
    return ERROR;
  }

  /* Comprueba la viabilidad del movimiento */
  if (dir == NO_DIRECTION || game_connection_is_open(game, current_space_id, dir) == FALSE)
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
    player_id = player_get_id(game_get_player(game));
    if (game_set_player_location(game, destination_id) == ERROR)
    {
      return ERROR;
    }

    for (i = 0; i < game_get_number_of_characters(game); i++)
    {
      character = game_get_character_from_index(game, i);
      if (character != NULL && character_get_following(character) == player_id)
      {
        if (game_set_character_location(game, destination_id, character_get_id(character)) == ERROR)
        {
          return ERROR;
        }
      }
    }

    dest_space = game_get_space(game, destination_id);
    if (dest_space != NULL)
    {
      space_set_discovered(dest_space, TRUE);
    }
    return OK;
  }
  printf("No se ha podido mover en esa direccion.\n");
  return ERROR;
}

Status game_actions_take(Game *game)
{
  Space *space = NULL;
  Id player_loc = NO_ID, obj_id = NO_ID;
  Command *last_cmd = NULL;
  Object *object = NULL;
  Player *player = NULL;
  char **arg = NULL;
  /* Comprueba la validez del puntero */
  if (!game)
  {
    return ERROR;
  }
  if (!(player = game_get_player(game)))
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
  if (!arg || arg[0][0] == '\0')
  {
    return ERROR;
  }

  if (inventory_is_full(player_get_backpack(game_get_player(game))) == TRUE)
  {
    return ERROR;
  }

  obj_id = game_get_object_id_from_name(game, arg[0]);
  if (obj_id == NO_ID)
  {
    return ERROR;
  }
  if (!space_contains_object(space, obj_id))
  {
    return ERROR;
  }
  if (!(object = game_get_object(game, obj_id)))
  {
    return ERROR;
  }

  if (object_get_movable(object) == FALSE)
  {
    return ERROR;
  }
  if (object_get_dependency(object) != NO_ID)
  {

    if (!player_has_object(player, object_get_dependency(object)))
    {
      return ERROR;
    }
  }
  if (space_remove_object(space, obj_id) == ERROR)
  {
    return ERROR;
  }

  if (player_add_object(game_get_player(game), obj_id) == ERROR)
  {
    return ERROR;
  }

  return OK;
}

Status game_actions_drop(Game *game)
{
  Id player_loc = NO_ID;
  Id obj_id = NO_ID;
  Command *last_cmd = NULL;
  Object *obj;
  char **arg = NULL;
  int i, max_objects;
  Id id_2;

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
  if (!arg || arg[0][0] == '\0')
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
        if (strcasecmp(object_get_name(obj), arg[0]) == 0)
        {
          /* Eliminacion y reubicacion del objeto */
          player_del_object(game_get_player(game), obj_id);
          game_set_object_location(game, player_loc, obj_id);
          if ((id_2 = object_get_dependency(obj)) != NO_ID)
          {
            player_del_object(game_get_player(game), id_2);
            game_set_object_location(game, player_loc, id_2);
          }
          return OK;
        }
      }
    }
  }

  return ERROR;
}

Status game_actions_attack(Game *game)
{
  Id space_id = NO_ID, enemy_id = NO_ID;
  Space *space;
  char *enemy_name = NULL;
  char **arg = NULL;
  Character *enemy = NULL;
  Player *player;
  int random_num;
  int player_health, char_health, n_attackers = 0, damaged_index, i;
  Character *ally;
  Id attackers_ids[MAX_CHARACTERS + 1];
  Id *followers_ids = NULL;
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
  arg = command_get_arg(last_cmd);
  enemy_name = arg[0];

  if (enemy_name == NULL)
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

  for (i = 0; i < space_get_n_characters(space); i++)
  {
    if (space_get_character(space, i) != NO_ID)
    {
      enemy = game_get_character(game, space_get_character(space, i));
      if (enemy && strcasecmp(character_get_name(enemy), enemy_name) == 0 && character_get_friendly(enemy) == FALSE)
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

  followers_ids = game_get_players_followers(game);
  if (!followers_ids)
  {
    return ERROR;
  }

  if ((n_attackers = game_get_number_of_followers_of_player(game)) == -1)
  {
    return ERROR;
  }

  for (i = 0; i < n_attackers; i++)
  {
    attackers_ids[i] = followers_ids[i];
  }

  attackers_ids[n_attackers] = player_get_id(game_get_player(game));
  n_attackers++;

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
  Id space_id = NO_ID, char_id = NO_ID;
  Space *space;
  Character *character;
  Command *last_cmd = NULL;
  int i = 0;
  char **arg = NULL;

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
  if (!arg || arg[0][0] == '\0')
  {
    return ERROR;
  }
  for (i = 0; i < space_get_n_characters(space); i++)
  {
    if (space_get_character(space, i) != NO_ID)
    {
      character = game_get_character(game, space_get_character(space, i));
      if (character && strcasecmp(character_get_name(character), arg[0]) == 0 && character_get_friendly(character) == TRUE)
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
  char **arg;
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
  if (!arg || arg[0][0] == '\0')
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

      if (strcasecmp(object_get_name(obj), arg[0]) == 0)
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
        if (obj && strcasecmp(object_get_name(obj), arg[0]) == 0)
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
  Space *space = NULL;
  Character *character = NULL;
  Player *player = NULL;
  char **arg = NULL, *name = NULL;
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
  if (!(space = game_get_space(game, game_get_player_location(game))))
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
    if (strcasecmp(name, arg[0]) == 0)
    {
      if (game_get_character_location(game, character_get_id(character)) != space_get_id(space))
      {
        return ERROR;
      }
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
Status game_actions_abandon(Game *game)
{
  Id *id;
  Character *character = NULL;
  char **arg = NULL;
  Command *last_cmd = NULL;
  int n_player, i;
  if (!game)
  {
    return ERROR;
  }
  /*Comprueba la validez del comando */
  if (!(last_cmd = game_get_last_command(game)))
  {
    return ERROR;
  }
  /*Comprueba que haya argumento (personaje a abandonar)*/
  if (!(arg = command_get_arg(last_cmd)))
  {
    return ERROR;
  }

  if ((n_player = game_get_number_of_characters(game)) <= 0)
  {
    return ERROR;
  }
  if (!(id = game_get_players_followers(game)))
  {
    return ERROR;
  }
  for (i = 0; i < n_player; i++)
  {
    if (id[i] == NO_ID)
    {
      break;
    }

    character = game_get_character(game, id[i]);
    if (!character)
    {
      return ERROR;
    }

    if (!strcasecmp(arg[0], character_get_name(character)))
    {
      if (character_set_following(character, NO_ID) == ERROR)
      {
        return ERROR;
      }
      return OK;
    }
  }
  return ERROR;
}

Status game_actions_use(Game *game)
{
  Player *player = NULL;
  Command *last_cmd = NULL;
  Inventory *backpack = NULL;
  Id object_in_backpack = NO_ID;
  char **arg = NULL;

  if (!game)
  {
    return ERROR;
  }
  if (!(last_cmd = game_get_last_command(game)))
  {
    return ERROR;
  }
  if (!(arg = command_get_arg(last_cmd)))
  {
    return ERROR;
  }
  if (!(player = game_get_player(game)))
  {
    return ERROR;
  }
  if (!(backpack = player_get_backpack(player)))
  {
    return ERROR;
  }
  object_in_backpack = game_get_object_id_from_name(game, arg[0]);
  if (object_in_backpack == NO_ID)
  {
    return ERROR;
  }
  if (!player_has_object(player, object_in_backpack))
  {
    return ERROR;
  }

  return OK;
}

Status game_actions_open(Game *game)
{
  Player *player = NULL;
  Command *last_cmd = NULL;
  Object *object = NULL;
  Link *link = NULL;
  char **arg = NULL;
  Id object_id = NO_ID, player_loc = NO_ID;
  int i = 0, n_links = 0;

  if (!game)
  {
    return ERROR;
  }
  if (!(last_cmd = game_get_last_command(game)))
  {
    return ERROR;
  }
  if (!(arg = command_get_arg(last_cmd)))
  {
    return ERROR;
  }
  if (command_get_nargs(last_cmd) != 3 || strcasecmp(arg[1], "with") != 0)
  {
    return ERROR;
  }
  if (!(player = game_get_player(game)))
  {
    return ERROR;
  }
  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID)
  {
    return ERROR;
  }

  n_links = game_get_number_of_links(game);
  if (n_links <= 0)
  {
    return ERROR;
  }

  for (i = 0; i < n_links; i++)
  {
    link = game_get_link_at(game, i);
    if (link && link_get_name(link) && strcasecmp(link_get_name(link), arg[0]) == 0)
    {
      break;
    }
  }

  if (!link || i == n_links)
  {
    return ERROR;
  }
  if (link_get_origin(link) != player_loc && link_get_destination(link) != player_loc)
  {
    return ERROR;
  }

  object_id = game_get_object_id_from_name(game, arg[2]);
  if (object_id == NO_ID)
  {
    return ERROR;
  }
  if (!player_has_object(player, object_id))
  {
    return ERROR;
  }
  if (!(object = game_get_object(game, object_id)))
  {
    return ERROR;
  }
  if (object_get_open(object) != link_get_id(link))
  {
    return ERROR;
  }
  if (link_get_open(link) == TRUE)
  {
    return ERROR;
  }

  return link_set_open(link, TRUE);
}
Status game_actions_save(Game *game){
  Command *last_cmd = NULL;
  char **arg = NULL;
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
  if (!arg || arg[0][0] == '\0')
  {
    return ERROR;
  }
  return game_managment_save_game(game,arg[0]);
}
Status game_actions_load(Game *game){
  Command *last_cmd = NULL;
  Status s;
  char **arg = NULL;
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
  if (!arg || arg[0][0] == '\0')
  {
    return ERROR;
  }
 s=game_managment_load_players(game,arg[0]);
 if(!s){
  return ERROR;
 }
 s=game_managment_load_spaces(game,arg[0]);
 if(!s){
  return ERROR;
 }
 s=game_managment_load_objects(game,arg[0]);
 if(!s){
  return ERROR;
 }
 s=game_managment_load_links(game,arg[0]);
 if(!s){
  return ERROR;
 }
 s=game_managment_load_characters(game,arg[0]);
 if(!s){
  return ERROR;
 }
 return s;
}