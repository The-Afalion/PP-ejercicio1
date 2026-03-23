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

/**
 * @brief Estructura de Game
 * Almacena los punteros a todas las entidades y el estado del ciclo de juego.
 */
struct _Game
{
  Player *player;                        /* Puntero al jugador */
  Object *objects[MAX_OBJECTS];          /* Array de punteros a objetos */
  Character *characters[MAX_CHARACTERS]; /*Array de punteros a personajes */
  Space *spaces[MAX_SPACES];             /*Array de punteros a espacios */
  int n_spaces;                          /* Número actual de espacios cargados */
  Link *link[MAX_LINKS];                  /* Array de punteros a enlaces */
  int n_links;                           /*!< Número actual de enlaces cargados */
  Command *last_cmd;                     /* Último comando introducido por el usuario */
  int finished;                          /*El juego ha finalizado */
  char chat_message[WORD_SIZE];          /* Último chat */
};

/* Prototipos de funciones privadas */
Status game_add_space(Game *game, Space *space);
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief Crea la instancia de juego, reserva memoria e inicializa punteros a NULL.
 */
Status game_create(Game **game)
{
  int i;

  if (!game)
    return ERROR;

  *game = (Game *)malloc(sizeof(Game));
  if (!*game)
    return ERROR;

  /* Inicialización de arrays de entidades */
  for (i = 0; i < MAX_SPACES; i++)
    (*game)->spaces[i] = NULL;
  for (i = 0; i < MAX_OBJECTS; i++)
    (*game)->objects[i] = NULL;
  for (i = 0; i < MAX_CHARACTERS; i++)
    (*game)->characters[i] = NULL;
  for (i = 0; i < MAX_LINKS; i++)
    (*game)->link[i] = NULL;

 
  /* Inicialización de estado y componentes básicos */
  (*game)->n_spaces = 0;
  (*game)->n_links = 0;
  (*game)->player = player_create(PLAYER_ID);
  (*game)->last_cmd = command_create();
  (*game)->finished = 0;
  (*game)->chat_message[0] = '\0';

  return OK;
}

/**
 * @brief Carga los componentes del juego desde un fichero externo.
 */
Status game_create_from_file(Game **game, char *filename)
{
  if (!game || !filename)
    return ERROR;

  if (game_create(game) == ERROR)
    return ERROR;

  /* Carga de entidades mediante el módulo game_reader */
  if (game_reader_load_spaces(*game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_objects(*game, filename) == ERROR)
    return ERROR;
  if (game_reader_load_characters(*game, filename) == ERROR)
    return ERROR;

  /* Posicionamiento inicial del jugador */
  game_set_player_location(*game, game_get_space_id_at(*game, FIRST_POSITION));

  return OK;
}

/**
 * @brief Libera toda la memoria dinámica asociada al juego y sus entidades.
 */
Status game_destroy(Game *game)
{
  int i;
  if (!game)
    return ERROR;

  /* Destrucción selectiva de espacios cargados */
  for (i = 0; i < game->n_spaces; i++)
    space_destroy(game->spaces[i]);

  if (game->player)
    player_destroy(game->player);

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    if (game->objects[i])
      object_destroy(game->objects[i]);
  }

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    if (game->characters[i])
      character_destroy(game->characters[i]);
  }

  for (size_t i = 0; i < MAX_LINKS; i++)
  {
    if (game->link[i])
      link_destroy(game->link[i]);
  }
  

  if (game->last_cmd)
    command_destroy(game->last_cmd);

  free(game);
  return OK;
}

/**
 * @brief Busca un espacio en el juego dado su identificador (Id).
 */
Space *game_get_space(Game *game, Id id)
{
  int i;
  if (id == NO_ID || !game)
    return NULL;

  for (i = 0; i < game->n_spaces; i++)
  {
    if (id == space_get_id(game->spaces[i]))
      return game->spaces[i];
  }

  return NULL;
}

/* --- Gestión de Localización de Jugador --- */

Id game_get_player_location(Game *game)
{
  if (!game)
    return NO_ID;
  return player_get_location(game->player);
}

Status game_set_player_location(Game *game, Id id)
{
  if (id == NO_ID || !game)
    return ERROR;
  return player_set_location(game->player, id);
}

/**
 * @brief Localiza en qué espacio se encuentra un objeto por su Id.
 */
Id game_get_object_location(Game *game, Id object_id)
{
  int i;
  if (!game || object_id == NO_ID)
    return NO_ID;

  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_contains_object(game->spaces[i], object_id) == OK)
    {
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

/**
 * @brief Mueve un objeto: lo quita de su posición actual y lo pone en el nuevo espacio.
 */
Status game_set_object_location(Game *game, Id space_id, Id object_id)
{
  Id loc_actual;
  int i;

  if (!game || object_id == NO_ID)
    return ERROR;

  /* Eliminación de la ubicación previa */
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

  /* Inserción en la nueva ubicación */
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

/* --- Gestión de Localización de Personajes --- */

Id game_get_character_location(Game *game, Id character_id)
{
  int i;
  if (!game || character_id == NO_ID)
    return NO_ID;

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

  if (!game || character_id == NO_ID)
    return ERROR;

  loc_actual = game_get_character_location(game, character_id);

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

/* --- Getters/Setters de estado del juego --- */

Command *game_get_last_command(Game *game)
{
  return (!game) ? NULL : game->last_cmd;
}

Status game_set_last_command(Game *game, Command *command)
{
  if (!game || !command)
    return ERROR;
  game->last_cmd = command;
  return OK;
}

int game_get_finished(Game *game)
{
  return (!game) ? 0 : game->finished;
}

Status game_set_finished(Game *game, int finished)
{
  if (!game)
    return ERROR;
  game->finished = finished;
  return OK;
}

/**
 * @brief Imprime el estado actual de todas las entidades para depuración.
 */
void game_print(Game *game)
{
  int i;
  if (!game)
    return;

  printf("\n\n-------------\n\n");
  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++)
    space_print(game->spaces[i]);

  player_print(game->player);

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    if (game->objects[i])
      object_print(game->objects[i]);
  }

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    if (game->characters[i])
      character_print(game->characters[i]);
  }

    fprintf(stdout, "---> Links:\n");
  for (i = 0; i < MAX_LINKS; i++) {
      if (game->link[i] != NULL) {
          fprintf(stdout, "     - Link %d: Id %ld\n", i, link_get_id(game->link[i]));
      }
  }
}

/* --- Búsqueda de punteros a entidades --- */

Player *game_get_player(Game *game)
{
  return (!game) ? NULL : game->player;
}

Object *game_get_object(Game *game, Id id)
{
  int i;
  if (!game || id == NO_ID)
    return NULL;

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
  if (!game || id == NO_ID)
    return NULL;

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    if (game->characters[i] != NULL && character_get_id(game->characters[i]) == id)
    {
      return game->characters[i];
    }
  }
  return NULL;
}

/* --- Funciones de inserción --- */

Status game_add_object(Game *game, Object *obj)
{
  int i;
  if (!game || !obj)
    return ERROR;

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    if (game->objects[i] == NULL)
    {
      game->objects[i] = obj;
      return OK;
    }
  }
  return ERROR;
}

Status game_add_character(Game *game, Character *character)
{
  int i;
  if (!game || !character)
    return ERROR;

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    if (game->characters[i] == NULL)
    {
      game->characters[i] = character;
      return OK;
    }
  }
  return ERROR;
}

Status game_add_space(Game *game, Space *space)
{
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES))
    return ERROR;

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;
  return OK;
}

/**
 * @brief Auxiliar para obtener el Id de un espacio por su posición en el array.
 */
Id game_get_space_id_at(Game *game, int position)
{
  if (position < 0 || position >= game->n_spaces || !game)
    return NO_ID;
  return space_get_id(game->spaces[position]);
}

/* --- Gestión del Chat --- */

Status game_set_chat_message(Game *game, char *message)
{
  if (!game || !message)
    return ERROR;
  strcpy(game->chat_message, message);
  return OK;
}

char *game_get_chat_message(Game *game)
{
  return (!game) ? NULL : game->chat_message;
}


BOOL game_connection_is_open(Game *game, Id space_id, Direction dir)
{
  Space *s = NULL;
  Id link_id = NO_ID;
  Link *l = NULL;
  if (!game || space_id == NO_ID || dir == desconocido)
  {
    return NO_ID;
  }
  for (size_t i = 0; i < MAX_SPACES; i++)
  {
    if (space_get_id(game->spaces[i]) == space_id)
    {
      s = game->spaces[i];
    }
  }

  for (size_t i = 0; i < MAX_LINKS; i++)
  {
    link_id = space_get_link_from_index(s, i);
    l = space_get_link(s, link_id);
    if (link_get_direction(l) == dir)
    {
      break;
    }
  }

  return link_get_open(l);
}


/*---Funciones enlaces---*/
Id game_get_link(Game *game, Id link_id)
{
  int i;
  if (!game || link_id == NO_ID)
    return NULL;

  for (i = 0; i < MAX_LINKS; i++)
  {
    if (game->link[i] != NULL && link_get_id(game->link[i]) == link_id)
    {
      return game->link[i];
    }
  }
  return NULL;
}

Id game_get_connection(Game *game, Id space_id, Direction dir)
{
if (!game||space_id == NULL||dir == desconocido){
    return NO_ID;
  }

  for (size_t i = 0; i < game->n_links; i++)
  {
    if (link_get_origin(game->link[i]) == space_id && link_get_direction(game->link[i]) == dir)
    {
      return link_get_destination(game->link[i]);
    }
  }
  return NO_ID;
}

BOOL game_connection_is_open(Game *game, Id space_id, Direction dir)
{
  Link * l = NULL;

  if (!game||space_id == NULL||dir == desconocido){
    return NO_ID;
  }

  for (size_t i = 0; i < game->n_links; i++)
  {
    if (link_get_origin(game->link[i]) == space_id && link_get_direction(game->link[i]) == dir)
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

    if (!game || !link) {
        return ERROR;
    }

    /* Recorremos el array buscando el primer hueco disponible (NULL) */
    for (i = 0; i < MAX_LINKS; i++) {
        if (game->link[i] == NULL) {
            game->link[i] = link;
            return OK; /* Enlace añadido correctamente */
        }
    }

    /* Si llegamos aquí, es que el array está lleno y no hay espacio */
    return ERROR; 
}

Link* game_get_link(Game* game, Id link_id) 
{
    int i;

    if (!game || link_id == NO_ID) {
        return NULL;
    }

    /* Buscamos el enlace por su ID dentro de los que no sean nulos */
    for (i = 0; i < MAX_LINKS; i++) {
        if (game->link[i] != NULL && link_get_id(game->link[i]) == link_id) {
            return game->link[i];
        }
    }

    return NULL; /* No se encontró el enlace */
}

int game_get_number_of_links(Game *game){
  int i,cont;
  if(!game){
    return -1;
  }
  for(i=0,cont=0;i<MAX_LINKS;i++){
    if(game->link[i]!=NULL){
      cont++;
    }
  }
  return cont;
}