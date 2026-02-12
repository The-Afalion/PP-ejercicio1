#include <stdio.h>
#include <stdlib.h>
#include "radio.h"

int main() {
    Radio *r = NULL;

    r = radio_init();
    if (!r) {
        return 1;
    }

    printf("Inserting Paint It, Black... result...: %d\n", radio_newMusic(r, "id:\"111\" title:\"Paint It, Black\" artist:\"The Rolling Stones\" duration:\"202\""));
    printf("Inserting Every Breath You Take... result...: %d\n", radio_newMusic(r, "id:\"222\" title:\"Every Breath You Take\" artist:\"The Police\" duration:\"253\""));

    printf("\nInserting radio recommendation: 222 --> 1111\n\n");
    radio_newRelation(r, 222, 111);

    printf("111 --> 222? %s\n", radio_relationExists(r, 111, 222) ? "Yes" : "No");
    printf("222 --> 111? %s\n", radio_relationExists(r, 222, 111) ? "Yes" : "No");

    printf("Number of connections from 111: %d\n", radio_getNumberOfRelationsFromId(r, 111));
    printf("Number of connections from 222: %d\n", radio_getNumberOfRelationsFromId(r, 222));

    printf("\nRadio recommendations from Paint It, Black: 111\n");

    printf("\nAll radio recommendations:\n");
    radio_print(stdout, r);

    radio_free(r);

    return 0;
}
