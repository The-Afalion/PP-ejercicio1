/**
 * @brief Implementa el módulo de conjuntos
 *
 * @file set.c
 * @author Unai
 * @version 1.0
 * @date 15-03-2026
 * @copyright GNU Public License
 */

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDS 100
/**
 * @brief Set
 * Estructura de datos que representa un conjunto de identificadores.
 */
struct Set
{
    Id ids[MAX_IDS]; /*!<  Array interno de identificadores */
    int n_ids;       /*!< Número actual de identificadores almacenados */
};

Set *set_create()
{
    Set *s = NULL;
    int i;

    s = (Set *)malloc(sizeof(Set));

    /* Comprueba si falla la reserva de memoria */
    if (s == NULL)
    {
        return NULL;
    }

    /* Inicializamos el número de elementos a 0 */
    s->n_ids = 0;

    /* Rellenamos el array de IDs con NO_ID */
    for (i = 0; i < MAX_IDS; i++)
    {
        s->ids[i] = NO_ID;
    }

    return s;
}

Status set_destroy(Set *s)
{
    /* Comprueba si el conjunto es NULL */
    if (s == NULL)
    {
        return ERROR;
    }

    /* Libera la memoria del conjunto */
    free(s);
    return OK;
}

Status set_add(Set *s, Id id)
{
    /* Comprueba que el conjunto, el ID y la capacidad sean válidos */
    if (s == NULL || id == NO_ID || s->n_ids >= MAX_IDS)
    {
        return ERROR;
    }

    /* Comprueba si el ID ya existe para evitar duplicados */
    if (set_find(s, id) == OK)
    {
        return ERROR;
    }

    /* Añade el ID en la primera posición libre y aumenta el contador */
    s->ids[s->n_ids] = id;
    s->n_ids++;

    return OK;
}

Status set_del(Set *s, Id id)
{
    int i, j;

    /* Comprueba que el conjunto y el ID sean válidos */
    if (s == NULL || id == NO_ID)
    {
        return ERROR;
    }

    for (i = 0; i < s->n_ids; i++)
    {
        /* Busca el ID a eliminar */
        if (s->ids[i] == id)
        {
            /* Desplaza los elementos hacia la izquierda para rellenar el hueco */
            for (j = i; j < s->n_ids - 1; j++)
            {
                s->ids[j] = s->ids[j + 1];
            }

            /* Elimina el último elemento duplicado y reduce el contador */
            s->ids[s->n_ids - 1] = NO_ID;
            s->n_ids--;

            return OK;
        }
    }

    return ERROR;
}

Status set_find(Set *s, Id id)
{
    int i;

    /* Comprueba que el conjunto y el ID sean válidos */
    if (s == NULL || id == NO_ID)
    {
        return ERROR;
    }

    /* Busca el ID en el array */
    for (i = 0; i < s->n_ids; i++)
    {
        if (s->ids[i] == id)
        {
            return OK;
        }
    }

    return ERROR;
}

void set_print(Set *s)
{
    int i;

    /* Comprueba si el conjunto es válido antes de imprimir */
    if (s == NULL)
    {
        return;
    }

    /* Imprime todos los IDs almacenados */
    for (i = 0; i < s->n_ids; i++)
    {
        printf(" %ld", s->ids[i]);
    }
}

Id set_get_id(Set *s, int indx)
{
    /* Comprueba que el conjunto y el índice sean válidos */
    if (s == NULL || indx < 0 || indx >= s->n_ids)
    {
        return NO_ID;
    }

    /* Devuelve el ID en la posición indicada */
    return s->ids[indx];
}

int set_get_numberid(Set *s)
{
    /* Comprueba si el conjunto es NULL */
    if (s == NULL)
    {
        return 0;
    }

    /* Devuelve el número de elementos */
    return s->n_ids;
}

Id *set_get_ids(Set *s)
{
    /* Comprueba que el conjunto sea válido y no esté vacío */
    if (s == NULL || s->n_ids == 0)
    {
        return NULL;
    }

    /* Devuelve el puntero al array interno */
    return s->ids;
}
