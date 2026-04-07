/**
 * @brief Modulo invetario
 *
 * @file inventory.c
 * @author Rodrigo
 * @version 1.0
 * @date 23-06-2026
 * @copyright GNU Public License
 */

#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Inventario
 *
 * Estructura con toda la info del inventario
 */
struct _Inventory {
  Set *objs;
  int max_objs;
};

Inventory *inventory_create(int max_objs) {
  Inventory *inventory = NULL;

  if (max_objs < 0) {
    return NULL;
  }

  inventory = (Inventory *)malloc(sizeof(Inventory));
  if (inventory == NULL) {
    return NULL;
  }

<<<<<<< HEAD
  inventory->objs = set_create(1);
=======
  inventory->objs = set_create(NO_ID);
>>>>>>> 27fe3ab62e547d3bd143fd7a0080e5c56c75256e
  if (inventory->objs == NULL) {
    free(inventory);
    return NULL;
  }

  inventory->max_objs = max_objs;

  return inventory;
}

/** Libera la memoria del anterior inventario (destroy) y crea uno nuevo */
Status inventory_destroy(Inventory *inventory) {
  if (inventory == NULL) {
    return ERROR;
  }

  set_destroy(inventory->objs);
  free(inventory);

  return OK;
}

Set *inventory_get_objs(Inventory *inventory) {
  if (inventory == NULL) {
    return NULL;
  }
  return inventory->objs;
}

int inventory_get_max_objs(Inventory *inventory) {
  if (inventory == NULL) {
    return -1;
  }
  return inventory->max_objs;
}

/** Máximo de objetos */
Status inventory_set_objs(Inventory *inventory, Set *objs) {
  if (inventory == NULL || objs == NULL) {
    return ERROR;
  }

  set_destroy(inventory->objs);
  inventory->objs = objs;

  return OK;
}

Status inventory_set_max_objs(Inventory *inventory, int max_objs) {
  if (inventory == NULL || max_objs < 0) {
    return ERROR;
  }

  inventory->max_objs = max_objs;

  return OK;
}

/** Añade un objeto al inventario */
Status inventory_add_object(Inventory *inventory, Id obj_id) {
  if (inventory == NULL || obj_id == NO_ID) {
    return ERROR;
  }

  if (inventory_is_full(inventory)) {
    return ERROR;
  }

  return set_add(inventory->objs, obj_id);
}

/** Destruye un objeto del inventario */
Status inventory_del_object(Inventory *inventory, Id obj_id) {
  if (inventory == NULL || obj_id == NO_ID) {
    return ERROR;
  }

  return set_del(inventory->objs, obj_id);
}

/** Revisa que el inventario este lleno */
BOOL inventory_is_full(Inventory *inventory) {
  if (inventory == NULL) {
    return TRUE;
  }

  if (set_get_numberid(inventory->objs) >= inventory->max_objs) {
    return TRUE;
  }

  return FALSE;
}

Status inventory_print(Inventory *inventory) {
  if (inventory == NULL) {
    return ERROR;
  }

  fprintf(stdout, "--> Inventory (Max Objs: %d):\n", inventory->max_objs);
  set_print(inventory->objs);

  return OK;
}