
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "space.h"
#include "character.h"
#include "object.h"
#include "player.h"
#include "link.h"

Status game_managment_load_spaces(Game *game, char *filename)
{
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID;
    Space *space = NULL;
    Status status = OK;
    char *endptr;
    char gdesc[GDESC_ROWS][GDESC_COLS];
    int i;
    Status des;

    /* Comprueba la validez del nombre de archivo */
    if (!filename)
    {
        return ERROR;
    }

    file = fopen(filename, "r");
    /* Comprueba si falla la apertura del archivo */
    if (file == NULL)
    {
        return ERROR;
    }

    /* Lectura de espacios linea a linea */
    while (fgets(line, WORD_SIZE, file))
    {
        if (strncmp("#s:", line, 3) == 0)
        {
            toks = strtok(line + 3, "|");
            id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(name, toks);

            /* Extraccion de la descripcion grafica bidimensional */
            for (i = 0, des = OK; i < GDESC_ROWS; i++)
            {
                toks = strtok(NULL, "|");
                if (toks)
                {
                    if (strlen(toks) != GDESC_COLS - 1)
                    {
                        des = ERROR;
                    }
                    else
                    {
                        strcpy(gdesc[i], toks);
                    }
                }
                else
                {
                    strcpy(gdesc[i], "         ");
                }
            }

            /* Creacion e integracion del espacio en el motor de juego */
            space = space_create(id);
            if (space != NULL)
            {
                space_set_name(space, name);
                if (des != ERROR)
                {
                    space_set_gdesc(space, gdesc);
                }

                game_add_space(game, space);
            }
        }
    }

    /* Verificacion de errores de lectura */
    if (ferror(file))
    {
        status = ERROR;
    }

    fclose(file);
    return status;
}

Status game_managment_load_objects(Game *game, char *filename)
{
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID, location_id = NO_ID;
    Id dependency = NO_ID, open = NO_ID;
    Object *object = NULL;
    Status status = OK;
    char *endptr;
    char description[WORD_SIZE] = "";
    int health = 0;
    int movable = 0;

    /* Comprueba la validez del nombre de archivo */
    if (!filename)
    {
        return ERROR;
    }

    file = fopen(filename, "r");
    /* Comprueba si falla la apertura del archivo */
    if (file == NULL)
    {
        return ERROR;
    }

    /* Lectura de objetos linea a linea */
    while (fgets(line, WORD_SIZE, file))
    {
        if (strncmp("#o:", line, 3) == 0)
        {
            toks = strtok(line + 3, "|");
            id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            location_id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            if (toks)
            {
                strcpy(description, toks);
            }
            toks = strtok(NULL, "|");
            if (toks)
            {
                health = (int)strtol(toks, &endptr, 10);
            }
            else
            {
                health = 0;
            }
            toks = strtok(NULL, "|");
            if (toks)
            {
                movable = (int)strtol(toks, &endptr, 10);
            }
            else
            {
                movable = 0;
            }
            toks = strtok(NULL, "|");
            if (toks)
            {
                dependency = strtol(toks, &endptr, 10);
            }
            else
            {
                dependency = NO_ID;
            }
            toks = strtok(NULL, "|");
            if (toks)
            {
                open = strtol(toks, &endptr, 10);
            }
            else
            {
                open = NO_ID;
            }

            /* Creacion e integracion del objeto en el motor de juego */
            object = object_create(id);
            if (object != NULL)
            {
                object_set_name(object, name);
                object_set_desc(object, description);
                object_set_health(object, health);
                object_set_movable(object, movable ? TRUE : FALSE);
                object_set_dependency(object, dependency);
                object_set_open(object, open);

                game_add_object(game, object);
                game_set_object_location(game, location_id, id);
            }
        }
    }

    /* Verificacion de errores de lectura */
    if (ferror(file))
    {
        status = ERROR;
    }

    fclose(file);
    return status;
}

Status game_managment_load_characters(Game *game, char *filename)
{
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char gdesc[7] = "";
    char message[101] = "";
    char *toks = NULL;
    Id id = NO_ID, location_id = NO_ID;
    int health = 0;
    int friendly = 0;
    Character *character = NULL;
    Status status = OK;
    char *endptr;

    /* Comprueba la validez del nombre de archivo */
    if (!filename)
    {
        return ERROR;
    }

    file = fopen(filename, "r");
    /* Comprueba si falla la apertura del archivo */
    if (file == NULL)
    {
        return ERROR;
    }

    /* Lectura de personajes linea a linea */
    while (fgets(line, WORD_SIZE, file))
    {
        if (strncmp("#c:", line, 3) == 0)
        {
            toks = strtok(line + 3, "|");
            id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            strcpy(gdesc, toks);
            toks = strtok(NULL, "|");
            location_id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            health = (int)strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            friendly = (int)strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(message, toks);

            /* Creacion e integracion del personaje en el motor de juego */
            character = character_create(id);
            if (character != NULL)
            {
                character_set_name(character, name);
                character_set_gdesc(character, gdesc);
                character_set_health(character, health);
                character_set_friendly(character, friendly);
                character_set_message(character, message);

                game_add_character(game, character);
                game_set_character_location(game, location_id, id);
            }
        }
    }

    /* Verificacion de errores de lectura */
    if (ferror(file))
    {
        status = ERROR;
    }

    fclose(file);
    return status;
}

Status game_managment_load_players(Game *game, char *filename)
{
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char gdesc[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID, location_id = NO_ID;
    int health = 0, max_objs = 0;
    Player *player = NULL;
    Status status = OK;
    char *endptr;
    Space *starting_space = NULL;

    /* Comprueba la validez del nombre de archivo */
    if (!filename)
    {
        return ERROR;
    }

    file = fopen(filename, "r");
    /* Comprueba si falla la apertura del archivo */
    if (file == NULL)
    {
        return ERROR;
    }

    /* Lectura de jugadores linea a linea */
    while (fgets(line, WORD_SIZE, file))
    {
        if (strncmp("#p:", line, 3) == 0)
        {
            toks = strtok(line + 3, "|");
            id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            strcpy(gdesc, toks);
            toks = strtok(NULL, "|");
            location_id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            health = (int)strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            max_objs = (int)strtol(toks, &endptr, 10);

            /* Creacion e integracion del jugador en el motor de juego */
            player = player_create(id);
            if (player != NULL)
            {
                player_set_name(player, name);
                player_set_gdesc(player, gdesc);
                player_set_location(player, location_id);
                player_set_health(player, health);
                inventory_set_max_objs(player_get_backpack(player), max_objs);

                game_set_player(game, player);

                /* Asignacion del estado descubierto al espacio inicial */
                starting_space = game_get_space(game, location_id);
                if (starting_space != NULL)
                {
                    space_set_discovered(starting_space, TRUE);
                }
            }
        }
    }

    /* Verificacion de errores de lectura */
    if (ferror(file))
    {
        status = ERROR;
    }

    fclose(file);
    return status;
}

Status game_managment_load_links(Game *game, char *filename)
{
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID, origin = NO_ID, destination = NO_ID;
    int dir_int = 0, open_int = 0;
    Link *link = NULL;
    Status status = OK;
    char *endptr;

    /* Comprueba la validez del nombre de archivo */
    if (!filename)
    {
        return ERROR;
    }

    file = fopen(filename, "r");
    /* Comprueba si falla la apertura del archivo */
    if (file == NULL)
    {
        return ERROR;
    }

    /* Lectura de enlaces linea a linea */
    while (fgets(line, WORD_SIZE, file))
    {
        if (strncmp("#l:", line, 3) == 0)
        {
            toks = strtok(line + 3, "|");
            id = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            origin = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            destination = strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            dir_int = (int)strtol(toks, &endptr, 10);
            toks = strtok(NULL, "|");
            open_int = (int)strtol(toks, &endptr, 10);

            /* Creacion e integracion del enlace en el motor de juego */
            link = link_create(id);
            if (link != NULL)
            {
                link_set_name(link, name);
                link_set_origin(link, origin);
                link_set_destination(link, destination);
                link_set_direction(link, (Directions)dir_int);
                link_set_open(link, open_int ? TRUE : FALSE);

                game_add_link(game, link);
            }
        }
    }

    /* Verificacion de errores de lectura */
    if (ferror(file))
    {
        status = ERROR;
    }

    fclose(file);
    return status;
}
Status game_managment_save_game(Game *game, char *filename){
     FILE *file = NULL;
    int i,l;
    Player*p;
    Character*c;
    Object*o;
    Space*s;
    Link *e;
    /* Comprueba la validez del nombre de archivo */
    if (!filename||!game)
    {
        return ERROR;
    }

    file = fopen(filename, "w");
    /* Comprueba si falla la apertura del archivo */
    if (file == NULL)
    {
        return ERROR;
    }
    if(game_get_number_of_players(game)<0){
        return ERROR;
    }
    for(i=0;i<game_get_number_of_players(game);i++){
        p=game_get_player_from_index(game,i);
        fprintf(file, "#p:%d|%s|%s|%d|%d|%d|\n", player_get_id(p),player_get_name(p),player_get_gdesc(p),player_get_location(p),player_get_health(p),player_get_number_of_backpack(p));
    }
    if(game_get_number_of_characters(game)<0){
        return ERROR;
    }
    for(i=0;i<game_get_number_of_characters(game);i++){
        c=game_get_character_from_index(game,i);
        fprintf(file, "#c:%d|%s|%s|%d|%d|%d|%s|%d|\n", character_get_id(c),character_get_name(c),character_get_gdesc(c),game_get_character_location(game,character_get_id(c)),character_get_id(c),character_get_friendly(c),character_get_message(c),character_get_following(c));
    }
    if(game_get_number_of_objects(game)<0){
        return ERROR;
    }
    for(i=0;i<game_get_number_of_objects(game);i++){
        o=game_get_object_from_index(game,i);
        fprintf(file, "#o:%d|%s|%d|%s|%d|%d|%d|%d|\n", object_get_id(o),object_get_name(o),game_get_object_location(game,object_get_id(o)),game_get_character_location(game,object_get_id(o)),object_get_desc(o),object_get_health(o),object_get_movable(o),object_get_dependency(o),object_get_open(o));
    }
    if(game_get_number_of_space(game)<0){
        return ERROR;
    }
    for(i=0;i<game_get_number_of_space(game);i++){
        s=game_get_space_from_index(game,i);
        fprintf(file, "#s:%d|%s|%s|%s|%s|%s|%s|%d|\n",space_get_id(s),space_get_name(s),space_get_gdes_from_index(s,0),space_get_gdes_from_index(s,1),space_get_gdes_from_index(s,2),space_get_gdes_from_index(s,3),space_get_gdes_from_index(s,4),space_get_discovered(s));
       }  
if(game_get_number_of_links(game)<0){
    return ERROR;
}
    for(i=0;i<game_get_number_of_links(game);i++){
        e=game_get_link_from_index(game,i);
        fprintf(file,"#l:%d|%s|%d|%d|%d|\n",link_get_id(l),link_get_name(l),link_get_origin(l),link_get_destination(l),link_get_direction(l),link_get_open(l));
    }

    return OK;
}