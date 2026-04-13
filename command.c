#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LENGHT 30
#define SINGLE_ELEM 1

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "exit"}, {"t", "Take"}, {"d", "drop"}, {"a", "attack"}, {"c", "chat"}, {"m", "move"}, {"i", "inspect"}};

struct _Command
{
  CommandCode code;            /* Codigo del comando enumerado */
  char arg[CMD_LENGHT];        /* Argumento del comando introducido */
  char last_input[CMD_LENGHT]; /* Almacena la ultima entrada completa del usuario */
};

Command *command_create()
{
  Command *newCommand = NULL;

  newCommand = (Command *)calloc(SINGLE_ELEM, sizeof(Command));

  /* Comprueba si falla la reserva de memoria */
  if (newCommand == NULL)
  {
    return NULL;
  }

  /* Inicializacion de los campos por defecto */
  newCommand->code = NO_CMD;
  newCommand->arg[0] = '\0';
  newCommand->last_input[0] = '\0';

  return newCommand;
}

Status command_destroy(Command *command)
{
  /* Comprueba que el comando no sea NULL antes de liberar */
  if (!command)
  {
    return ERROR;
  }

  free(command);
  command = NULL;
  return OK;
}

Status command_set_code(Command *command, CommandCode code)
{
  /* Comprueba la validez del puntero */
  if (!command)
  {
    return ERROR;
  }

  command->code = code;
  return OK;
}

CommandCode command_get_code(Command *command)
{
  /* Comprueba la validez del puntero y devuelve el codigo */
  if (!command)
  {
    return NO_CMD;
  }
  return command->code;
}

char *command_get_arg(Command *command)
{
  /* Comprueba la validez del puntero y devuelve el argumento */
  if (!command)
  {
    return NULL;
  }
  return command->arg;
}

char *command_get_last_input(Command *command)
{
  /* Comprueba la validez del puntero y devuelve la entrada cruda */
  if (!command)
  {
    return NULL;
  }
  return command->last_input;
}

Status command_get_user_input(Command *command)
{
  char input[CMD_LENGHT] = "", *token = NULL, *arg = NULL;
  int i = UNKNOWN - NO_CMD + 1;
  CommandCode cmd;

  /* Comprueba la validez del comando */
  if (!command)
  {
    return ERROR;
  }

  /* Lee la entrada del usuario desde el flujo estándar */
  if (fgets(input, CMD_LENGHT, stdin))
  {
    strncpy(command->last_input, input, CMD_LENGHT - 1);
    command->last_input[CMD_LENGHT - 1] = '\0';

    /* Extrae el primer token correspondiente al comando */
    token = strtok(input, " \n");

    /* Si la entrada esta vacia, asigna codigo desconocido */
    if (!token)
    {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;

    /* Busca coincidencia del token con los comandos validos */
    while (cmd == UNKNOWN && i < N_CMD)
    {
      if (!strcmp(token, cmd_to_str[i][CMDS]) || !strcmp(token, cmd_to_str[i][CMDL]))
      {
        cmd = i + NO_CMD;
      }
      else
      {
        i++;
      }
    }

    /* Extrae el segundo token correspondiente al argumento */
    arg = strtok(NULL, " \n");
    if (arg)
    {
      strncpy(command->arg, arg, CMD_LENGHT - 1);
      command->arg[CMD_LENGHT - 1] = '\0';
    }
    else
    {
      command->arg[0] = '\0';
    }

    return command_set_code(command, cmd);
  }
  else
  {
    /* Asigna comando de salida en caso de fin de archivo (EOF) */
    strncpy(command->last_input, "exit", CMD_LENGHT - 1);
    command->last_input[CMD_LENGHT - 1] = '\0';
    return command_set_code(command, EXIT);
  }
}