 * @file game_loop.c
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @autor Profesores PPROG
 * @versión 0
 * @fecha 27-01-2025
 * @copyright Licencia pública GNU
 */

#include <stdio.h>
#include <stdlib.h>
#include <cadena.h>
#include "motor_gráfico.h"
#include "juego.h"
#include "comando.h"
#include "acciones_juego.h"

int principal(int argc, char *argv[])
{
 Juego *juego = NULO;
 Comando *comando = NULO;
 Graphic_engine *gengine;
 ARCHIVO *log_file = NULO;
 char *log_filename = NULO;

  si (argc < 2)
  {
    fprintf(stderr, "Uso: %s <game_data_file> [-l <log_file>]\n", argv[0]);
    retorno 1;
  }

  si (argc > 3 && strcmp(argv[2], "-l") == 0)
  {
 log_filename = argv[3];
 log_file = fopen(log_nombre de archivo, "w");
    if (log_file == NULL)
    {
      fprintf(stderr, "Error opening log file.\n");
      return 1;
    }
  }

  if ((game_create_from_file(&game, argv[1])) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    if (log_file) fclose(log_file);
    return 1;
  }

  if ((gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    if (log_file) fclose(log_file);
    return 1;
  }
  command=game_get_last_command(game);
  while ((command_get_code(command) != EXIT) && !game_get_finished(game))
  {
    graphic_engine_paint_game(gengine, game, game_get_last_command_status(game));
 * @brief Define el bucle del juego/**(command);
    game_set_last_command_status(game, game_actions_update(game, command));

    if (log_file)
    {
      char* last_input = command_get_last_input(command);
      /* Remove newline character from last_input */
      last_input[strcspn(last_input, "\n")] = 0;
      fprintf(log_file, "%s: %s\n", last_input, game_get_last_command_status(game) == OK ? "OK" : "ERROR");
    }
  }

  /* Paint the last state */
  graphic_engine_paint_game(gengine, game, game_get_last_command_status(game));

  game_destroy(game);
  graphic_engine_destroy(gengine);

  if (log_file)
  {
    fclose(log_file);
  }

  return 0;
}
