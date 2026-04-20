/**
 * @brief Implementa la lógica principal del juego
 *
 * @file game.c
 * @author Unai
 * @version 2.0
 * @date 15-03-2026
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
#define FIRST_POSITION 0
#define MAX_OBJECTS 100
#define MAX_LINKS 800
#define MAX_PLAYERS 8

struct _Game
{
  Player *players[MAX_PLAYERS];          /*!< Array de punteros a jugadores */
  int turn;                              /*!< Numero de turno actual */
  Object *objects[MAX_OBJECTS];          /*!< Array de punteros a objetos */
  Character *characters[MAX_CHARACTERS]; /*!< Array de punteros a personajes */
  Space *spaces[MAX_SPACES];             /*!< Array de punteros a espacios */
  int n_spaces;                          /*!< Contador de espacios cargados */
  int n_players;                         /*!< Numero actual de jugadores */
  Link *link[MAX_LINKS];                 /*!< Array de punteros a enlaces */
  int n_links;                           /*!< Contador de enlaces cargados */
  int finished;                          /*!< Bandera de finalizacion del juego */
  char object_inspection[WORD_SIZE];     /*!< Descripcion del objeto activo */
  char messages[MAX_PLAYERS][WORD_SIZE]; /*!< Array de mensajes por jugador */
  Command *last_command;                 /*!< Puntero al ultimo comando procesado */
  Status last_status;                    /*!< Estado del ultimo comando procesado */
  int n_characters;                      /*!< Contador de personajes cargados */
  int n_objects;                         /*!< Contador de objetos cargados */
};

Status game_add_space(Game *game, Space *space);
Id game_get_space_id_at(Game *game, int position);

Status game_create(Game **game)
{
  int i;

  /* Comprueba la integridad del puntero al juego */
  if (!game)
  {
    return ERROR;
  }

  *game = (Game *)malloc(sizeof(Game));
  /* Comprueba si la reserva del bloque principal falla */
  if (!*game)
  {
    return ERROR;
  }

  /* Limpieza e inicializacion de arrays de componentes */
  for (i = 0; i < MAX_SPACES; i++)
  {
    (*game)->spaces[i] = NULL;
  }
  for (i = 0; i < MAX_OBJECTS; i++)
  {
    (*game)->objects[i] = NULL;
  }
  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    (*game)->characters[i] = NULL;
  }
  for (i = 0; i < MAX_LINKS; i++)
  {
    (*game)->link[i] = NULL;
  }
  for (i = 0; i < MAX_PLAYERS; i++)
  {
    (*game)->players[i] = NULL;
    (*game)->messages[i][0] = '\0';
  }

  /* Asignacion de estados predeterminados */
  (*game)->n_spaces = 0;
  (*game)->n_links = 0;
  (*game)->finished = 0;
  (*game)->turn = 0;
  (*game)->object_inspection[0] = '\0';
  (*game)->n_players = 0;
  (*game)->n_objects = 0;
  (*game)->n_characters = 0;
  (*game)->last_command = command_create();
  (*game)->last_status = OK;

  return OK;
}

Status game_create_from_file(Game **game, char *filename)
{
  /* Comprueba la validez de los argumentos base */
  if (!game || !filename)
  {
    return ERROR;
  }

  /* Inicializa la estructura principal de memoria */
  if (game_create(game) == ERROR)
  {
    return ERROR;
  }

  /* Delegacion modular de la carga de las entidades */
  if (game_reader_load_spaces(*game, filename) == ERROR)
  {
    return ERROR;
  }
  if (game_reader_load_objects(*game, filename) == ERROR)
  {
    return ERROR;
  }
  if (game_reader_load_players(*game, filename) == ERROR)
  {
    return ERROR;
  }
  if (game_reader_load_characters(*game, filename) == ERROR)
  {
    return ERROR;
  }
  if (game_reader_load_links(*game, filename) == ERROR)
  {
    return ERROR;
  }

  return OK;
}

Status game_destroy(Game *game)
{
  int i;

  /* Comprueba si el motor de juego esta asignado */
  if (!game)
  {
    return ERROR;
  }

  /* Destruccion escalonada de entidades */
  for (i = 0; i < game->n_spaces; i++)
  {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; i < game->n_players; i++)
  {
    if (game->players[i])
    {
      player_destroy(game->players[i]);
    }
  }

  for (i = 0; i < game->n_links; i++)
  {
    if (game->link[i])
    {
      link_destroy(game->link[i]);
    }
  }

  for (i = 0; i < game->n_objects; i++)
  {
    if (game->objects[i])
    {
      object_destroy(game->objects[i]);
    }
  }

  for (i = 0; i < game->n_characters; i++)
  {
    if (game->characters[i])
    {
      character_destroy(game->characters[i]);
    }
  }

  if (game->last_command)
  {
    command_destroy(game->last_command);
  }

  /* Liberacion del bloque padre */
  free(game);
  return OK;
}

Space *game_get_space(Game *game, Id id)
{
  int i;

  /* Comprueba la validez de los parametros */
  if (id == NO_ID || !game)
  {
    return NULL;
  }

  /* Busqueda secuencial del espacio por identificador */
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
  /* Comprueba la validez del juego */
  if (!game)
  {
    return NO_ID;
  }
  return player_get_location(game->players[game->turn]);
}

Status game_set_player_location(Game *game, Id id)
{
  /* Comprueba la validez de los parametros */
  if (id == NO_ID || !game)
  {
    return ERROR;
  }
  return player_set_location(game->players[game->turn], id);
}

Id game_get_object_location(Game *game, Id object_id)
{
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || object_id == NO_ID)
  {
    return NO_ID;
  }

  /* Itera sobre los espacios para localizar el objeto */
  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_contains_object(game->spaces[i], object_id) == OK)
    {
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

Status game_set_object_location(Game *game, Id space_id, Id object_id)
{
  Id loc_actual;
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || object_id == NO_ID)
  {
    return ERROR;
  }

  /* Eliminacion de la ubicacion previa del objeto */
  loc_actual = game_get_object_location(game, object_id);
  if (loc_actual != NO_ID)
  {
    for (i = 0; i < game->n_spaces; i++)
    {
      if (space_get_id(game->spaces[i]) == loc_actual)
      {
        space_remove_object(game->spaces[i], object_id);
        break;
      }
    }
  }

  /* Insercion del objeto en la nueva ubicacion */
  if (space_id != NO_ID)
  {
    for (i = 0; i < game->n_spaces; i++)
    {
      if (space_get_id(game->spaces[i]) == space_id)
      {
        return space_add_object(game->spaces[i], object_id);
      }
    }
  }

  return OK;
}

Id game_get_character_location(Game *game, Id character_id)
{
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || character_id == NO_ID)
  {
    return NO_ID;
  }

  /* Itera sobre los espacios para localizar al personaje */
  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_get_character(game->spaces[i]) == character_id)
    {
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

Status game_set_character_location(Game *game, Id space_id, Id character_id)
{
  Id loc_actual;
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || character_id == NO_ID)
  {
    return ERROR;
  }

  loc_actual = game_get_character_location(game, character_id);

  /* Eliminacion de la ubicacion previa del personaje */
  if (loc_actual != NO_ID)
  {
    for (i = 0; i < game->n_spaces; i++)
    {
      if (space_get_id(game->spaces[i]) == loc_actual)
      {
        space_set_character(game->spaces[i], NO_ID);
        break;
      }
    }
  }

  /* Insercion del personaje en la nueva ubicacion */
  if (space_id != NO_ID)
  {
    for (i = 0; i < game->n_spaces; i++)
    {
      if (space_get_id(game->spaces[i]) == space_id)
      {
        return space_set_character(game->spaces[i], character_id);
      }
    }
  }

  return OK;
}

Command *game_get_last_command(Game *game)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return NULL;
  }
  return game->last_command;
}

Status game_set_last_command(Game *game, Command *command)
{
  /* Comprueba la validez de los parametros */
  if (!game || !command)
  {
    game_set_last_command_status(game, ERROR);
  }

  game->last_command = command;
  return game->last_status;
}

Status game_set_last_command_status(Game *game, Status status)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return ERROR;
  }

  game->last_status = status;
  return OK;
}

Status game_get_last_command_status(Game *game)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return ERROR;
  }

  return game->last_status;
}

int game_get_finished(Game *game)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return 0;
  }
  return game->finished;
}

Status game_set_finished(Game *game, int finished)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return ERROR;
  }

  game->finished = finished;
  return OK;
}

void game_print(Game *game)
{
  int i;

  /* Comprueba la validez del juego antes de imprimir */
  if (!game)
  {
    return;
  }

  printf("\n\n-------------\n\n");
  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++)
  {
    space_print(game->spaces[i]);
  }

  player_print(game->players[game->turn]);

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    if (game->objects[i])
    {
      object_print(game->objects[i]);
    }
  }

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    if (game->characters[i])
    {
      character_print(game->characters[i]);
    }
  }

  fprintf(stdout, "---> Links:\n");
  for (i = 0; i < MAX_LINKS; i++)
  {
    if (game->link[i] != NULL)
    {
      fprintf(stdout, "     - Link %d: Id %ld\n", i, link_get_id(game->link[i]));
    }
  }
}

Player *game_get_player(Game *game)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return NULL;
  }
  return game->players[game->turn];
}

Status game_set_player(Game *game, Player *player)
{
  /* Comprueba la validez y capacidad de jugadores */
  if (!game || !player || game->n_players >= MAX_PLAYERS)
  {
    return ERROR;
  }

  game->players[game->n_players] = player;
  game->n_players++;
  return OK;
}

Object *game_get_object(Game *game, Id id)
{
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || id == NO_ID)
  {
    return NULL;
  }

  /* Busca el objeto por identificador */
  for (i = 0; i < MAX_OBJECTS; i++)
  {
    if (game->objects[i] != NULL && object_get_id(game->objects[i]) == id)
    {
      return game->objects[i];
    }
  }
  return NULL;
}

Character *game_get_character(Game *game, Id id)
{
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || id == NO_ID)
  {
    return NULL;
  }

  /* Busca el personaje por identificador */
  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    if (game->characters[i] != NULL && character_get_id(game->characters[i]) == id)
    {
      return game->characters[i];
    }
  }
  return NULL;
}

Character *game_get_character_at(Game *game, int position)
{
  /* Comprueba que el juego exista y la posición sea válida */
  if (!game || position < 0 || position >= game->n_characters)
  {
    return NULL;
  }

  return game->characters[position];
}

Status game_add_object(Game *game, Object *obj)
{
  /* Comprueba la validez y capacidad de objetos */
  if (!game || !obj || game->n_objects >= MAX_OBJECTS)
  {
    return ERROR;
  }

  game->objects[game->n_objects] = obj;
  game->n_objects++;
  return OK;
}

Status game_add_character(Game *game, Character *character)
{
  /* Comprueba la validez y capacidad de personajes */
  if (!game || !character || game->n_characters >= MAX_CHARACTERS)
  {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;
  return OK;
}

Status game_add_space(Game *game, Space *space)
{
  /* Comprueba la validez y capacidad de espacios */
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
  /* Comprueba la validez de la posicion y del juego */
  if (position < 0 || position >= game->n_spaces || !game)
  {
    return NO_ID;
  }
  return space_get_id(game->spaces[position]);
}

Status game_set_chat_message(Game *game, char *message)
{
  /* Comprueba la validez de los parametros */
  if (!game || !message)
  {
    return ERROR;
  }

  strcpy(game->messages[game->turn], message);
  return OK;
}

char *game_get_chat_message(Game *game)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return NULL;
  }
  return game->messages[game->turn];
}

Id game_get_connection(Game *game, Id space_id, Directions dir)
{
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || space_id == NO_ID || dir == U)
  {
    return NO_ID;
  }

  /* Busca la conexion especifica en el array de enlaces */
  for (i = 0; i < game->n_links; i++)
  {
    if (link_get_origin(game->link[i]) == space_id && link_get_direction(game->link[i]) == dir)
    {
      return link_get_destination(game->link[i]);
    }
  }
  return NO_ID;
}

BOOL game_connection_is_open(Game *game, Id space_id, Directions dir)
{
  Link *l = NULL;
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || space_id == NO_ID || dir == U)
  {
    return FALSE;
  }

  /* Obtiene el enlace solicitado */
  for (i = 0; i < game->n_links; i++)
  {
    if ((link_get_origin(game->link[i]) == space_id) && (link_get_direction(game->link[i]) == dir))
    {
      l = game->link[i];
      break;
    }
  }

  return link_get_open(l);
}

Status game_add_link(Game *game, Link *link)
{
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || !link)
  {
    return ERROR;
  }

  /* Itera para encontrar un espacio libre en el array */
  for (i = 0; i < MAX_LINKS; i++)
  {
    if (game->link[i] == NULL)
    {
      game->link[i] = link;
      game->n_links++;
      return OK;
    }
  }

  return ERROR;
}

Link *game_get_link(Game *game, Id link_id)
{
  int i;

  /* Comprueba la validez de los parametros */
  if (!game || link_id == NO_ID)
  {
    return NULL;
  }

  /* Busca el enlace por identificador */
  for (i = 0; i < MAX_LINKS; i++)
  {
    if (game->link[i] != NULL && link_get_id(game->link[i]) == link_id)
    {
      return game->link[i];
    }
  }

  return NULL;
}

int game_get_number_of_links(Game *game)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return -1;
  }

  return game->n_links;
}

int game_get_turn(Game *game)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return -1;
  }

  return game->turn;
}

void game_next_turn(Game *game)
{
  /* Comprueba la validez del juego y la existencia de jugadores */
  if (!game || game->n_players <= 0)
  {
    return;
  }

  /* Aplica operador modulo para ciclar el turno */
  game->turn = (game->turn + 1) % game->n_players;
}

Status game_set_object_desc(Game *game, const char *inspection)
{
  /* Comprueba la validez de los parametros */
  if (!game || !inspection)
  {
    return ERROR;
  }

  strcpy(game->object_inspection, inspection);
  return OK;
}

char *game_get_object_desc(Game *game)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return NULL;
  }

  return game->object_inspection;
}

Character *game_get_character_from_index(Game *game, int index)
{
  /* Comprueba la validez de los parametros */
  if (!game || index < 0 || index >= game->n_characters)
  {
    return NULL;
  }

  return game->characters[index];
}

int game_get_number_of_characters(Game *game)
{
  /* Comprueba la validez del juego */
  if (!game)
  {
    return -1;
  }

  return game->n_characters;
}
int game_get_number_of_followers_of_player(Game*game){
  Id id;
  int cont,i;
  if(!game){
    return -1;
  }
 id= player_get_id(game->players[game->turn]);
 for(i=0,cont =0;i<game->n_characters;i++){
  if(id==character_get_following(game->characters[i])){
    cont++;
  }
 }
 return cont;
}
Id * game_get_players_followers(Game*game){
  static Id ids[MAX_CHARACTERS];
  Id player_id;
  int i,cont;
  if(!game){
    return NULL;
  }

  player_id = player_get_id(game->players[game->turn]);
  if (player_id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    ids[i] = NO_ID;
  }

  for(i=0,cont =0;i<game->n_characters;i++){
    if(player_id == character_get_following(game->characters[i])){
      ids[cont]=character_get_id(game->characters[i]);
      cont++;
    }
  }
  return ids;
}
