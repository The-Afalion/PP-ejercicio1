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
/* Dibuja una fila de 3 espacios (Oeste, Centro, Este) horizontalmente */
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
    int i, k, len;

    /* Cadenas para guardar los nombres de los objetos */
    char obj_w[20] = "", obj_c[20] = "", obj_e[20] = "";
    Object *obj = NULL;

    /* 1. Búsqueda de objetos Oeste */
    if (id_w != NO_ID) {
        for (k = 0; k < MAX_OBJECTS; k++) {
            if (game_get_object_location(game, k) == id_w) {
                obj = game_get_object(game, k);
                if (obj) {
                    if (strlen(obj_w) > 0 && strlen(obj_w) < 9) strcat(obj_w, " ");
                    strncat(obj_w, object_get_name(obj), 9 - strlen(obj_w));
                }
            }
        }
    }

    /* 2. Búsqueda de objetos Centro */
    if (id_c != NO_ID) {
        for (k = 0; k < MAX_OBJECTS; k++) {
            if (game_get_object_location(game, k) == id_c) {
                obj = game_get_object(game, k);
                if (obj) {
                    if (strlen(obj_c) > 0 && strlen(obj_c) < 9) strcat(obj_c, " ");
                    strncat(obj_c, object_get_name(obj), 9 - strlen(obj_c));
                }
            }
        }
    }

    /* 3. Búsqueda de objetos Este */
    if (id_e != NO_ID) {
        for (k = 0; k < MAX_OBJECTS; k++) {
            if (game_get_object_location(game, k) == id_e) {
                obj = game_get_object(game, k);
                if (obj) {
                    if (strlen(obj_e) > 0 && strlen(obj_e) < 9) strcat(obj_e, " ");
                    strncat(obj_e, object_get_name(obj), 9 - strlen(obj_e));
                }
            }
        }
    }

    /* FILA 1: Borde superior */
    sprintf(line_w, id_w != NO_ID ? " +-----------+ " : "               ");
    sprintf(line_c, id_c != NO_ID ? " +-----------+ " : "               ");
    sprintf(line_e, id_e != NO_ID ? " +-----------+ " : "               ");
    sprintf(str, "%s%s%s", line_w, line_c, line_e);
    screen_area_puts(area, str);

    /* FILA 2: ID del espacio */
    sprintf(line_w, id_w != NO_ID ? " |%11d| " : "               ", (int)id_w);
    sprintf(line_c, id_c != NO_ID ? " |%11d| " : "               ", (int)id_c);
    sprintf(line_e, id_e != NO_ID ? " |%11d| " : "               ", (int)id_e);
    sprintf(str, "%s%s%s", line_w, line_c, line_e);
    screen_area_puts(area, str);

    /* FILA 3 a 7: GDESC */
    for (i = 0; i < GDESC_ROWS; i++) {
        if (s_w && g_w) sprintf(line_w, " | %-9s | ", g_w[i]);
        else if (id_w != NO_ID) sprintf(line_w, " |           | ");
        else sprintf(line_w, "               ");

        if (s_c && g_c) {
            char central[12];
            char left_conn = (i == 2 && id_w != NO_ID) ? '<' : '|';
            char right_conn = (i == 2 && id_e != NO_ID) ? '>' : '|';
            strncpy(central, g_c[i], 9);
            central[9] = '\0';
            sprintf(line_c, " %c %-9s %c ", left_conn, central, right_conn);
        } else if (id_c != NO_ID) {
            sprintf(line_c, " |           | ");
        } else {
            sprintf(line_c, "               ");
        }

        if (s_e && g_e) sprintf(line_e, " | %-9s | ", g_e[i]);
        else if (id_e != NO_ID) sprintf(line_e, " |           | ");
        else sprintf(line_e, "               ");

        sprintf(str, "%s%s%s", line_w, line_c, line_e);
        screen_area_puts(area, str);
    }

    /* FILA 8: Línea de Objetos y Tag del jugador */
    sprintf(line_w, id_w != NO_ID ? " | %-9s | " : "               ", obj_w);
    sprintf(line_c, id_c != NO_ID ? " | %-9s |%s" : "               ", obj_c, tag_c ? tag_c : "");
    sprintf(line_e, id_e != NO_ID ? " | %-9s | " : "               ", obj_e);
    
    sprintf(str, "%s%s%s", line_w, line_c, line_e);
    
    /* TRUCO CLAVE: Recortamos todos los espacios vacíos a la derecha. 
       Así la línea nunca superará el límite de 48 caracteres de tu mapa y no saltará. */
    len = strlen(str);
    while (len > 0 && str[len - 1] == ' ') {
        str[len - 1] = '\0';
        len--;
    }
    screen_area_puts(area, str);

    /* FILA 9: Borde inferior */
    sprintf(line_w, id_w != NO_ID ? " +-----------+ " : "               ");
    sprintf(line_c, id_c != NO_ID ? " +-----------+ " : "               ");
    sprintf(line_e, id_e != NO_ID ? " +-----------+ " : "               ");
    sprintf(str, "%s%s%s", line_w, line_c, line_e);
    
    /* Repetimos el truco aquí por si acaso */
    len = strlen(str);
    while (len > 0 && str[len - 1] == ' ') {
        str[len - 1] = '\0';
        len--;
    }
    screen_area_puts(area, str);
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

/* Helper function to paint a space with its gdesc, objects, and characters */
void _paint_space(Area *area, Game *game, Id space_id, Id id_east, Id id_west, char *tag) {
    char str[255], obj_str[25] = "";
    char **gdesc = NULL;
    Space *space = NULL;
    int i, k;
    Id char_id = NO_ID;
    Character *character = NULL;
    const char *char_gdesc = NULL;
    Object *obj = NULL;

    if (space_id == NO_ID) {
        /* 9 líneas vacías en total: Bordes(2) + ID(1) + Dibujo(5) + Objeto(1) */
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

    /* --- 1. BUSCAMOS LOS OBJETOS --- */
    for (k = 0; k < MAX_OBJECTS; k++) {
        if (game_get_object_location(game, k) == space_id) {
            obj = game_get_object(game, k);
            if (obj) {
                if (strlen(obj_str) > 0 && strlen(obj_str) < 9) {
                    strcat(obj_str, " ");
                }
                /* Recortamos a 9 caracteres para dejar los márgenes intactos */
                strncat(obj_str, object_get_name(obj), 9 - strlen(obj_str));
            }
        }
    }

    /* --- 2. BORDE SUPERIOR CONTINUO --- */
    sprintf(str, "  +-----------+");
    screen_area_puts(area, str);

    /* --- 3. LÍNEA DEL ID (Alineado a la derecha como en la foto) --- */
    sprintf(str, "  |%11d|", (int)space_id);
    screen_area_puts(area, str);

    /* --- 4. DIBUJO DEL ESPACIO (GDESC) --- */
    if (gdesc) {
        for (i = 0; i < GDESC_ROWS; i++) {
            char left_ind[5] = "  ";
            char right_ind[5] = "  ";
            char line_content[15];

            /* Flechas de movimiento para este/oeste */
            if (i == 2) {
                if (id_west != NO_ID) strcpy(left_ind, "<-");
                if (id_east != NO_ID) strcpy(right_ind, "->");
            }

            strncpy(line_content, gdesc[i], 9);
            line_content[9] = '\0';

            /* Overlay del personaje en el medio */
            if (i == 2 && char_gdesc) {
                int len = strlen(char_gdesc);
                int start = (9 - len) / 2;
                if (start >= 0 && start + len <= 9) {
                    strncpy(line_content + start, char_gdesc, len);
                }
            }

            /* Pintamos la línea con un espacio de margen interior: "| %-9s |" */
            sprintf(str, "%s| %-9s |%s", left_ind, line_content, right_ind);

            /* Añadir etiqueta de jugador (Player, ^, v) en la última línea */
            if (i == GDESC_ROWS - 1) {
                 char temp[20];
                 sprintf(temp, " %s", tag ? tag : "");
                 strcat(str, temp);
            }

            screen_area_puts(area, str);
        }
        free(gdesc);
    } else {
        /* Fallback si no hay dibujo en el fichero .dat */
        for (i = 0; i < GDESC_ROWS; i++) {
            sprintf(str, "  |           |");
            screen_area_puts(area, str);
        }
    }

    /* --- 5. LÍNEA DEL OBJETO (Con margen interior como en la foto) --- */
    if (strlen(obj_str) > 0) {
        sprintf(str, "  | %-9s |", obj_str);
    } else {
        sprintf(str, "  |           |");
    }
    screen_area_puts(area, str);

    /* --- 6. BORDE INFERIOR --- */
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
