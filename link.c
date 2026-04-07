#include "link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SINGLE_ELEM 1
struct _Link {
    Id id;
    char nom[WORD_SIZE];
    Id origin;
    Id destination;
    Directions direction;
    BOOL open;
};

Link* link_create(Id id) {
    Link* new_link = NULL;

    if (id == NO_ID) {
        return NULL;
    }
    new_link = (Link *)calloc(SINGLE_ELEM, sizeof(Link));
    if (new_link == NULL) {
        return NULL; 
    }

    new_link->id = id;
    new_link->nom[0] = '\0';
    new_link->origin = NO_ID;
    new_link->destination = NO_ID;
    new_link->direction = U; 
    new_link->open = FALSE;          

    return new_link;
}

Status link_destroy(Link* link) {
    if (!link) {
        return ERROR;
    }

    free(link);
    return OK;
}


Status link_set_name(Link* link, char* name) {
    if (!link || !name) {
        return ERROR;
    }
    strcpy(link->nom, name);
    return OK;
}

Status link_set_origin(Link* link, Id origin) {
    if (!link) {
        return ERROR;
    }
    link->origin = origin;
    return OK;
}

Status link_set_destination(Link* link, Id destination) {
    if (!link) {
        return ERROR;
    }
    link->destination = destination;
    return OK;
}

Status link_set_direction(Link* link, Directions direction) {
    if (!link) {
        return ERROR;
    }
    link->direction = direction;
    return OK;
}

Status link_set_open(Link* link, BOOL open) {
    if (!link) {
        return ERROR;
    }
    link->open = open;
    return OK;
}

Id link_get_id(Link* link) {
    if (!link) {
        return NO_ID;
    }
    return link->id;
}

char* link_get_name(Link* link) {
    if (!link) {
        return NULL;
    }
    return link->nom;
}

Id link_get_origin(Link* link) {
    if (!link) {
        return NO_ID;
    }
    return link->origin;
}

Id link_get_destination(Link* link) {
    if (!link) {
        return NO_ID;
    }
    return link->destination;
}

Directions link_get_direction(Link* link) {
    if (!link) {
        return U; 
    }
    return link->direction;
}

BOOL link_get_open(Link* link) {
    if (!link) {
        return FALSE; 
    }
    return link->open;
}
Status link_set_id(Link* link,Id id){
    if(!link||id==NO_ID){
        return ERROR;
    }
    link->id=id;
    return OK;
}

Status link_print(Link *link){
    if(!link){
        return ERROR;
    }
    fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->nom);
    fprintf(stdout, "    | Origin: %ld\n", link->origin);
    fprintf(stdout, "    | Destination: %ld\n", link->destination);
    fprintf(stdout, "    | Direction (enum): %d\n", link->direction);
    fprintf(stdout, "    | Open: %s\n", link->open ? "TRUE" : "FALSE");
    return OK;
}
