#ifndef SET_H
#define SET_H
#include "types.h"
typedef struct Set Set;
Set* set_create(Id id);
Status set_destroy(Set* s);
Status set_add(Set* s,Id id);
Status set_del(Set* s,Id id);
Status set_find(Set* s,Id id);
void set_print(Set* s);
Id set_get_id(Set*s,int indx);
int set_get_numberid(Set*s);
int* set_get_ids(Set*s);
#endif