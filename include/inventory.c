/**
 * @brief Implementa el módulo de inventario
 *
 * @file inventory.c
 * @author Rodrigo
 * @version 1.0
 * @date 23-03-2026
 * @copyright GNU Public License
 */

#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Inventory
{
  Set *objs;     /*!< Conjunto de objetos almacenados */
  int max_objs;  /*!< Capacidad maxima del inventario */
};

Inventory *inventory_create(int max_objs)
{
  Inventory *inventory = NULL;

  /* Comprueba que la capacidad sea valida */
  if (max_objs < 0)
  {
    return NULL;
  }

  inventory = (Inventory *)malloc(sizeof(Inventory));
  /* Comprueba si la reserva de memoria principal falla */
  if (inventory == NULL)
  {
    return NULL;
  }

  inventory->objs = set_create();
  /* Comprueba si la reserva del conjunto interno falla */
  if (inventory->objs == NULL)
  {
    free(inventory);
    return NULL;
  }

  inventory->max_objs = max_objs;
  return inventory;
}

Status inventory_destroy(Inventory *inventory)
{
  /* Comprueba la validez del puntero */
  if (inventory == NULL)
  {
    return ERROR;
  }

  /* Libera la memoria del conjunto interno y la estructura */
  set_destroy(inventory->objs);
  free(inventory);
  return OK;
}

Set *inventory_get_objs(Inventory *inventory)
{
  /* Comprueba la validez del puntero y devuelve el conjunto */
  if (inventory == NULL)
  {
    return NULL;
  }
  return inventory->objs;
}

int inventory_get_max_objs(Inventory *inventory)
{
  /* Comprueba la validez del puntero y devuelve la capacidad */
  if (inventory == NULL)
  {
    return -1;
  }
  return inventory->max_objs;
}

Status inventory_set_objs(Inventory *inventory, Set *objs)
{
  /* Comprueba la validez de los punteros */
  if (inventory == NULL || objs == NULL)
  {
    return ERROR;
  }

  /* Reemplaza el conjunto anterior por el nuevo */
  set_destroy(inventory->objs);
  inventory->objs = objs;
  return OK;
}

Status inventory_set_max_objs(Inventory *inventory, int max_objs)
{
  /* Comprueba la validez de los datos */
  if (inventory == NULL || max_objs < 0)
  {
    return ERROR;
  }

  inventory->max_objs = max_objs;
  return OK;
}

Status inventory_add_object(Inventory *inventory, Id obj_id)
{
  /* Comprueba la validez de los datos */
  if (inventory == NULL || obj_id == NO_ID)
  {
    return ERROR;
  }

  /* Comprueba si el inventario ha alcanzado su limite */
  if (inventory_is_full(inventory))
  {
    return ERROR;
  }

  /* Añade el objeto al conjunto */
  return set_add(inventory->objs, obj_id);
}

Status inventory_del_object(Inventory *inventory, Id obj_id)
{
  /* Comprueba la validez de los datos */
  if (inventory == NULL || obj_id == NO_ID)
  {
    return ERROR;
  }

  /* Elimina el objeto del conjunto */
  return set_del(inventory->objs, obj_id);
}

BOOL inventory_is_full(Inventory *inventory)
{
  /* Si el inventario es NULL, se asume lleno como proteccion */
  if (inventory == NULL)
  {
    return TRUE;
  }

  /* Comprueba si la cantidad de IDs iguala o supera el maximo permitido */
  if (set_get_numberid(inventory->objs) >= inventory->max_objs)
  {
    return TRUE;
  }

  return FALSE;
}

Status inventory_print(Inventory *inventory)
{
  /* Comprueba la validez del puntero */
  if (inventory == NULL)
  {
    return ERROR;
  }

  /* Imprime la informacion por salida estandar */
  fprintf(stdout, "--> Inventory (Max Objs: %d):\n", inventory->max_objs);
  set_print(inventory->objs);

  return OK;
}
