/**
 * @brief Implementación del módulo de jugador
 * @file player.c
 * @author Unai
 * @version 1.0
 * @date 15-02-2026
 */

#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definiciones para evitar números mágicos */
#define SINGLE_ELEM 1
#define FIRST_CHAR 0
#define START_HEALTH 3


/**
 * @brief Player
 * Estructura de Jugador que contiene el ID, nombre, ubicación actual e ID del objeto que transporta.
 */
struct Player
{
  Id id;                              /*!< Id del jugador*/
  char name[WORD_SIZE + SINGLE_ELEM]; /*!< Nombre del jugador*/
  Id location;                        /*!< Ubicación actual del jugador*/
  Inventory *backpack;                /*!< Inventario del jugador*/
  int nobj;                           /*!< Número de objetos en el inventario*/
  int health;                         /*!< Puntos de salud del jugador*/
  char *gdesc;                        /*!< Descripción gráfica del jugador*/
};

Player *player_create(Id id)
{
  Player *newPlayer = NULL;

  /*Se comprueba si el ID proporcionado es válido */
  if (id == NO_ID)
  {
    return NULL;
  }

  /* Reserva memoria para un único elemento Player */
  newPlayer = (Player *)calloc(SINGLE_ELEM, sizeof(Player));

  /* Comprueba si hubo un error al reservar memoria */
  if (newPlayer == NULL)
  {
    return NULL;
  }

  /* Inicializa los valores por defecto del jugador */
  newPlayer->id = id;
  newPlayer->name[FIRST_CHAR] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->backpack = inventory_create(INVENTORY_SIZE);
  newPlayer->health = START_HEALTH;
  newPlayer->gdesc = NULL;

  return newPlayer;
}

Status player_destroy(Player *player)
{
  /* Comprueba si el jugador existe antes de destruirlo */
  if (!player)
  {
    return ERROR;
  }

  /* Libera la memoria */
  if (player->gdesc)
  {
    free(player->gdesc);
  }
  if (player->backpack)
  {
    inventory_destroy(player->backpack);
  }
  free(player);
  return OK;
}

Id player_get_id(Player *player)
{
  /* Comprueba que el puntero no sea NULL */
  if (!player)
  {
    return NO_ID;
  }
  return player->id;
}

Status player_set_name(Player *player, char *name)
{
  /* Verifica que el jugador y el nombre existan */
  if (!player || !name)
  {
    return ERROR;
  }

  /* Copia el nombre y comprueba si falla */
  if (!strcpy(player->name, name))
  {
    return ERROR;
  }
  return OK;
}

const char *player_get_name(Player *player)
{
  /* Comprueba validez del puntero */
  if (!player)
  {
    return NULL;
  }
  return player->name;
}

Status player_set_location(Player *player, Id location)
{
  /* Comprueba validez del puntero */
  if (!player)
  {
    return ERROR;
  }
  /* Actualiza la ubicación */
  player->location = location;
  return OK;
}

Id player_get_location(Player *player)
{
  /* Comprueba validez del puntero */
  if (!player)
  {
    return NO_ID;
  }
  return player->location;
}

Status player_add_object(Player *player, Id object)
{
  /* Comprueba validez del puntero y del id */
  if (!player || object == NO_ID)
  {
    return ERROR;
  }
  /* Guarda el objeto en el inventario */
  if (inventory_add_object(player->backpack, object) == ERROR)
  {
    return ERROR;
  }
  return OK;
}

Id player_get_object(Player *player, int index)
{
  /* Comprueba validez del puntero  y index */
  if (!player || index < 0 || index >= inventory_get_max_objs(player->backpack))
  {
    return NO_ID;
  }
  /* Devuelve el objeto en la posición dada */
  return set_get_id(inventory_get_objs(player->backpack), index);
}

BOOL player_has_object(Player *player, Id object)
{
  /* Comprueba validez del puntero y verifica si el objeto está en el inventario */
  if (!player || object == NO_ID)
  {
    return FALSE;
  }

  if (set_find(inventory_get_objs(player->backpack), object) == OK)
  {
    return TRUE;
  }
  return FALSE;
}

Status player_del_object(Player *player, Id object)
{
  /* Comprueba validez del puntero */
  if (!player || player_has_object(player, object) == FALSE)
  {
    return ERROR;
  }
  /* Elimina el objeto del inventario */
  if (inventory_del_object(player->backpack, object) == ERROR)
  {
    return ERROR;
  }
  return OK;
}

Status player_print(Player *player)
{
  /* Comprueba si el jugador es válido para imprimir */
  if (!player)
  {
    return ERROR;
  }

  /* Imprime la información*/
  fprintf(stdout, "--> Jugador (Id: %ld; Nombre: %s; Descripción: %s)\n", player->id, player->name, player->gdesc ? player->gdesc : "None");
  fprintf(stdout, "--> Salud: %d\n", player->health);
  fprintf(stdout, "--> Localización: %ld\n", player->location);
  inventory_print(player->backpack);

  return OK;
}
Status player_set_health(Player *player, int h)
{ /*Cambia salud del jugador,si la salud es <= 0 devielve error*/
  if (!player || h <= 0)
  {
    return ERROR;
  }
  player->health = h;
  return OK;
}
int player_get_health(Player *player)
{ /*Devuelve salud del jugador*/
  if (!player)
  {
    return -1;
  }
  return player->health;
}
Status player_set_gdesc(Player *player, char *des)
{ /*Cambia descripcion del jugador,si la descripcion es NULL devielve error*/
  if (!player || !des)
  {
    return ERROR;
  }
  if (player->gdesc)
  {
    free(player->gdesc);
  }
  player->gdesc = (char *)malloc((strlen(des) + 1) * sizeof(char));
  if (!player->gdesc)
  {
    return ERROR;
  }
  strcpy(player->gdesc, des);
  return OK;
}
char *player_get_gdesc(Player *player)
{ /*Devuelve la descripcion, comprueba puntero */
  if (!player)
  {
    return NULL;
  }
  return player->gdesc;
}

Inventory *player_get_backpack(Player *player)
{ /*Devuelve mochila del jugador, comprueba puntero*/
  if (!player)
  {
    return NULL;
  }
  return player->backpack;
}
int player_get_number_of_backpack(Player*p){
  if(!p){
    return -1;
  }
  return p->nobj;
}