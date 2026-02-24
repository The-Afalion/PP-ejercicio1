#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Set{
Id ids[WORD_SIZE];
int n_ids;
};
Set* set_create(Id id){
    int i;
    Set* s=NULL;
    if(id<0){
        return NULL;
    }
    s->ids[0]=id;
    for(i=1;i<WORD_SIZE;i++){
       s->ids[i]=NO_ID; 
    }
    s->n_ids=0;
    if(id!=NO_ID){
        s->n_ids++;
    }
    return s;
}
Status set_destroy(Set* s){
free(s);
return OK;
}

Status set_add(Set* s,Id id){
    int i;
    if(!s||id==NO_ID||s->n_ids==WORD_SIZE){
        return ERROR;
    }
    for(i=0;i<WORD_SIZE;i++){
        if(set_find(s,s->ids[i])){
            return ERROR;
        }
    }
    for(i=0;i<WORD_SIZE;i++){
        if(s->ids[i]==NO_ID){
             s->ids[s->n_ids]=id;
              s->n_ids++;
              return OK;
        }
    }
    return OK;
}
Status set_del(Set* s,Id id){
    int i;
    if(!s||id== NO_ID){
        return ERROR;
    }
    for(i=0;i<WORD_SIZE;i++){
        if(set_find(s,s->ids[i])){
           s->ids[i]=NO_ID;
           s->n_ids--;
           return OK;
        }
    }
    return ERROR;
}
Status set_find(Set* s,Id id){
     int i;
    if(!s||id== NO_ID){
        return ERROR;
    }

    for(i=0;i<WORD_SIZE;i++){
        if(s->ids[i]==id){
            return OK;
        }
    }
    return ERROR;
}
void set_print(Set* s){
int i;
    for(i=0;i<WORD_SIZE;i++){
        if(s->ids[i]!=NO_ID){
            printf(" %d",s->ids[i]);
        }
    }
}
Id set_get_id(Set*s,int indx){
    if(!s||indx<0){
        return -1;
    }
    return s->ids[indx];
}