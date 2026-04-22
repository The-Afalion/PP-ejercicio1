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

#define WIDTH_MAP 55
#define WIDTH_DES 55
#define WIDTH_BAN 25
#define HEIGHT_MAP 30
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3
#define MAX_OBJECTS 100
#define ROOM_WIDTH 15

struct _Graphic_engine
{
    Area *map, *descript, *banner, *help, *feedback;
};

void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, BOOL is_act);
Status graphic_engine_get_objects_str(Game *game, Space *space, char *str);

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
    Space *west, *east;
    Character *character;
    char str[255], west_str[85], middle_str[85], east_str[85], obj_list[ROOM_WIDTH + 1];
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
    middle_discovered = space_get_discovered(middle);

    /* Generacion grafica del borde superior */
    if (!west)
    {
        sprintf(west_str, "                 ");
    }
    else
    {
        sprintf(west_str, "+---------------+");
    }

    if (!east)
    {
        sprintf(east_str, "                 ");
    }
    else
    {
        sprintf(east_str, "+---------------+");
    }

    sprintf(str, "%s  +---------------+  %s", west_str, east_str);
    screen_area_puts(area, str);

    /* Construccion del bloque de informacion de personajes e identificadores */
    if (!west)
    {
        sprintf(west_str, "                 ");
    }
    else if (!(west_discovered = space_get_discovered(west)))
    {
        sprintf(west_str, "|            %3d|", (int)space_get_id(west));
    }
    else
    {
        character = game_get_character(game, space_get_character(west, 0));
        if (!character)
        {
            character_gdesc = "      ";
        }
        else
        {
            character_gdesc = character_get_gdesc(character);
        }
        sprintf(west_str, "|     %s %3d|", character_gdesc, (int)space_get_id(west));
    }

    character = game_get_character(game, space_get_character(middle, 0));
    if (!character)
    {
        character_gdesc = "      ";
    }
    else
    {
        character_gdesc = character_get_gdesc(character);
    }

    if (middle_discovered)
    {
        sprintf(middle_str, "  | %s %s %3d|  ", is_act == TRUE ? player_get_gdesc(game_get_player(game)) : "   ", character_gdesc, (int)space_get_id(middle));
    }
    else
    {
        sprintf(middle_str, "  |            %3d|  ", (int)space_get_id(middle));
    }

    if (!east)
    {
        sprintf(east_str, "                 ");
    }
    else if (!(east_discovered = space_get_discovered(east)))
    {
        sprintf(east_str, "|            %3d|", (int)space_get_id(east));
    }
    else
    {
        character = game_get_character(game, space_get_character(east, 0));
        if (!character)
        {
            character_gdesc = "      ";
        }
        else
        {
            character_gdesc = character_get_gdesc(character);
        }
        sprintf(east_str, "|     %s %3d|", character_gdesc, (int)space_get_id(east));
    }

    sprintf(str, "%s%s%s", west_str, middle_str, east_str);
    screen_area_puts(area, str);

    /* Generacion de la representacion visual interior (gdesc) */
    for (i = 0; i < GDESC_ROWS; i++)
    {
        if (!west)
        {
            sprintf(west_str, "                 ");
        }
        else if (!(west_discovered))
        {
            sprintf(west_str, "|               |");
        }
        else
        {
            space_gdesc = space_get_gdesc(west);
            if (!space_gdesc)
            {
                sprintf(west_str, "|               |");
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
                sprintf(middle_str, "  |               |  ");
            }
            else
            {
                sprintf(middle_str, "  |%s      |  ", space_gdesc[i]);
            }
        }
        else
        {
            sprintf(middle_str, "  |               |  ");
        }

        if (!east)
        {
            sprintf(east_str, "                 ");
        }
        else if (!(east_discovered))
        {
            sprintf(east_str, "|               |");
        }
        else
        {
            space_gdesc = space_get_gdesc(east);
            if (!space_gdesc)
            {
                sprintf(east_str, "|               |");
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
        sprintf(west_str, "                 ");
    }
    else if (!(west_discovered))
    {
        sprintf(west_str, "|               |");
    }
    else
    {
        obj_list_status = graphic_engine_get_objects_str(game, west, obj_list);
        if (obj_list_status == ERROR)
        {
            sprintf(west_str, "|               |");
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
            sprintf(middle_str, " %s|               |%s ", (west) ? "<" : " ", (east) ? ">" : " ");
        }
        else
        {
            sprintf(middle_str, " %s|%s|%s ", (west) ? "<" : " ", obj_list, (east) ? ">" : " ");
        }
    }
    else
    {
        sprintf(middle_str, "  |               |  ");
    }

    if (!east)
    {
        sprintf(east_str, "                 ");
    }
    else if (!(east_discovered))
    {
        sprintf(east_str, "|               |");
    }
    else
    {
        obj_list_status = graphic_engine_get_objects_str(game, east, obj_list);
        if (obj_list_status == ERROR)
        {
            sprintf(east_str, "|               |");
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
        sprintf(west_str, "                 ");
    }
    else
    {
        sprintf(west_str, "+---------------+");
    }

    if (!east)
    {
        sprintf(east_str, "                 ");
    }
    else
    {
        sprintf(east_str, "+---------------+");
    }

    sprintf(str, "%s  +---------------+  %s", west_str, east_str);
    screen_area_puts(area, str);
}

Status graphic_engine_get_objects_str(Game *game, Space *space, char *str)
{
    Id *n;
    int i, cont;
    char car[ROOM_WIDTH + 1] = "";

    /* Comprueba la validez de los parametros */
    if (!game || !space || !str)
    {
        return ERROR;
    }

    n = space_get_objects(space);
    if (!n)
    {
        return ERROR;
    }

    cont = space_get_number_of_objects(space);
    if (cont == -1)
    {
        return ERROR;
    }

    /* Recorrido secuencial para concatenar los nombres de objetos */
    for (i = 0; i < cont; i++)
    {
        if (strlen(car) + strlen(object_get_name(game_get_object(game, n[i]))) < ROOM_WIDTH)
        {
            strcat(car, object_get_name(game_get_object(game, n[i])));
        }
        if (i < cont - 1)
        {
            strcat(car, ", ");
        }
    }

    /* Padding de la cadena para asegurar el ancho constante del formato grafico */
    while (strlen(car) < 15)
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
    Id id_act = NO_ID, id_back = NO_ID, id_top = NO_ID, id_next = NO_ID, obj_loc = NO_ID, object_in_backpack = NO_ID;
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

        /* Renderizado direccional Norte y Actual */
        if (game_get_connection(game, space_get_id(act), N) != NO_ID)
        {
            id_top = game_get_connection(game, id_back, N);
            if (id_top != NO_ID)
            {
                graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_top), FALSE);
                screen_area_puts(ge->map, " ");
            }
        }

        if (id_back != NO_ID)
        {
            graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_back), FALSE);
            screen_area_puts(ge->map, "                           ^");
        }

        graphic_engine_paint_spaces_row(ge->map, game, act, TRUE);

        /* Renderizado direccional Sur */
        if (id_next != NO_ID)
        {
            screen_area_puts(ge->map, "                           v");
            graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_next), FALSE);
        }
    }

    /* Procedimiento de actualizacion del panel de descripcion */
    screen_area_clear(ge->descript);

    /* Renderizado de ubicaciones de objetos globales */
    screen_area_puts(ge->descript, " Objects:");
    for (i = 0; i < MAX_OBJECTS; i++)
    {
        obj = game_get_object(game, i);
        if (obj)
        {
            obj_loc = game_get_object_location(game, i);
            if (obj_loc != NO_ID)
            {
                sprintf(str, "  %-10s: %d", object_get_name(obj), (int)obj_loc);
                screen_area_puts(ge->descript, str);
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
            if (char_loc != NO_ID)
            {
                int health = character_get_health(character);
                if (health > 0)
                {
                    sprintf(str, "  %-10s: %d (%d)", character_get_name(character), (int)char_loc, health);
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
    sprintf(str, " Player: %d (%d)", (int)player_get_location(player), player_get_health(player));
    screen_area_puts(ge->descript, str);

    screen_area_puts(ge->descript, "Player has: ");
    for (i = 0; i < max_backpack_obj; i++)
    {
        object_in_backpack = player_get_object(player, i);
        if (object_in_backpack != NO_ID)
        {
            obj = game_get_object(game, object_in_backpack);
            if (obj)
            {
                sprintf(str, "  - %s", object_get_name(obj));
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
    sprintf(str, "  Turn Player :%d ", game_get_turn(game) + 1);
    screen_area_puts(ge->banner, str);

    screen_area_clear(ge->help);
    screen_area_puts(ge->help, " The commands you can use are:");
    screen_area_puts(ge->help, "     exit/e, take/t, drop/d, attack/a, chat/c, move/m");
    screen_area_puts(ge->help, "     inspect/i, recruit/r, abandon/ab, open/o");
    screen_area_puts(ge->help, "     move: north/south/east/west/up/down");

    if (paint_cmd == TRUE)
    {
        last_cmd = command_get_code(game_get_last_command(game));
        if (last_cmd_status == OK)
        {
            sprintf(str, " %s (%s): OK", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
        }
        else
        {
            sprintf(str, " %s (%s): ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
        }
        screen_area_puts(ge->feedback, str);
    }

    /* Refresco por pantalla del ciclo completo */
    screen_paint(game_get_turn(game));
    printf("prompt:> ");
}
