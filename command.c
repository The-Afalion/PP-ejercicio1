/**
 * @brief Implementa el intérprete de comandos, gestionando la entrada del usuario.
 * @file command.c
 * @author Rodrigo & Unai
 * @version 2.0
 * @date 12-03-2024
 * @copyright GNU Public License
 */

#include "command.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGHT 30

/**
 * @brief Mapeo de códigos de comando a sus representaciones en cadena (corta y larga).
 */
char *cmd_to_str[N_CMD][N_CMDT] = {
    {"", "No command"}, /*!< NO_CMD: Sin comando */
    {"", "Unknown"},    /*!< UNKNOWN: Comando desconocido */
    {"e", "Exit"},      /*!< EXIT: Salir del juego */
    {"n", "Next"},      /*!< NEXT: Moverse a la siguiente casilla */
    {"b", "Back"},      /*!< BACK: Moverse a la casilla anterior */
    {"t", "Take"},      /*!< TAKE: Coger un objeto */
    {"d", "Drop"}       /*!< DROP: Dejar un objeto */
};

/**
 * @brief Estructura de Comando
 * Almacena la información relacionada con un comando introducido por el usuario.
 */
struct _Command {
  CommandCode code; /*!< El código del comando. */
};

/**
 * @brief Crea un nuevo comando.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @return Un puntero al comando recién creado, o NULL si ocurre un error.
 */
Command* command_create() {
  Command* newCommand = NULL;

  newCommand = (Command*)calloc(1, sizeof(Command));
  if (newCommand == NULL) {
    return NULL;
  }

  newCommand->code = NO_CMD;

  return newCommand;
}

/**
 * @brief Destruye un comando.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param command Un puntero al comando a destruir.
 * @return OK si el comando se destruyó correctamente, o ERROR en caso contrario.
 */
Status command_destroy(Command* command) {
  if (!command) {
    return ERROR;
  }

  free(command);
  return OK;
}

/**
 * @brief Establece el código de un comando.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param command Un puntero al comando.
 * @param code El nuevo código para el comando.
 * @return OK si el código se estableció correctamente, o ERROR en caso contrario.
 */
Status command_set_code(Command* command, CommandCode code) {
  if (!command) {
    return ERROR;
  }

  command->code = code;
  return OK;
}

/**
 * @brief Obtiene el código de un comando.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param command Un puntero al comando.
 * @return El código del comando, o NO_CMD si el puntero es nulo.
 */
CommandCode command_get_code(Command* command) {
  if (!command) {
    return NO_CMD;
  }
  return command->code;
}

/**
 * @brief Obtiene la entrada del usuario y la convierte en un comando.
 * @author Rodrigo & Unai
 * @date 12-03-2024
 * @param command Un puntero al comando donde se almacenará el resultado.
 * @return OK si la entrada se procesó correctamente, o ERROR en caso contrario.
 */
Status command_get_user_input(Command* command) {
  char input[CMD_LENGHT] = "";
  char *token = NULL;
  int i = UNKNOWN - NO_CMD + 1;
  CommandCode cmd;

  if (!command) {
    return ERROR;
  }

  if (fgets(input, CMD_LENGHT, stdin)) {
    token = strtok(input, " \n");
    if (!token) {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD) {
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
        cmd = i + NO_CMD;
      } else {
        i++;
      }
    }
    return command_set_code(command, cmd);
  } else {
    return command_set_code(command, EXIT);
  }
}
