/**
 * @brief Implementa el interprete de comandos
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

#define CMD_LENGHT 30
#define SINGLE_ELEM 1

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"t", "Take"}, {"d", "Drop"}, {"a", "Attack"}, {"c", "Chat"}, {"m", "Move"}, {"i", "Inspect"} };

/**
 * @brief Command
 * Almacena toda la informacion relacionada con un comando.
 */
struct _Command
{
  CommandCode code; 
  char arg[CMD_LENGHT];
  char last_input[CMD_LENGHT]; /* New field to store the last input */
};

Command *command_create()
{
  Command *newCommand = NULL;


  newCommand = (Command *)calloc(SINGLE_ELEM, sizeof(Command));


  if (newCommand == NULL)
  {
    return NULL;
  }


  newCommand->code = NO_CMD;
  newCommand->arg[0] = '\0';
  newCommand->last_input[0] = '\0';

  return newCommand;
}

Status command_destroy(Command *command)
{

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
  if (!command)
  {
    return ERROR;
  }

  command->code = code;

  return OK;
}

CommandCode command_get_code(Command *command)
{
  if (!command)
  {
    return NO_CMD;
  }
  return command->code;
}

char* command_get_arg(Command *command)
{
  /* Comprobamos que el comando exista */
  if (!command)
  {
    return NULL;
  }
  return command->arg;
}

char* command_get_last_input(Command* command)
{
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


  if (!command)
  {
    return ERROR;
  }

  /* Leemos la entrada del usuario desde el teclado */
  if (fgets(input, CMD_LENGHT, stdin))
  {
    strncpy(command->last_input, input, CMD_LENGHT - 1); /* Store the full input */
    command->last_input[CMD_LENGHT - 1] = '\0';

    /* Separamos la primera palabra introducida */
    token = strtok(input, " \n");

    /* Si no hay texto, lo marcamos como desconocido */
    if (!token)
    {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;

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
    strncpy(command->last_input, "exit", CMD_LENGHT - 1); /* Store "exit" if EOF */
    command->last_input[CMD_LENGHT - 1] = '\0';
    return command_set_code(command, EXIT);
  }
}
/**
 * @brief Copia los datos de un comando a otro
 * @author Gemini
*/
