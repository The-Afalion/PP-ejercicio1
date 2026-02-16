/**
 * @brief Implementa el intérprete de comandos
 *
 * @file command.c
 * @author Unai
 * @version 1.0
 * @date 15-02-2026
 * @copyright GNU Public License
 */

#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGHT 30
#define SINGLE_ELEM 1

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"n", "Next"}, {"b", "Back"}, {"t", "Take"}, {"d", "Drop"}};

/**
 * @brief Command
 * Almacena toda la información relacionada con un comando.
 */
struct _Command
{
  CommandCode code; /*!< Código del comando */
};

Command *command_create()
{
  Command *newCommand = NULL;

  /* Reservamos memoria para el comando */
  newCommand = (Command *)calloc(SINGLE_ELEM, sizeof(Command));

  /* Comprobamos si hubo error en la reserva */
  if (newCommand == NULL)
  {
    return NULL;
  }

  /* Inicializamos el comando por defecto (vacío) */
  newCommand->code = NO_CMD;

  return newCommand;
}

Status command_destroy(Command *command)
{
  /* Comprobamos que el comando exista */
  if (!command)
  {
    return ERROR;
  }

  /* Liberamos la memoria */
  free(command);
  command = NULL;
  return OK;
}

Status command_set_code(Command *command, CommandCode code)
{
  /* Comprobamos que el comando exista */
  if (!command)
  {
    return ERROR;
  }

  /* Asignamos el nuevo código */
  command->code = code;

  return OK;
}

CommandCode command_get_code(Command *command)
{
  /* Comprobamos que el comando exista */
  if (!command)
  {
    return NO_CMD;
  }
  return command->code;
}

Status command_get_user_input(Command *command)
{
  char input[CMD_LENGHT] = "", *token = NULL;
  int i = UNKNOWN - NO_CMD + 1; /* Calculamos el índice para empezar a buscar */
  CommandCode cmd;

  /* Comprobamos que el comando exista */
  if (!command)
  {
    return ERROR;
  }

  /* Leemos la entrada del usuario desde el teclado */
  if (fgets(input, CMD_LENGHT, stdin))
  {

    /* Separamos la primera palabra introducida */
    token = strtok(input, " \n");

    /* Si no hay texto, lo marcamos como desconocido */
    if (!token)
    {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;

    /* Buscamos si la palabra coincide con algún comando corto o largo */
    while (cmd == UNKNOWN && i < N_CMD)
    {
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL]))
      {
        cmd = i + NO_CMD;
      }
      else
      {
        i++;
      }
    }

    /* Asignamos el código encontrado */
    return command_set_code(command, cmd);
  }
  else
  {
    /* Si falla la lectura, forzamos la salida del juego */
    return command_set_code(command, EXIT);
  }
}