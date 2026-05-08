/**
 * @brief Implementa el motor gráfico textual
 *
 * @file graphic_engine.c
 * @author Unai
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "graphic_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "character.h"
#include "player.h"
#include "object.h"

#define WIDTH_MAP 67
#define WIDTH_DES 55
#define WIDTH_BAN 25
#define HEIGHT_MAP 30
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3
#define MAX_OBJECTS 100
#define ROOM_WIDTH 19

struct _Graphic_engine
{
    Area *map, *descript, *banner, *help, *feedback;
};

void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, BOOL is_act);
Status graphic_engine_get_objects_str(Game *game, Space *space, char *str);
void graphic_engine_get_vertical_exits_str(Game *game, Space *space, char *str);

Graphic_engine *graphic_engine_create()
{
    static Graphic_engine *ge = NULL;

    /* Comprueba si el motor grafico ya ha sido instanciado */
    if (ge)
    {
        return ge;
    }

    /* Inicializacion del entorno de pantalla fisica */
    screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
    ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));

    /* Comprueba si la reserva de memoria falla */
    if (ge == NULL)
    {
        return NULL;
    }

    /* Delimitacion de las sub-areas de la interfaz grafica */
    ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
    ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
    ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
    ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
    ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

    return ge;
}

void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, BOOL is_act)
{
    Space *west, *east, *up, *down;
    Character *character;
    char str[255], west_str[85], middle_str[85], east_str[85], obj_list[ROOM_WIDTH + 1];
    char vertical_exits[3];
    const char *character_gdesc;
    char (*space_gdesc)[GDESC_COLS];
    int i;
    Status obj_list_status;
    BOOL west_discovered = FALSE, east_discovered = FALSE, middle_discovered = FALSE;

    /* Comprueba la validez de los argumentos base */
    if (!area || !middle)
    {
        return;
    }

    /* Recoleccion de referencias de los espacios adyacentes */
    west = game_get_space(game, game_get_connection(game, space_get_id(middle), W));
    east = game_get_space(game, game_get_connection(game, space_get_id(middle), E));
    up = game_get_space(game, game_get_connection(game, space_get_id(middle), U));
    down = game_get_space(game, game_get_connection(game, space_get_id(middle), D));
    middle_discovered = space_get_discovered(middle);

    /* Generacion grafica del borde superior */
    if (!west)
    {
        sprintf(west_str, "                     ");
    }
    else
    {
        sprintf(west_str, "+-------------------+");
    }

    if (!east)
    {
        east_str[0] = '\0'; /* EVITA EL LINE WRAP */
    }
    else
    {
        sprintf(east_str, "+-------------------+");
    }

    sprintf(str, "%s  +-------%s------+  %s", west_str, up ? "^-Up-^" : "------", east_str);
    screen_area_puts(area, str);

    /* CONSTRUCCION DEL BLOQUE DE PERSONAJES E IDs (CORREGIDO CON %-6s PARA ALINEAR BORDES) */
    if (!west)
    {
        sprintf(west_str, "                     ");
    }
    else if (!(west_discovered = space_get_discovered(west)))
    {
        graphic_engine_get_vertical_exits_str(game, west, vertical_exits);
        sprintf(west_str, "|%s              %3d|", vertical_exits, (int)space_get_id(west));
    }
    else
    {
        graphic_engine_get_vertical_exits_str(game, west, vertical_exits);
        character = game_get_character(game, space_get_character(west, 0));
        character_gdesc = character ? character_get_gdesc(character) : "      ";
        sprintf(west_str, "|%s  %-6s  %7d|", vertical_exits, character_gdesc, (int)space_get_id(west));
    }

    character = game_get_character(game, space_get_character(middle, 0));
    character_gdesc = character ? character_get_gdesc(character) : "      ";

    if (middle_discovered)
    {
        graphic_engine_get_vertical_exits_str(game, middle, vertical_exits);
        sprintf(middle_str, "  |%s %-3s %-6s %5d|  ", vertical_exits, is_act == TRUE ? player_get_gdesc(game_get_player(game)) : "   ", character_gdesc, (int)space_get_id(middle));
    }
    else
    {
        graphic_engine_get_vertical_exits_str(game, middle, vertical_exits);
        sprintf(middle_str, "  |%s              %3d|  ", vertical_exits, (int)space_get_id(middle));
    }

    if (!east)
    {
        east_str[0] = '\0'; /* EVITA EL LINE WRAP */
    }
    else if (!(east_discovered = space_get_discovered(east)))
    {
        graphic_engine_get_vertical_exits_str(game, east, vertical_exits);
        sprintf(east_str, "|%s              %3d|", vertical_exits, (int)space_get_id(east));
    }
    else
    {
        graphic_engine_get_vertical_exits_str(game, east, vertical_exits);
        character = game_get_character(game, space_get_character(east, 0));
        character_gdesc = character ? character_get_gdesc(character) : "      ";
        sprintf(east_str, "|%s  %-6s  %7d|", vertical_exits, character_gdesc, (int)space_get_id(east));
    }

    sprintf(str, "%s%s%s", west_str, middle_str, east_str);
    screen_area_puts(area, str);

    /* Generacion de la representacion visual interior (gdesc) */
    for (i = 0; i < GDESC_ROWS; i++)
    {
        if (!west)
        {
            sprintf(west_str, "                     ");
        }
        else if (!(west_discovered))
        {
            sprintf(west_str, "|                   |");
        }
        else
        {
            space_gdesc = space_get_gdesc(west);
            if (!space_gdesc)
            {
                sprintf(west_str, "|                   |");
            }
            else
            {
                sprintf(west_str, "|%s      |", space_gdesc[i]);
            }
        }

        space_gdesc = space_get_gdesc(middle);
        if (middle_discovered)
        {
            if (!space_gdesc)
            {
                sprintf(middle_str, "  |                   |  ");
            }
            else
            {
                sprintf(middle_str, "  |%s      |  ", space_gdesc[i]);
            }
        }
        else
        {
            sprintf(middle_str, "  |                   |  ");
        }

        if (!east)
        {
            east_str[0] = '\0'; /* EVITA EL LINE WRAP */
        }
        else if (!(east_discovered))
        {
            sprintf(east_str, "|                   |");
        }
        else
        {
            space_gdesc = space_get_gdesc(east);
            if (!space_gdesc)
            {
                sprintf(east_str, "|                   |");
            }
            else
            {
                sprintf(east_str, "|%s      |", space_gdesc[i]);
            }
        }

        sprintf(str, "%s%s%s", west_str, middle_str, east_str);
        screen_area_puts(area, str);
    }

    /* Evaluacion y renderizado de los objetos presentes en cada espacio */
    if (!west)
    {
        sprintf(west_str, "                     ");
    }
    else if (!(west_discovered))
    {
        sprintf(west_str, "|                   |");
    }
    else
    {
        obj_list_status = graphic_engine_get_objects_str(game, west, obj_list);
        if (obj_list_status == ERROR)
        {
            sprintf(west_str, "|                   |");
        }
        else
        {
            sprintf(west_str, "|%s|", obj_list);
        }
    }

    if (middle_discovered)
    {
        obj_list_status = graphic_engine_get_objects_str(game, middle, obj_list);
        if (obj_list_status == ERROR)
        {
            sprintf(middle_str, " %s|                   |%s ", (west) ? "<" : " ", (east) ? ">" : " ");
        }
        else
        {
            sprintf(middle_str, " %s|%s|%s ", (west) ? "<" : " ", obj_list, (east) ? ">" : " ");
        }
    }
    else
    {
        sprintf(middle_str, "  |                   |  ");
    }

    if (!east)
    {
        east_str[0] = '\0'; /* EVITA EL LINE WRAP */
    }
    else if (!(east_discovered))
    {
        sprintf(east_str, "|                   |");
    }
    else
    {
        obj_list_status = graphic_engine_get_objects_str(game, east, obj_list);
        if (obj_list_status == ERROR)
        {
            sprintf(east_str, "|                   |");
        }
        else
        {
            sprintf(east_str, "|%s|", obj_list);
        }
    }

    sprintf(str, "%s%s%s", west_str, middle_str, east_str);
    screen_area_puts(area, str);

    /* Construccion grafica del borde inferior de cierre */
    if (!west)
    {
        sprintf(west_str, "                     ");
    }
    else
    {
        sprintf(west_str, "+-------------------+");
    }

    if (!east)
    {
        east_str[0] = '\0'; /* EVITA EL LINE WRAP */
    }
    else
    {
        sprintf(east_str, "+-------------------+");
    }

    /* Renderizado de vDownv si hay conexion hacia abajo */
    sprintf(str, "%s  +-------%s------+  %s", west_str, down ? "vDownv" : "------", east_str);
    screen_area_puts(area, str);
}

Status graphic_engine_get_objects_str(Game *game, Space *space, char *str)
{
    Id *n;
    int i, cont;
    char car[ROOM_WIDTH + 1] = "";
    char temp[ROOM_WIDTH + 1] = "";

    if (!game || !space || !str) return ERROR;

    n = space_get_objects(space);
    if (!n) return ERROR;

    cont = space_get_number_of_objects(space);
    if (cont <= 0)
    {
        /* Rellenar con espacios si la sala esta vacia */
        while (strlen(car) < ROOM_WIDTH) strcat(car, " ");
        strcpy(str, car);
        return OK;
    }

    for (i = 0; i < cont; i++)
    {
        Object *obj = game_get_object(game, n[i]);
        if (!obj) continue;

        /* Preparamos el nombre (con coma delante si no es el primero) */
        if (strlen(car) == 0) {
            sprintf(temp, "%s", object_get_name(obj));
        } else {
            sprintf(temp, ", %s", object_get_name(obj));
        }

        /* Solo lo añadimos si NO rompemos el limite de la habitacion (19) */
        if (strlen(car) + strlen(temp) <= ROOM_WIDTH) {
            strcat(car, temp);
        } else {
            /* Si ya no cabe, dejamos de imprimir objetos para no deformar el mapa */
            break;
        }
    }

    /* Padding de la cadena para asegurar el ancho constante del formato grafico */
    while (strlen(car) < ROOM_WIDTH)
    {
        strcat(car, " ");
    }

    strcpy(str, car);
    return OK;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
    /* Comprueba la validez del motor grafico */
    if (!ge)
    {
        return;
    }

    /* Liberacion de las areas visuales estructuradas */
    screen_area_destroy(ge->map);
    screen_area_destroy(ge->descript);
    screen_area_destroy(ge->banner);
    screen_area_destroy(ge->help);
    screen_area_destroy(ge->feedback);

    screen_destroy();
    free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Status last_cmd_status, BOOL paint_cmd)
{
    Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, object_in_backpack = NO_ID, *obj_ids = NULL;
    Space *act = NULL;
    char str[255];
    CommandCode last_cmd = UNKNOWN;
    extern char *cmd_to_str[N_CMD][N_CMDT];
    int i;
    Player *player = NULL;
    Character *character = NULL;
    Object *obj = NULL;
    int obj_found = 0;
    int max_backpack_obj = 0;
 
    /* Comprueba la validez del juego */
    if (!game)
    {
        return;
    }
    
    /* Procedimiento de actualizacion de la capa visual del mapa */
    screen_area_clear(ge->map);
    if ((id_act = game_get_player_location(game)) != NO_ID)
    {
        act = game_get_space(game, id_act);
        id_back = game_get_connection(game, space_get_id(act), N);
        id_next = game_get_connection(game, space_get_id(act), S);

        /* Renderizado direccional Norte y Actual (Evitando saltar de la altura HEIGHT_MAP) */
        if (id_back != NO_ID)
        {
            graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_back), FALSE);
            screen_area_puts(ge->map, "                                 ^");
        }

        graphic_engine_paint_spaces_row(ge->map, game, act, TRUE);

        /* Renderizado direccional Sur */
        if (id_next != NO_ID)
        {
            screen_area_puts(ge->map, "                                 v");
            graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_next), FALSE);
        }
    }

    /* Procedimiento de actualizacion del panel de descripcion */
    screen_area_clear(ge->descript);
    screen_area_puts(ge->descript, "You are in:");
    if (act)    {
        screen_area_puts(ge->descript, space_get_name(act));
    }

    /* Renderizado de ubicaciones de objetos globales */
    screen_area_puts(ge->descript, " Objects:");
    for (i = 0; i < space_get_number_of_objects(act); i++)
    {
        obj_ids = space_get_objects(act);
        if (obj_ids[i] != NO_ID)
        {
            if (game_get_object_location(game,obj_ids[i])==game_get_player_location(game))
            {
                obj = game_get_object(game, obj_ids[i]);
                if (obj)
                {
                    sprintf(str, "  - %s -Health:%d -Damage:%d -Dependency:%ld", object_get_name(obj),object_get_health(obj),object_get_damage(obj),object_get_dependency(obj));
                    screen_area_puts(ge->descript, str);
                }
            }
        }
    }


    /* Renderizado del estado y ubicacion de los personajes */
    screen_area_puts(ge->descript, " Characters:");
    for (i = 0; i < MAX_CHARACTERS; i++)
    {
        character = game_get_character_at(game, i);
        if (character)
        {
            Id char_loc = game_get_character_location(game, character_get_id(character));
            if (game_get_character_location(game,character_get_id(character))==game_get_player_location(game))
            {
                int health = character_get_health(character);
                if (health > 0)
                {
                    sprintf(str, "  %-10s: %d (%d) - %s- Money: %d", character_get_name(character), (int)char_loc, health, character_get_friendly(character) ? "Friend" : "Enemy",character_get_money(character));
                }
                else
                {
                    sprintf(str, "  %-10s: %d (DEAD)", character_get_name(character), (int)char_loc);
                }
                screen_area_puts(ge->descript, str);
            }
        }
    }

    /* Monitorizacion del estado del jugador activo */
    player = game_get_player(game);
    max_backpack_obj = inventory_get_max_objs(player_get_backpack(player));
    sprintf(str, " Player P%ld: %d (%d)", player_get_id(player), (int)player_get_location(player), player_get_health(player));
    screen_area_puts(ge->descript, str);
    if (player_get_team(player) != NO_ID)
    {
        sprintf(str, " Team: %ld", player_get_team(player));
        screen_area_puts(ge->descript, str);
    }

    screen_area_puts(ge->descript, "Player has: ");
    for (i = 0; i < max_backpack_obj; i++)
    {
        object_in_backpack = player_get_object(player, i);
        if (object_in_backpack != NO_ID)
        {
            obj = game_get_object(game, object_in_backpack);
            if (obj)
            {
               sprintf(str, "  - %s (%ld) -Money:%d", object_get_name(obj), object_get_id(obj), player_get_money(player));
            }
            else
            {
                sprintf(str, "  - Unknown");
            }
            screen_area_puts(ge->descript, str);
            obj_found++;
        }
    }

    if (obj_found == 0)
    {
        screen_area_puts(ge->descript, "no objects");
    }

    /* Renderizado del sistema de dialogos e inspeccion */
    screen_area_puts(ge->descript, " ");
    screen_area_puts(ge->descript, game_get_chat_message(game));
    game_set_chat_message(game, "");

    screen_area_puts(ge->descript, " ");
    if (game_get_object_desc(game) != NULL)
    {
        if (strlen(game_get_object_desc(game)) > 0)
        {
            sprintf(str, "Item description: %s", game_get_object_desc(game));
            screen_area_puts(ge->descript, str);
            game_set_object_desc(game, "");
        }
    }

    /* Actualizacion de modulos auxiliares: Banner, Help y Feedback */
    sprintf(str, "  Turn Player: P%ld ", game_get_current_player_id(game));
    screen_area_puts(ge->banner, str);

    screen_area_clear(ge->help);
    screen_area_puts(ge->help, " The commands you can use are:");
    screen_area_puts(ge->help, "     exit/e, take/t, drop/d, attack/a, chat/c, move/m");
    screen_area_puts(ge->help, "     inspect/i, recruit/r, abandon/ab, use/u, team/tm, open/o,steal/st,buy/b,save/s,load/l,colab/cl");
    screen_area_puts(ge->help, "     move: north/south/east/west/up/down; U/D marks up/down exits");

    if (paint_cmd == TRUE)
    {
        last_cmd = command_get_code(game_get_last_command(game));
        if (last_cmd_status == OK)
        {
            sprintf(str, " P%ld %s (%s): OK", game_get_current_player_id(game), cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
        }
        else
        {
            sprintf(str, " P%ld %s (%s): ERROR", game_get_current_player_id(game), cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
        }
        screen_area_puts(ge->feedback, str);
    }

    /* Refresco por pantalla del ciclo completo */
    screen_paint(game_get_turn(game));

    if (game_get_finished(game)) {
        printf("GAME OVER\n");
    } else if (command_get_code(game_get_last_command(game)) == EXIT) {
        printf("GAME EXIT\n");
    } else {
        printf("prompt:> ");
    }
}

void graphic_engine_get_vertical_exits_str(Game *game, Space *space, char *str)
{
    if (!game || !space || !str)
    {
        return;
    }

    str[0] = game_get_connection(game, space_get_id(space), U) != NO_ID ? 'U' : ' ';
    str[1] = game_get_connection(game, space_get_id(space), D) != NO_ID ? 'D' : ' ';
    str[2] = '\0';
}