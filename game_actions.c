/**
 * @brief Implementa la actualización del juego a través de las acciones del usuario
 *
 * @file game_actions.c
 * @author Unai&Rodrigo
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

/**
   Funciones privadas
*/
Status game_actions_unknown(Game *game);
Status game_actions_exit(Game *game);
Status game_actions_move(Game *game);
Status game_actions_take(Game *game);
Status game_actions_drop(Game *game);
Status game_actions_attack(Game*game);
Status game_actions_chat(Game* game);
Status game_actions_inspect(Game* game);

/**
 * @brief Actualiza el estado del juego según el comando recibido
 * @author Unai
 * @param game Puntero al juego
 * @param command Puntero al comando a ejecutar
 * @return OK si la acción se realiza con éxito, ERROR en caso contrario
 */
Status game_actions_update(Game *game, Command *command)
{
  CommandCode cmd;
  Status status = OK;

  game_set_last_command(game, command);
  cmd = command_get_code(command);

  /* Distribuidor de acciones: Llama a la función correspondiente según el comando */
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

/**
 * @brief Maneja un comando desconocido
 * @author Unai
 */
Status game_actions_unknown(Game *game) {
  return ERROR;
}

/**
 * @brief Gestiona la salida del juego
 * @author Unai
 */
Status game_actions_exit(Game *game) {
  return OK;
}

/**
 * @brief Permite al jugador moverse a cualquier espacio
 * @author Alejandro Dominguez
 */
Status game_actions_move(Game *game)
{
  Id current_space_id = NO_ID, destination_id = NO_ID;  
  char *arg = NULL;
  Direction dir = desconocido;
  Command *last_cmd = NULL;

  if (!game) return ERROR;

  /*Obtener la direccion*/
  last_cmd = game_get_last_command(game);
  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  /*Traducimos el arg para que lo entinda la dirccion*/
  if (strcasecmp(arg, "north") == 0 || strcasecmp(arg, "n") == 0 ) dir = norte;
  else if (strcasecmp(arg, "south") == 0 || strcasecmp(arg, "s") == 0 ) dir = sur;
  else if (strcasecmp(arg, "west") == 0 || strcasecmp(arg, "w") == 0 ) dir = oeste;
  else if (strcasecmp(arg, "east") == 0 || strcasecmp(arg, "e") == 0 ) dir = este;

  /*Obtenemos la unicacion actual del jugador*/
  current_space_id = game_get_player_location(game);
  if (!current_space_id) return ERROR;

  /*Verificamos si se puede*/
  if (dir == desconocido || game_connection_is_open(game, current_space_id, dir) == FALSE) return ERROR;

  destination_id = game_get_connection(game, current_space_id, dir);

  /*Movemos al jugador*/
  if(destination_id != NO_ID)
  {
    game_set_player_location(game, destination_id);
    return OK;
  }

  return ERROR;
}

/**
 * @brief Permite al jugador coger un objeto del espacio actual especificando su nombre
 * @author Unai
 */
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
  Inventory *inv = NULL;

  if (!game) return ERROR;

  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID) return ERROR;

  space = game_get_space(game, player_loc);
  if (!space) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  /* Si el jugador ya lleva un objeto, no puede coger otro */
  if (inventory_is_full(player_get_backpack(game_get_player(game))) == TRUE) {
    return ERROR;
  }

  num_objs = space_get_number_of_objects(space);

  if (num_objs > 0) {
    /* Obtenemos el array interno de IDs de los objetos de la sala */
    objs = space_get_objects(space);

    if (objs) {
      /* Buscamos si el nombre introducido coincide con alguno de la sala */
      for (i = 0; i < num_objs; i++) {
        obj = game_get_object(game, objs[i]);

        /* Protección: Verificamos que el objeto exista y tenga nombre válido */
        if (obj != NULL && object_get_name(obj) != NULL) {
          if (strcasecmp(object_get_name(obj), arg) == 0) {
            obj_id = objs[i];
            break;
          }
        }
      }

      /* ¡CUIDADO! NO hacemos free(objs) porque es el puntero interno del Set */

      /* Si hemos encontrado el objeto, hacemos el intercambio */
      if (obj_id != NO_ID) {
        /* ASIGNACIÓN: Se lo damos al jugador */
        player_add_object(game_get_player(game), obj_id);
        
        /* EXTRACCIÓN: Lo quitamos del mapa (asignándolo a NO_ID) */
        game_set_object_location(game, NO_ID, obj_id);
        return OK;
      }
    }
  }

  return ERROR;
}

/**
 * @brief Permite al jugador soltar automáticamente el objeto que lleva encima
 * @author Unai
 */
Status game_actions_drop(Game *game)
{
  Id player_loc = NO_ID;
  Id obj_id = NO_ID;
  Command *last_cmd = NULL;
  Object *obj;
  char *arg = NULL;
  int i, max_objects;

  if (!game) return ERROR;

  /* Ubicación actual para saber dónde caerá el objeto */
  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID) return ERROR;

  /*Obtenemos el argumento del comando*/
  last_cmd = game_get_last_command(game);
  if (!last_cmd) return NULL;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return NULL;

  /*Bucameos el objeto por el nombre dentro de la mochila*/
  max_objects = inventory_get_max_objs(player_get_backpack(game_get_player(game)));
  for (i = 0; i < max_objects; i++)
  {
    obj_id = player_get_object(game_get_player(game), i);
    if (obj_id != NO_ID)
    {
      obj = game_get_object(game, obj_id);

      /*si coincide el nombre del objeto con el argumento introducido*/
      if (obj != NULL && object_get_name(obj) != NULL)
      {
        if (strcasecmp(object_get_name(obj), arg) == 0)
        {
          /*Lo borramos del inventario*/
          player_del_object(game_get_player(game), obj_id);

          /*Lo colocamos en la sala*/
          game_set_object_location(game, player_loc, obj_id);
          return OK;
        }
      }
    }
  }

  /* Retorna error si el jugador no llevaba nada encima */
  return ERROR;
}

/**
 * @brief Gestiona el combate entre el jugador y un personaje hostil
 * @author Unai
 */
Status game_actions_attack(Game *game)
{
  Id space_id, char_id;
  Space *space;
  Character *character;
  Player *player;
  int random_num;
  int player_health, char_health;

  if (!game) return ERROR;

  player = game_get_player(game);
  if (!player) return ERROR;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) return ERROR;

  space = game_get_space(game, space_id);
  if (!space) return ERROR;

  char_id = space_get_character(space);
  if (char_id == NO_ID) return ERROR;

  character = game_get_character(game, char_id);
  if (!character) return ERROR;

  /* No se puede atacar si es amigo */
  if (character_get_friendly(character)) return ERROR;

  char_health = character_get_health(character);
  /* Si la salud es 0 o menos, ya está muerto, no se le ataca */
  if (char_health <= 0) return ERROR;

  /* Tirada de dados: de 0 a 9 */
  random_num = rand() % 10;

  if (random_num <= 4) {
    /* Gana el adversario: el jugador pierde 1 punto de vida */
    player_health = player_get_health(player);
    player_health--;
    player_set_heatlh(player, player_health); 

    /* Si el jugador se queda sin vida, termina el juego */
    if (player_health <= 0) game_set_finished(game, 1);
  } else {
    /* Gana el jugador: el personaje pierde 1 punto de vida */
    char_health--;
    character_set_health(character, char_health);
  }
  return OK;
}

/**
 * @brief Permite entablar conversación con un personaje amistoso
 * @author Unai
 */
Status game_actions_chat(Game* game) 
{
  Id space_id, char_id;
  Space *space;
  Character *character;

  if (!game) return ERROR;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) return ERROR;

  space = game_get_space(game, space_id);
  if (!space) return ERROR;

  char_id = space_get_character(space);
  if (char_id == NO_ID) return ERROR;

  character = game_get_character(game, char_id);
  if (!character) return ERROR;

  /* Verificamos que el NPC sea amistoso y esté vivo */
  if (character_get_friendly(character) == 0) return ERROR;
  if (character_get_health(character) <= 0) return ERROR;

  /* Imprimimos en la interfaz el mensaje del personaje */
  game_set_chat_message(game, character_get_message(character));
  return OK;
}

Status game_actions_inspect(Game *game) 
{
  char *arg;
  int i, max_backpac_obj, num_obj_in_space;
  Space *space =NULL;
  Command *last_cmd = NULL;
  Object *obj = NULL;
  Id player_loc = NO_ID, obj_id = NO_ID, *objs = NULL;
  Player *player = NULL;
  BOOL found = FALSE;

  if (!game) return ERROR;

  /*Obtenemos el argumento del comando*/
  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;
  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  player = game_get_player(game);
  if (!player) return ERROR;

  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID) return ERROR;

  space = game_get_space(game, player_loc);
  if (!space) return ERROR;

  /*Comprobar si esta en la mochila*/
  max_backpac_obj = inventory_get_max_objs(player_get_backpack(player));
  for (i = 0; i < max_backpac_obj; i++)
  {
    obj_id = player_get_object(player, i);
    if (obj_id != NO_ID)
    {
      obj = game_get_object(game, obj_id);
      if (obj == NULL) return ERROR;

      if (strcasecmp(object_get_name(obj), arg) == 0)
      {
        found = TRUE;
        break;
      }
    }
  }

  /*Bucar en el espacio actual*/
  if (!found && space)
  {
    num_obj_in_space = space_get_number_of_objects(space);
    if (num_obj_in_space == 0) return ERROR;

    objs = space_get_objects(space);
    if (objs)
    {
      for (i = 0; i< num_obj_in_space; i++)
      {
        obj = game_get_object(game, objs[i]);
        if (obj && strcasecmp(object_get_name(obj), arg) == 0)
        {
          found = TRUE;
          break;
        }
      }
    }
  }

  /*Si lo encontramos, guardamos su desc para enseñarla*/
  if (obj && found)
  {
    game_set_object_desc(game, object_get_desc(obj));
    return OK;
  }

  return ERROR;
}
