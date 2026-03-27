#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef struct _Link Link;

typedef enum { norte, sur, este, oeste, desconocido } Direccion;

Link* link_create(Id id);
Status link_destroy(Link* link);
Status link_set_name(Link* link, char* name);
Status link_set_origin(Link* link, Id origin);
Status link_set_destination(Link* link, Id destination);
Status link_set_direction(Link* link, Direccion direction);
Status link_set_open(Link* link, BOOL open);
Id link_get_id(Link* link);
char* link_get_name(Link* link);
Id link_get_origin(Link* link);
Id link_get_destination(Link* link);
Direccion link_get_direction(Link* link);
BOOL link_get_open(Link* link);
Status link_print(Link *link);
Status link_set_id(Link* link,Id id);

#endif