/**
 * @brief Inventario
 *
 * @file inventory.h
 * @author Rodrigo
 * @version 1.0
 * @date 23-03-2026
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "set.h"
#include "types.h"

/**
 * @brief Define el inventario.
 */
typedef struct _Inventory Inventory;

/**
 * @brief Crea un inventario.
 * @author Rodrigo
 *
 * @param max_objs Máximo de objetos.
 * @return Puntero al nuevo inventario. NULL si hay error.
 */
Inventory *inventory_create(int max_objs);

/**
 * @brief Destruye un inventario.
 * @author Rodrigo
 *
 * @param inventory Puntero al inventario a destruir.
 * @return OK si el inventario se destruye, ERROR si no.
 */
Status inventory_destroy(Inventory *inventory);

/**
 * @brief Obtiene el conjunto de objetos del inventario.
 * @author Rodrigo
 *
 * @param inventory Puntero al inventario.
 * @return Un puntero al conjunto de objetos, NULL si hay algún error.
 */
Set *inventory_get_objs(Inventory *inventory);

/**
 * @brief Obtiene el máximo de objetos que el inventario puede albergar.
 * @author Rodrigo
 *
 * @param inventory Puntero al inventario.
 * @return Máximo posible de objetos dentro del inventario, -1 si ocurre un error.
 */
int inventory_get_max_objs(Inventory *inventory);

/**
 * @brief Establece el conjunto de objetos para el inventario.
 * @author Rodrigo
 *
 * @param inventory Puntero al inventario.
 * @param objs Puntero al conjunto de objetos para ser asignado al inventario.
 * @return OK si se asignó bien, si no ERROR.
 */
Status inventory_set_objs(Inventory *inventory, Set *objs);

/**
 * @brief Establece el máximo de objetos para el inventario.
 * @author Rodrigo
 *
 * @param inventory Puntero al inventario.
 * @param max_objs Máximo de objetos que el inventario puede albergar.
 * @return OK si el valor se asignó bien, si no ERROR.
 */
Status inventory_set_max_objs(Inventory *inventory, int max_objs);

/**
 * @brief Añade un objeto al inventario.
 * @author Rodrigo
 *
 * @param inventory Puntero al inventario.
 * @param obj_id El ID del objeto a añadir.
 * @return OK si el objeto se añadió con éxito, de lo contrario ERROR.
 */
Status inventory_add_object(Inventory *inventory, Id obj_id);

/**
 * @brief Elimina un objeto del inventario.
 * @author Rodrigo
 *
 * @param inventory Puntero al inventario.
 * @param obj_id El ID del objeto a eliminar.
 * @return OK si el objeto se eliminó con éxito, de lo contrario ERROR.
 */
Status inventory_del_object(Inventory *inventory, Id obj_id);

/**
 * @brief Comprueba si el inventario está lleno.
 * @author Rodrigo
 *
 * @param inventory Puntero al inventario.
 * @return TRUE si el inventario está lleno, de lo contrario FALSE.
 */
BOOL inventory_is_full(Inventory *inventory);

/**
 * @brief Imprime los datos del inventario.
 * @author Rodrigo
 *
 * Esta función es para fines de depuración. Imprime el número máximo de objetos
 * y el conjunto de objetos en el inventario.
 *
 * @param inventory Puntero al inventario para imprimir en la terminal.
 * @return OK si el inventario se imprimió con éxito, de lo contrario ERROR.
 */
Status inventory_print(Inventory *inventory);

#endif