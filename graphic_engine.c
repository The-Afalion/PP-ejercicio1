/**
 * @brief Implementa un motor gráfico textual para el juego.
 * @file graphic_engine.c
 * @author Rodrigo & Unai
 * @version 2.0
 * @date 12-03-2024
 * @copyright GNU Public License
 */

#include "graphic_engine.h"
#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

/* Definiciones de las dimensiones de las áreas de la pantalla */
#define WIDTH_MAP 48
#define WIDTH_DES 29
#define WIDTH_BAN 25
#define HEIGHT_MAP 13
#define HEIGHT_BAN 1
#define HEIGHT_HLP 3
#define HEIGHT_FDB 3

/**
 * @brief Estructura del Motor Gráfico
 * Almacena punteros a las diferentes áreas de la pantalla.
 */
struct _Graphic_engine {
  Area *map;      /*!< Área del mapa */
  Area *descript; /*!< Área de descripción */
  Area *banner;   /*!< Área del banner */
  Area *help;     /*!< Área de ayuda */
  Area *feedback; /*!< Área de feedback */
};

/**
 * @brief Crea el motor gráfico.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @return Un puntero al motor gráfico creado, o NULL si ocurre un error.
 */
Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  /* Inicialización de las áreas de la pantalla */
  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

/**
 * @brief Destruye el motor gráfico.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param ge Puntero al motor gráfico a destruir.
 */
void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) {
    return;
  }

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/**
 * @brief Dibuja el estado actual del juego en la pantalla.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param ge Puntero al motor gráfico.
 * @param game Puntero al juego.
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space *space_act = NULL;
  char obj_char = ' ';
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  /* 1. Dibuja el área del mapa */
  screen_area_clear(ge->map);
  id_act = game_get_player_location(game);
  if (id_act != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    obj_loc = game_get_object_location(game);

    /* Dibuja la casilla anterior (norte) */
    if (id_back != NO_ID) {
      obj_char = (obj_loc == id_back) ? '*' : ' ';
      sprintf(str, "  |         %2d|", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj_char);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    /* Dibuja la casilla actual */
    obj_char = (obj_loc == id_act) ? '*' : ' ';
    sprintf(str, "  +-----------+");

      screen_area_puts(ge->map, str);
    sprintf(str, "  | >o<     %2d|", (int)id_act);
    screen_area_puts(ge->map, str);
    sprintf(str, "  |     %c     |", obj_char);
    screen_area_puts(ge->map, str);
    sprintf(str, "  +-----------+");
    screen_area_puts(ge->map, str);

    /* Dibuja la casilla siguiente (sur) */
    if (id_next != NO_ID) {
      obj_char = (obj_loc == id_next) ? '*' : ' ';
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|", (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj_char);
      screen_area_puts(ge->map, str);
    }
  }

  /* 2. Dibuja el área de descripción */
  screen_area_clear(ge->descript);
  if (obj_loc != NO_ID) {
    sprintf(str, "  Object location: %d", (int)obj_loc);
  } else {
    sprintf(str, "  Object location: none");
  }
  screen_area_puts(ge->descript, str);

  if (player_get_object(game->player) != NO_ID) {
    sprintf(str, "  Player object: %d", (int)player_get_object(game->player));
  } else {
    sprintf(str, "  Player object: none");
  }
  screen_area_puts(ge->descript, str);

  /* 3. Dibuja el área del banner */
  screen_area_puts(ge->banner, " The haunted castle game ");

  /* 4. Dibuja el área de ayuda */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, exit or e, take or t, drop or d");
  screen_area_puts(ge->help, str);

  /* 5. Dibuja el área de feedback */
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* 6. Vuelca todo a la terminal */
  screen_paint();
  printf("prompt:> ");
}
