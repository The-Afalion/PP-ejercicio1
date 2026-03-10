/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"
#include "game_actions.h"

int main(int argc, char *argv[])
{
  Game *game = NULL;
  Command *command = NULL;
  Graphic_engine *gengine;
  Status status = OK;

  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  if ((status = game_create_from_file(&game, argv[1])) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  command = command_create();
  while ((command_get_code(command) != EXIT) && !game_get_finished(game))
  {
    graphic_engine_paint_game(gengine, game, status);
    command_get_user_input(command);
    status = game_actions_update(game, command);
  }

  command_destroy(command); 
  game_destroy(game);
  graphic_engine_destroy(gengine);

  return 0;
}