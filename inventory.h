
#ifndef INVENTORY_H
#define INVENTORY_H

#include "set.h"
#include "types.h"

typedef struct _Inventory Inventory;

Inventory *inventory_create(int max_objs);

STATUS inventory_destroy(Inventory *inventory);

Set *inventory_get_objs(Inventory *inventory);

int inventory_get_max_objs(Inventory *inventory);

STATUS inventory_set_objs(Inventory *inventory, Set *objs);

STATUS inventory_set_max_objs(Inventory *inventory, int max_objs);

STATUS inventory_add_object(Inventory *inventory, Id obj_id);

STATUS inventory_del_object(Inventory *inventory, Id obj_id);

BOOL inventory_is_full(Inventory *inventory);

STATUS inventory_print(Inventory *inventory);

#endif
