/**
 * @brief Implementa el módulo de enlaces
 *
 * @file link.c
 * @author Unai
 * @version 1.0
 * @date 13-04-2026
 * @copyright GNU Public License
 */

#include "link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SINGLE_ELEM 1

struct _Link
{
    Id id;                /*!<  Identificador del enlace */
    char nom[WORD_SIZE];  /*!< Nombre del enlace */
    Id origin;            /*!< Id del espacio de origen */
    Id destination;       /*!< Id del espacio de destino */
    Directions direction; /*!< Dirección del enlace */
    BOOL open;            /*!< Indica si el enlace está abierto o cerrado */
};

Link *link_create(Id id)
{
    Link *new_link = NULL;

    /* Si nos pasan un ID inválido */
    if (id == NO_ID)
    {
        return NULL;
    }

    new_link = (Link *)calloc(SINGLE_ELEM, sizeof(Link));

    /* Comprobación por si falla la reserva de memoria */
    if (new_link == NULL)
    {
        return NULL;
    }

    /* Rellenamos los datos básicos con valores por defecto */
    new_link->id = id;
    new_link->nom[0] = '\0';
    new_link->origin = NO_ID;
    new_link->destination = NO_ID;
    new_link->direction = NO_DIRECTION;
    new_link->open = FALSE;

    return new_link;
}

Status link_destroy(Link *link)
{
    /* Comprueba si el enlace es NULL */
    if (!link)
    {
        return ERROR;
    }

    /* Liberamos el enlace */
    free(link);
    return OK;
}

Status link_set_name(Link *link, char *name)
{
    /* Nos aseguramos de que ni el enlace ni el nombre sean NULL */
    if (!link || !name)
    {
        return ERROR;
    }
    /* Copiamos el nombre */
    strcpy(link->nom, name);
    return OK;
}

Status link_set_origin(Link *link, Id origin)
{
    /* Comprueba que el enlace exista */
    if (!link)
    {
        return ERROR;
    }
    link->origin = origin;
    return OK;
}

Status link_set_destination(Link *link, Id destination)
{
    /* Comprueba que el enlace exista */
    if (!link)
    {
        return ERROR;
    }
    link->destination = destination;
    return OK;
}

Status link_set_direction(Link *link, Directions direction)
{
    /* Comprueba que el enlace exista */
    if (!link || direction < N || direction > D)
    {
        return ERROR;
    }
    link->direction = direction;
    return OK;
}

Status link_set_open(Link *link, BOOL open)
{
    /* Comprueba que el enlace exista */
    if (!link)
    {
        return ERROR;
    }
    link->open = open;
    return OK;
}

Id link_get_id(Link *link)
{
    /* Comprueba si es NULL y devuelve su ID */
    if (!link)
    {
        return NO_ID;
    }
    return link->id;
}

char *link_get_name(Link *link)
{
    /* Comprueba si es NULL y devuelve el nombre */
    if (!link)
    {
        return NULL;
    }
    return link->nom;
}

Id link_get_origin(Link *link)
{
    /* Devuelve el espacio de origen o NO_ID si hay error */
    if (!link)
    {
        return NO_ID;
    }
    return link->origin;
}

Id link_get_destination(Link *link)
{
    /* Devuelve el espacio de destino o NO_ID si hay error */
    if (!link)
    {
        return NO_ID;
    }
    return link->destination;
}

Directions link_get_direction(Link *link)
{
    /* Devuelve la dirección del enlace o la dirección por defecto (U) */
    if (!link)
    {
        return NO_DIRECTION;
    }
    return link->direction;
}

BOOL link_get_open(Link *link)
{
    /* Comprueba el estado del enlace */
    if (!link)
    {
        return FALSE;
    }
    return link->open;
}

Status link_set_id(Link *link, Id id)
{
    /* Nos aseguramos de que el enlace no sea NULL y el ID sea válido */
    if (!link || id == NO_ID)
    {
        return ERROR;
    }
    link->id = id;
    return OK;
}

Status link_print(Link *link)
{
    /* Comprueba si el enlace es válido antes de imprimir */
    if (!link)
    {
        return ERROR;
    }

    /* Imprime toda la información almacenada en la estructura */
    fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->nom);
    fprintf(stdout, "    | Origin: %ld\n", link->origin);
    fprintf(stdout, "    | Destination: %ld\n", link->destination);
    fprintf(stdout, "    | Direction (enum): %d\n", link->direction);
    fprintf(stdout, "    | Open: %s\n", link->open ? "TRUE" : "FALSE");

    return OK;
}
