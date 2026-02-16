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

/**
 * @brief Estructura de Jugador
 * Contiene el ID, nombre, ubicación actual e ID del objeto que transporta.
 */
struct Player
{
  Id id;
  char name[WORD_SIZE + SINGLE_ELEM];
  Id location;
  Id object;
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
  newPlayer->object = NO_ID;

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

Status player_set_object(Player *player, Id object)
{
  /* Comprueba validez del puntero */
  if (!player)
  {
    return ERROR;
  }
  /* Guarda el objeto en el inventario */
  player->object = object;
  return OK;
}

Id player_get_object(Player *player)
{
  /* Comprueba validez del puntero */
  if (!player)
  {
    return NO_ID;
  }
  return player->object;
}

Status player_print(Player *player)
{
  /* Comprueba si el jugador es válido para imprimir */
  if (!player)
  {
    return ERROR;
  }

  /* Imprime la información*/
  fprintf(stdout, "--> Jugador (Id: %ld; Nombre: %s)\n", player->id, player->name);
  fprintf(stdout, "--> Localización: %ld\n", player->location);
  fprintf(stdout, "--> Objeto: %ld\n", player->object);

  return OK;
}