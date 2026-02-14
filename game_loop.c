/**
 * @brief Define el bucle principal del juego.
 * @file game_loop.c
 * @author Rodrigo & Unai
 * @version 2.0
 * @date 12-03-2024
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"

/* Prototipos de funciones privadas */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
void game_loop_cleanup(Game game, Graphic_engine *gengine);

/**
 * @brief Función principal del juego.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param argc Número de argumentos de la línea de comandos.
 * @param argv Array de cadenas de la línea de comandos.
 * @return EXIT_SUCCESS si el juego termina correctamente, EXIT_FAILURE en caso de error.
 */
int main(int argc, char *argv[]) {
  Game game;
  Graphic_engine *gengine;
  int result;
  Command *last_cmd;

  /* Control de argumentos: se debe proporcionar un fichero de datos del juego */
  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  /* Inicialización del juego y del motor gráfico */
  result = game_loop_init(&game, &gengine, argv[1]);
  if (result != EXIT_SUCCESS) {
    fprintf(stderr, "Error while initializing game.\n");
    return EXIT_FAILURE;
  }

  last_cmd = game_get_last_command(&game);

  /* Bucle principal del juego */
  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(&game) == FALSE)) {
    graphic_engine_paint_game(gengine, &game);
    command_get_user_input(last_cmd);
    game_actions_update(&game, last_cmd);
  }

  /* Liberación de recursos */
  game_loop_cleanup(game, gengine);

  return EXIT_SUCCESS;
}

/**
 * @brief Inicializa el juego y el motor gráfico.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Puntero a la estructura del juego.
 * @param gengine Puntero al puntero del motor gráfico.
 * @param file_name Nombre del fichero de datos del juego.
 * @return EXIT_SUCCESS si la inicialización es correcta, EXIT_FAILURE en caso de error.
 */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name) {
  if (game_create_from_file(game, file_name) == ERROR) {
    return EXIT_FAILURE;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    game_destroy(game);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/**
 * @brief Libera la memoria del juego y del motor gráfico.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param game Estructura del juego.
 * @param gengine Puntero al motor gráfico.
 */
void game_loop_cleanup(Game game, Graphic_engine *gengine) {
  game_destroy(&game);
  graphic_engine_destroy(gengine);
}
