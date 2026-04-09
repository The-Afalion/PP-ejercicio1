/**
 * @file game_loop.c
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 27-01-2025
 * @copyright Licencia publica GNU
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"
#include "game_actions.h"

int main(int argc, char *argv[]) {
  Game *game = NULL;
  Command *command = NULL;
  Graphic_engine *gengine;
  FILE *log_file = NULL;
  char *log_filename = NULL;

  if (argc < 2) {
    fprintf(stderr, "Uso: %s <game_data_file> [-l <log_file>]\\n", argv[0]);
    return 1;
  }

  if (argc > 3 && strcmp(argv[2], "-l") == 0) {
    log_filename = argv[3];
    log_file = fopen(log_filename, "w");
    if (log_file == NULL) {
      fprintf(stderr, "Error opening log file.\\n");
      return 1;
    }
  }

  if (game_create_from_file(&game, argv[1]) == ERROR) {
    fprintf(stderr, "Error while initializing game.\\n");
    if (log_file) fclose(log_file);
    return 1;
  }

  if ((gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\\n");
    game_destroy(game);
    if (log_file) fclose(log_file);
    return 1;
  }

  command = game_get_last_command(game);
  while ((command_get_code(command) != EXIT) && !game_get_finished(game)) {
    graphic_engine_paint_game(gengine, game, game_get_last_command_status(game));
    command_get_user_input(command);
    game_set_last_command_status(game, game_actions_update(game, command));

    if (log_file) {
      char* last_input = command_get_last_input(command);
      if (last_input) {
        last_input[strcspn(last_input, "\\n")] = 0;
        fprintf(log_file, "%s: %s\\n", last_input, game_get_last_command_status(game) == OK ? "OK" : "ERROR");
      }
    }

    graphic_engine_paint_game(gengine, game, game_get_last_command_status(game));
    sleep(3);
    game_next_turn(game);
  }

  /* Paint the last state */
  graphic_engine_paint_game(gengine, game, game_get_last_command_status(game));

  game_destroy(game);
  graphic_engine_destroy(gengine);

  if (log_file) {
    fclose(log_file);
  }

  return 0;
}
