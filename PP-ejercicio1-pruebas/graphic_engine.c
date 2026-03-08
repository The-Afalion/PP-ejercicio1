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
    char str[255];
    char **gdesc = NULL;
    Space *space = NULL;
    int i, k;
    char obj_char = ' ';
    Id char_id = NO_ID;
    Character *character = NULL;
    const char *char_gdesc = NULL;

    if (space_id == NO_ID) {
        /* Print empty space if ID is invalid */
        for (i = 0; i < GDESC_ROWS + 2; i++) { /* +2 for borders */
            screen_area_puts(area, " ");
        }
        return;
    }

    space = game_get_space(game, space_id);
    gdesc = space_get_gdesc(space);
    char_id = space_get_character(space);
    if (char_id != NO_ID) {
        character = game_get_character(game, char_id);
        if (character) {
            /* Only show character if alive */
            if (character_get_health(character) > 0) {
                char_gdesc = character_get_gdesc(character);
            }
        }
    }

    /* Check for objects in space */
    for (k = 0; k < MAX_OBJECTS; k++) {
        if (game_get_object_location(game, k) == space_id) {
            obj_char = '*'; /* Symbol for object */
            break;
        }
    }

    /* Top border with ID */
    sprintf(str, "  +--%3d------+", (int)space_id);
    screen_area_puts(area, str);

    if (gdesc) {
        for (i = 0; i < GDESC_ROWS; i++) {
            char left_ind[10] = "      ";
            char right_ind[10] = "      ";
            char line_content[20];

            /* Arrows for East/West on center line (index 2) */
            if (i == 2) {
                if (id_west != NO_ID) strcpy(left_ind, " <--  ");
                if (id_east != NO_ID) strcpy(right_ind, "  --> ");
            }

            strncpy(line_content, gdesc[i], 19);
            line_content[19] = '\0';

            /* Overlay character on line 2 (index 2) */
            if (i == 2 && char_gdesc) {
                int len = strlen(char_gdesc);
                int start = (9 - len) / 2;
                if (start >= 0 && start + len <= 9) {
                    strncpy(line_content + start, char_gdesc, len);
                }
            }

            /* Overlay object symbol on line 3 (index 3) */
            if (i == 3 && obj_char == '*') {
                /* Put '*' in center */
                if (strlen(line_content) > 4) {
                    line_content[4] = '*';
                }
            }

            sprintf(str, "%s|%s|%s", left_ind, line_content, right_ind);

            /* Show Tag on the last line */
            if (i == GDESC_ROWS - 1) {
                 char temp[20];
                 sprintf(temp, " %s", tag ? tag : "");
                 strcat(str, temp);
            }

            screen_area_puts(area, str);
        }
        free(gdesc);
    } else {
        /* Fallback */
        sprintf(str, "  |           |");
        screen_area_puts(area, str);
        sprintf(str, "  | %s       |", tag ? tag : "   ");
        screen_area_puts(area, str);
        sprintf(str, "  |           |");
        screen_area_puts(area, str);
        sprintf(str, "  |           |");
        screen_area_puts(area, str);
        sprintf(str, "  |           |");
        screen_area_puts(area, str);
    }

    /* Bottom border */
    sprintf(str, "  +-----------+");
    screen_area_puts(area, str);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Status last_cmd_status)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space *space_act = NULL;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  char *chat_msg = NULL;
  Player *player = NULL;
  Character *character = NULL;
  Object *obj = NULL;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);

    /* --- NORTH SPACE --- */
    _paint_space(ge->map, game, id_back, NO_ID, NO_ID, "^");

    /* Connector */
    if (id_back != NO_ID) {
        screen_area_puts(ge->map, "        ^");
    } else {
        screen_area_puts(ge->map, " ");
    }

    /* --- CURRENT SPACE --- */
    _paint_space(ge->map, game, id_act, space_get_east(space_act), space_get_west(space_act), "(Player)");

    /* Connector */
    if (id_next != NO_ID) {
        screen_area_puts(ge->map, "        v");
    } else {
        screen_area_puts(ge->map, " ");
    }

    /* --- SOUTH SPACE --- */
    _paint_space(ge->map, game, id_next, NO_ID, NO_ID, "v");
  }

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


  /* Paint in the banner area */
  screen_area_puts(ge->banner, " The haunted castle game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, exit or e");
  screen_area_puts(ge->help, str);
  sprintf(str, "     take or t, drop or d, left or l, right or r, attack or a, chat or c");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], last_cmd_status == OK ? "OK" : "ERROR");
  screen_area_puts(ge->feedback, str);

  /* Mostrar mensaje de chat si existe */
  chat_msg = game_get_chat_message(game);
  if (chat_msg && chat_msg[0] != '\0') {
      sprintf(str, " Chat: %s", chat_msg);
      screen_area_puts(ge->feedback, str);
      game_set_chat_message(game, "");
  }

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}