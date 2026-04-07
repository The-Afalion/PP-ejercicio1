/**
 * @brief Implementa el motor gráfico textual
 *
 * @file graphic_engine.c
 * @author Unai
 * @version 1.0
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

/* Definiciones de dimensiones para las áreas de la interfaz */
#define WIDTH_MAP 55
#define WIDTH_DES 55
#define WIDTH_BAN 25
#define HEIGHT_MAP 30
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3
#define MAX_OBJECTS 100
#define ROOM_WIDTH 15

/**
 * @brief Estructura interna del motor gráfico
 * Organiza las distintas áreas de la pantalla (mapa, descripción, ayuda, etc.)
 */
struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback;
};

/* Prototipos de funciones privadas de dibujado */
void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, BOOL is_act);
Status graphic_engine_get_objects_str(Game *game, Space *space, char *str);

/**
 * @brief Inicializa el motor gráfico y reserva las áreas de pantalla
 * @author Unai
 * @return Puntero al motor gráfico creado o NULL en caso de error
 */
Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  if (ge) return ge;

  /* Inicialización de la pantalla física */
  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL) return NULL;

  /* ASIGNACIÓN: Definimos las coordenadas y tamaños de cada sub-área lógica */
  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

/**
 * @brief Dibuja una fila de espacios (Oeste, Centro, Este) en el área del mapa
 * @author Unai
 */
void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, BOOL is_act) {
    Space *west, *east;
    Character *character;
    char str[255], west_str[85], middle_str[85], east_str[85], obj_list[ROOM_WIDTH + 1];
    const char *character_gdesc;
    char (*space_gdesc)[GDESC_COLS];
    int i;
    Status obj_list_status;

    if (!area || !middle) return;

    /* Obtenemos los espacios adyacentes horizontalmente */
    west = game_get_space(game, game_get_connection(game, space_get_id(middle), W));
    east = game_get_space(game, game_get_connection(game, space_get_id(middle), E)); 

    /* 1. Dibujado de las líneas superiores de los cuadros */
    sprintf(str, "%s  +---------------+  %s",
        !west ? "                 " : "+---------------+",
        !east ? "                 " : "+---------------+"
    );
    screen_area_puts(area, str);

    /* 2. Dibujado de la información de personajes e IDs */
    if (!west) {
        sprintf(west_str, "                 ");
    } else {
        character = game_get_character(game, space_get_character(west));
        character_gdesc = !character ? "      " : character_get_gdesc(character);
        sprintf(west_str, "|     %s %3d|", character_gdesc, (int) space_get_id(west));
    }

    character = game_get_character(game, space_get_character(middle));
    character_gdesc = !character ? "      " : character_get_gdesc(character);
    /* INDICADOR: Si es el espacio actual, pintamos ^C> para señalar al jugador */
    sprintf(middle_str, "  | %s %s %3d|  ",is_act == TRUE ? "^C>" : "   " , character_gdesc, (int) space_get_id(middle));

    if (!east) {
        sprintf(east_str, "                 ");
    } else {
        character = game_get_character(game, space_get_character(east));
        character_gdesc = !character ? "      " : character_get_gdesc(character);
        sprintf(east_str, "|     %s %3d|", character_gdesc, (int) space_get_id(east));
    }

    sprintf(str, "%s%s%s", west_str, middle_str, east_str);
    screen_area_puts(area, str);

    /* 3. Dibujado de las líneas de descripción gráfica (GDESC) */
    for (i = 0; i < GDESC_ROWS; i++) {
        if (!west) sprintf(west_str, "                 ");
        else {
            space_gdesc = space_get_gdesc(west);
            sprintf(west_str, "|%s      |", !space_gdesc ? "         " : space_gdesc[i]);
        }

        space_gdesc = space_get_gdesc(middle);
        sprintf(middle_str, "  |%s      |  ", !space_gdesc ? "         " : space_gdesc[i]);

        if (!east) sprintf(east_str, "                 ");
        else {
            space_gdesc = space_get_gdesc(east);
            sprintf(east_str, "|%s      |", !space_gdesc ? "         " : space_gdesc[i]);
        }

        sprintf(str, "%s%s%s", west_str, middle_str, east_str);
        screen_area_puts(area, str);
    }

    /* 4. ASIGNACIÓN: Procesamos y pintamos la cadena de objetos de cada casilla */
    if (!west) sprintf(west_str, "                 ");
    else {
        obj_list_status = graphic_engine_get_objects_str(game, west, obj_list);
        sprintf(west_str, "|%s|", obj_list_status == ERROR ? "               " : obj_list);
    }

    obj_list_status = graphic_engine_get_objects_str(game, middle, obj_list);
    sprintf(middle_str, " %s|%s|%s ",
        (west) ? "<" : " ", /* Flecha indicadora de conexión oeste */
        obj_list_status == ERROR ? "               " : obj_list,
        (east) ? ">" : " "  /* Flecha indicadora de conexión este */
    );

    if (!east) sprintf(east_str, "                 ");
    else {
        obj_list_status = graphic_engine_get_objects_str(game, east, obj_list);
        sprintf(east_str, "|%s|", obj_list_status == ERROR ? "               " : obj_list);
    }

    sprintf(str, "%s%s%s", west_str, middle_str, east_str);
    screen_area_puts(area, str);

    /* 5. Dibujado de las líneas de cierre del cuadro */
    sprintf(str, "%s  +---------------+  %s",
        !west ? "                 " : "+---------------+",
        !east ? "                 " : "+---------------+"
    );
    screen_area_puts(area, str);
}

/**
 * @brief Genera una cadena con los nombres de los objetos presentes en un espacio
 * @author Unai
 */
Status graphic_engine_get_objects_str(Game *game, Space *space, char *str) {
    Id *n;
    int i,cont;
    char car[ROOM_WIDTH+1] = "";
    if(!game||!space||!str) return ERROR;

    n=space_get_objects(space);
    if(!n) return ERROR;

    cont=space_get_number_of_objects(space);
    if(cont==-1) return ERROR;

    /* CONCATENACIÓN: Recorremos los IDs y pegamos sus nombres en la cadena temporal */
    for(i=0;i<cont;i++){
        if(strlen(car)+strlen(object_get_name(game_get_object(game,n[i]))) < ROOM_WIDTH){
            strcat(car,object_get_name(game_get_object(game,n[i])));
        }
        if(i<cont-1) strcat(car,", ");
    }

    /* RELLENO: Si la cadena es corta, completamos con espacios para no romper el dibujo */
    while(strlen(car)<15) strcat(car, " ");
    
    strcpy(str,car);
    return OK;
}

/**
 * @brief Destruye el motor gráfico y libera la memoria de las áreas
 * @author Unai
 */
void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/**
 * @brief Función principal que coordina el pintado de toda la interfaz del juego
 * @author Unai
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Status last_cmd_status) {
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

  if (!game) return;

  /* --- 1. Pintado del ÁREA DEL MAPA --- */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    act = game_get_space(game, id_act);
    id_back = game_get_connection(game, space_get_id(act), N);
    id_next = game_get_connection(game, space_get_id(act), S);

    /* Lógica para dibujar hasta 3 filas (Norte, Actual, Sur) */
    if (game_get_connection(game, space_get_id(act), N) != NO_ID) {
        id_top = game_get_connection(game, id_back, N);
        if (id_top != NO_ID) {
            graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_top), FALSE);
            screen_area_puts(ge->map, " ");
        }
    }

    if (id_back != NO_ID) {
        graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_back), FALSE);
        screen_area_puts(ge->map, "                           ^"); /* Flecha de conexión norte */
    }

    /* PINTADO: El espacio donde está el jugador (is_act = TRUE) */
    graphic_engine_paint_spaces_row(ge->map, game, act, TRUE);

    if (id_next != NO_ID) {
        screen_area_puts(ge->map, "                           v"); /* Flecha de conexión sur */
        graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_next), FALSE);
    }
    /* ... resto de lógica de dibujado de espacios ... */
  }

  /* --- 2. Pintado del ÁREA DE DESCRIPCIÓN --- */
  screen_area_clear(ge->descript);

  /* LISTADO: Mostramos dónde está cada objeto del juego */
  screen_area_puts(ge->descript, " Objects:");
  for (i = 0; i < MAX_OBJECTS; i++) {
      obj = game_get_object(game, i);
      if (obj) {
          obj_loc = game_get_object_location(game, i);
          if (obj_loc != NO_ID) {
              sprintf(str, "  %-10s: %d", object_get_name(obj), (int)obj_loc);
              screen_area_puts(ge->descript, str);
          }
      }
  }

  /* LISTADO: Mostramos personajes vivos y su salud */
  screen_area_puts(ge->descript, " Characters:");
  for (i = 0; i < MAX_CHARACTERS; i++) {
      character = game_get_character(game, i);
      if (character) {
          Id char_loc = game_get_character_location(game, i);
          if (char_loc != NO_ID) {
              int health = character_get_health(character);
              if (health > 0) sprintf(str, "  %-10s: %d (%d)", character_get_name(character), (int)char_loc, health);
              else sprintf(str, "  %-10s: %d (DEAD)", character_get_name(character), (int)char_loc);
              screen_area_puts(ge->descript, str);
          }
      }
  }

  /* INFO JUGADOR: Ubicación, salud y objeto equipado */
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
        sprintf(str, "  - %s", obj ? object_get_name(obj) : "Unknown");
        screen_area_puts(ge->descript, str);
        obj_found++;
    }
  }
  if (obj_found == 0)
  {
    screen_area_puts(ge->descript, "no objects");
  }

  /* CHAT: Mostramos el mensaje si el jugador ha hablado con alguien */
  screen_area_puts(ge->descript, " ");
  screen_area_puts(ge->descript, game_get_chat_message(game));
  game_set_chat_message(game, ""); /* ELIMINACIÓN: Limpiamos el mensaje tras dibujarlo */
  /*MOSTRAMOS LA DESCRIPCION DEL OBJETO EXAMINADO*/
  screen_area_puts(ge->descript, " ");
  if (game_get_object_desc(game) != NULL && strlen(game_get_object_desc(game)) > 0)
  {
    sprintf(str, "Item description: %s", game_get_object_desc(game));
    screen_area_puts(ge->descript, str);
    game_set_object_desc(game, "");
  }

  /* --- 3. Pintado del BANNER, AYUDA y FEEDBACK --- */
sprintf(str, "  Turn Player :%d ", game_get_turn(game) + 1);
screen_area_puts(ge->banner, str);

  screen_area_clear(ge->help);
  screen_area_puts(ge->help, " The commands you can use are:");
  screen_area_puts(ge->help, "     exit/e, take/t, drop/d, attack/a, chat/c, move/m, inspect/i");

  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], last_cmd_status == OK ? "OK" : "ERROR");
  screen_area_puts(ge->feedback, str);

  /* Pintamos pantalla */
  screen_paint(RED);
  printf("prompt:> ");
}
