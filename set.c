#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDS 100 /* Defines a maximum size for the set */

struct Set {
    Id ids[MAX_IDS];
    int n_ids;
};

Set *set_create(Id id) {
    Set *s = NULL;
    int i;

    s = (Set *)malloc(sizeof(Set));
    if (s == NULL) {
        return NULL;
    }

    /* A new set is created empty. The 'id' parameter is ignored. */
    s->n_ids = 0;
    for (i = 0; i < MAX_IDS; i++) {
        s->ids[i] = NO_ID;
    }

    return s;
}

Status set_destroy(Set *s) {
    if (s == NULL) {
        return ERROR; /* Added NULL check */
    }
    free(s);
    return OK;
}

Status set_add(Set *s, Id id) {
    if (s == NULL || id == NO_ID || s->n_ids >= MAX_IDS) {
        return ERROR;
    }

    /* set_find returns OK if found, so if it is found, we cannot add it again. */
    if (set_find(s, id) == OK) {
        return ERROR; /* Already exists */
    }

    s->ids[s->n_ids] = id;
    s->n_ids++;

    return OK;
}

Status set_del(Set *s, Id id) {
    int i, j;

    if (s == NULL || id == NO_ID) {
        return ERROR;
    }

    for (i = 0; i < s->n_ids; i++) {
        if (s->ids[i] == id) {
            /* Shift elements to fill the gap */
            for (j = i; j < s->n_ids - 1; j++) {
                s->ids[j] = s->ids[j + 1];
            }
            s->ids[s->n_ids - 1] = NO_ID;
            s->n_ids--;
            return OK;
        }
    }

    return ERROR; /* Not found */
}

Status set_find(Set *s, Id id) {
    int i;
    if (s == NULL || id == NO_ID) {
        return ERROR;
    }

    for (i = 0; i < s->n_ids; i++) {
        if (s->ids[i] == id) {
            return OK; /* Found */
        }
    }
    return ERROR; /* Not found */
}

void set_print(Set *s) {
    int i;
    if (s == NULL) {
        return;
    }
    for (i = 0; i < s->n_ids; i++) {
        printf(" %ld", s->ids[i]);
    }
}

Id set_get_id(Set *s, int indx) {
    if (s == NULL || indx < 0 || indx >= s->n_ids) {
        return NO_ID;
    }
    return s->ids[indx];
}

int set_get_numberid(Set *s) {
    if (s == NULL) {
        return 0; /* A NULL set has 0 elements */
    }
    return s->n_ids;
}

Id* set_get_ids(Set *s) {
    if (s == NULL || s->n_ids == 0) {
        return NULL; /* Returns NULL if no elements */
    }

    return s->ids;
   
}
