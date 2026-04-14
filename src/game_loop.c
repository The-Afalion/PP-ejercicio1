/**
 * @brief Contiene el bucle principal de ejecución del juego
 *
 * @file game_loop.c
 * @author Unai
 * @version 1.0
 * @date 15-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"
#include "game_actions.h"
#include <time.h>

int main(int argc, char *argv[])
{
  Game *game = NULL;
  Command *command = NULL;
  Graphic_engine *gengine;
  FILE *log_file = NULL;
  char *log_filename = NULL;

  /* Inicializacion de la semilla aleatoria */
  srand(time(NULL));

  /* Comprueba los argumentos de entrada */
  if (argc < 2)
  {
    fprintf(stderr, "Uso: %s <game_data_file> [-l <log_file>]\n", argv[0]);
    return 1;
  }

  /* Gestiona la apertura del archivo log si se solicita */
  if (argc > 3 && strcmp(argv[2], "-l") == 0)
  {
    log_filename = argv[3];
    log_file = fopen(log_filename, "w");
    if (log_file == NULL)
    {
      fprintf(stderr, "Error opening log file.\n");
      return 1;
    }
  }

  /* Inicializacion del juego desde archivo */
  if (game_create_from_file(&game, argv[1]) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    if (log_file)
    {
      fclose(log_file);
    }
    return 1;
  }

  /* Inicializacion del motor grafico */
  if ((gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    if (log_file)
    {
      fclose(log_file);
    }
    return 1;
  }

  command = game_get_last_command(game);

  /* Bucle principal del juego */
  while ((command_get_code(command) != EXIT) && !game_get_finished(game))
  {
    /* Actualiza la interfaz grafica pre-comando */
    graphic_engine_paint_game(gengine, game, game_get_last_command_status(game), FALSE);

    /* Obtiene la entrada del usuario */
    command_get_user_input(command);

    /* Procesa el comando y actualiza el estado */
    game_set_last_command_status(game, game_actions_update(game, command));

    /* Registro en log si aplica */
    if (log_file)
    {
      char *last_input = command_get_last_input(command);
      if (last_input)
      {
        last_input[strcspn(last_input, "\n")] = 0;
        fprintf(log_file, "%s: %s\n", last_input, game_get_last_command_status(game) == OK ? "OK" : "ERROR");
      }
    }

    /* Actualiza la interfaz grafica post-comando */
    graphic_engine_paint_game(gengine, game, game_get_last_command_status(game), TRUE);
    sleep(1);

    /* Procesa el cambio de turno */
    game_next_turn(game);
  }

  /* Imprime el estado final antes de salir */
  graphic_engine_paint_game(gengine, game, game_get_last_command_status(game), TRUE);

  /* Liberacion de recursos generales */
  game_destroy(game);
  graphic_engine_destroy(gengine);

  if (log_file)
  {
    fclose(log_file);
  }

  return 0;
}
