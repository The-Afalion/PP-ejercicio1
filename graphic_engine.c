/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Unai
 * @version 1.0
 * @date 15-02-2026
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

#define WIDTH_MAP 48
#define WIDTH_DES 29
#define WIDTH_BAN 25
#define HEIGHT_MAP 24
#define HEIGHT_BAN 1
#define HEIGHT_HLP 3
#define HEIGHT_FDB 3
#define MAX_OBJECTS 100

struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback;
};

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  if (ge)
  {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL)
  {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}
/* Dibuja una fila de 3 espacios (Oeste, Centro, Este) horizontalmente */
void _paint_row(Area *area, Game *game, Id id_w, Id id_c, Id id_e, char *tag_c) {
    char str[512];
    char line_w[50], line_c[50], line_e[50];
    Space *s_w = game_get_space(game, id_w);
    Space *s_c = game_get_space(game, id_c);
    Space *s_e = game_get_space(game, id_e);
    char **g_w = s_w ? space_get_gdesc(s_w) : NULL;
    char **g_c = s_c ? space_get_gdesc(s_c) : NULL;
    char **g_e = s_e ? space_get_gdesc(s_e) : NULL;
    
    int i;
    char left_conn;
    char right_conn;

    /* 1. Borde superior */
    sprintf(line_w, id_w != NO_ID ? " +-----------+ " : "               ");
    sprintf(line_c, id_c != NO_ID ? " +--%3d------+ " : "               ", (int)id_c);
    sprintf(line_e, id_e != NO_ID ? " +-----------+ " : "               ");
    sprintf(str, "%s%s%s", line_w, line_c, line_e);
    screen_area_puts(area, str);

    /* 2. Contenido de GDESC (filas) */
    for (i = 0; i < GDESC_ROWS; i++) {
        /* Lógica para Oeste */
        if (s_w && g_w) sprintf(line_w, " |%11s| ", g_w[i]);
        else sprintf(line_w, "               ");

        /* Lógica para Centro (con tag y flechas) */
        if (s_c && g_c) {
            char central_content[12];
            strcpy(central_content, g_c[i]);
            
            /* Flechas laterales solo en la fila central del dibujo */
            left_conn = (i == 2 && id_w != NO_ID) ? '<' : '|';
            right_conn = (i == 2 && id_e != NO_ID) ? '>' : '|';
            sprintf(line_c, "%c%s%c", left_conn, central_content, right_conn);
        } else {
            sprintf(line_c, "               ");
        }

        /* Lógica para Este */
        if (s_e && g_e) sprintf(line_e, " |%11s| ", g_e[i]);
        else sprintf(line_e, "               ");

        sprintf(str, "%s%s%s", line_w, line_c, line_e);
        screen_area_puts(area, str);
    }

    /* 3. Borde inferior y Tag */
    sprintf(line_w, id_w != NO_ID ? " +-----------+ " : "               ");
    sprintf(line_c, id_c != NO_ID ? " +-----------+ %s" : "               ", tag_c ? tag_c : "");
    sprintf(line_e, id_e != NO_ID ? " +-----------+ " : "               ");
    sprintf(str, "%s%s%s", line_w, line_c, line_e);
    screen_area_puts(area, str);

    if (g_w) free(g_w);
    if (g_c) free(g_c);
    if (g_e) free(g_e);
}
void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void _paint_space(Area *area, Game *game, Id space_id, Id id_east, Id id_west, char *tag) {
  
    char str[255];
    char **gdesc = NULL;
    Space *space = NULL;
    int i, k;
    Id char_id = NO_ID;
    Character *character = NULL;
    const char *char_gdesc = NULL;
    
    char obj_str[25] = "";
    Object *obj = NULL;

    char left_ind[5];
    char right_ind[5];
    char line_content[15];
    char temp[20];
    if (space_id == NO_ID) {
        for (i = 0; i < GDESC_ROWS + 4; i++) { 
            screen_area_puts(area, " ");
        }
        return;
    }

    space = game_get_space(game, space_id);
    gdesc = space_get_gdesc(space);
    char_id = space_get_character(space);
    
    if (char_id != NO_ID) {
        character = game_get_character(game, char_id);
        if (character && character_get_health(character) > 0) {
            char_gdesc = character_get_gdesc(character);
        }
    }
    for (k = 0; k < MAX_OBJECTS; k++) {
        if (game_get_object_location(game, k) == space_id) {
            obj = game_get_object(game, k);
            if (obj) {
                if (strlen(obj_str) > 0 && strlen(obj_str) < 9) {
                    strcat(obj_str, " ");
                }
                strncat(obj_str, object_get_name(obj), 9 - strlen(obj_str));
            }
        }
    }
    sprintf(str, "  +-----------+");
    screen_area_puts(area, str);

    sprintf(str, "  |%11d|", (int)space_id);
    screen_area_puts(area, str);

    if (gdesc) {
        for (i = 0; i < GDESC_ROWS; i++) {
            strcpy(left_ind, "  ");
            strcpy(right_ind, "  ");

            if (i == 2) {
                if (id_west != NO_ID) strcpy(left_ind, "<-");
                if (id_east != NO_ID) strcpy(right_ind, "->");
            }

            strncpy(line_content, gdesc[i], 9);
            line_content[9] = '\0';

            if (i == 2 && char_gdesc) {
                int len = strlen(char_gdesc);
                int start = (9 - len) / 2;
                if (start >= 0 && start + len <= 9) {
                    strncpy(line_content + start, char_gdesc, len);
                }
            }

            sprintf(str, "%s| %-9s |%s", left_ind, line_content, right_ind);

            if (i == GDESC_ROWS - 1) {
                 sprintf(temp, " %s", tag ? tag : "");
                 strcat(str, temp);
            }
            screen_area_puts(area, str);
        }
        free(gdesc);
    } else {
        for (i = 0; i < GDESC_ROWS; i++) {
            sprintf(str, "  |           |");
            screen_area_puts(area, str);
        }
    }
    if (strlen(obj_str) > 0) {
        sprintf(str, "  | %-9s |", obj_str);
    } else {
        sprintf(str, "  |           |");
    }
    screen_area_puts(area, str);

    sprintf(str, "  +-----------+");
    screen_area_puts(area, str);
}
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Status last_cmd_status)
{
  Id id_act = NO_ID, id_n = NO_ID, id_s = NO_ID, id_e = NO_ID, id_w = NO_ID;
  Id id_nw = NO_ID, id_ne = NO_ID, id_sw = NO_ID, id_se = NO_ID;
  Id obj_loc = NO_ID;
  Space *space_tmp = NULL;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  char *chat_msg = NULL;
  Player *player = NULL;
  Character *character = NULL;
  Object *obj = NULL;

  /* 1. Paint the MAP area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    /* Obtenemos la cruz principal (N, S, E, O) */
    space_tmp = game_get_space(game, id_act);
    id_n = space_get_north(space_tmp);
    id_s = space_get_south(space_tmp);
    id_e = space_get_east(space_tmp);
    id_w = space_get_west(space_tmp);

    /* Obtenemos las esquinas para completar el mapa 3x3 */
    if (id_n != NO_ID) {
        space_tmp = game_get_space(game, id_n);
        id_nw = space_get_west(space_tmp);
        id_ne = space_get_east(space_tmp);
    }
    if (id_s != NO_ID) {
        space_tmp = game_get_space(game, id_s);
        id_sw = space_get_west(space_tmp);
        id_se = space_get_east(space_tmp);
    }

    /* --- FILA NORTE (Oeste-Norte-Este) --- */
    _paint_row(ge->map, game, id_nw, id_n, id_ne, "");
    
    /* Conector vertical Norte */
    screen_area_puts(ge->map, id_n != NO_ID ? "                     ^" : " ");

    /* --- FILA ACTUAL (Oeste-Centro-Este) --- */
    _paint_row(ge->map, game, id_w, id_act, id_e, "(Player)");

    /* Conector vertical Sur */
    screen_area_puts(ge->map, id_s != NO_ID ? "                     v" : " ");

    /* --- FILA SUR (Oeste-Sur-Este) --- */
    _paint_row(ge->map, game, id_sw, id_s, id_se, "");
  }

  /* 2. Paint the DESCRIPTION area */
  screen_area_clear(ge->descript);

  /* --- Objects List --- */
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
  screen_area_puts(ge->descript, " ");

  /* --- Characters List --- */
  screen_area_puts(ge->descript, " Characters:");
  for (i = 0; i < MAX_CHARACTERS; i++) {
      character = game_get_character(game, i);
      if (character) {
          Id char_loc = game_get_character_location(game, i);
          if (char_loc != NO_ID) {
              int health = character_get_health(character);
              if (health > 0) {
                  sprintf(str, "  %-10s: %d (%d)", character_get_name(character), (int)char_loc, health);
              } else {
                  sprintf(str, "  %-10s: %d (DEAD)", character_get_name(character), (int)char_loc);
              }
              screen_area_puts(ge->descript, str);
          }
      }
  }
  screen_area_puts(ge->descript, " ");

  /* --- Player Info --- */
  player = game_get_player(game);
  sprintf(str, " Player: %d (%d)", (int)player_get_location(player), player_get_health(player));
  screen_area_puts(ge->descript, str);

  if (player_get_object(player) != NO_ID)
  {
    obj = game_get_object(game, player_get_object(player));
    sprintf(str, " Player has: %s", obj ? object_get_name(obj) : "Unknown");
  }
  else
  {
    sprintf(str, " Player has no objects");
  }
  screen_area_puts(ge->descript, str);

  /* 3. Paint the BANNER area */
  screen_area_puts(ge->banner, "  The haunted castle game ");

  /* 4. Paint the HELP area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next/n, back/b, exit/e, take/t, drop/d");
  screen_area_puts(ge->help, str);
  sprintf(str, "     left/l, right/r, attack/a, chat/c");
  screen_area_puts(ge->help, str);

  /* 5. Paint the FEEDBACK area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], last_cmd_status == OK ? "OK" : "ERROR");
  screen_area_puts(ge->feedback, str);

  chat_msg = game_get_chat_message(game);
  if (chat_msg && chat_msg[0] != '\0') {
      sprintf(str, " Chat: %s", chat_msg);
      screen_area_puts(ge->feedback, str);
      game_set_chat_message(game, "");
  }

  /* 6. Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
