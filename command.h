/**
 * @brief Define la interfaz del intérprete de comandos
 *
 * @file command.h
 * @author Unai y Rodrigo
 * @version 1.0
 * @date 15-2-26
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 7

/**
 * @brief Tipos de formato para los comandos (corto o largo)
 */
typedef enum { CMDS, CMDL } CommandType;

/**
 * @brief Códigos de los comandos disponibles en el juego
 */
typedef enum { NO_CMD = -1, UNKNOWN, EXIT, NEXT, BACK, TAKE, DROP } CommandCode;

/**
 * @brief Estructura opaca del comando
 */
typedef struct _Command Command;

/**
 * @brief Crea un nuevo comando.
 * @author Unai y Rodrigo
 * @return Puntero al comando creado o NULL en caso de error.
 */
Command* command_create();

/**
 * @brief Libera la memoria de un comando.
 * @author Unai y Rodrigo
 * @param command Puntero al comando a destruir.
 * @return OK si se destruye con éxito, ERROR en caso contrario.
 */
Status command_destroy(Command* command);

/**
 * @brief Asigna un código a un comando.
 * @author Unai y Rodrigo
 * @param command Puntero al comando.
 * @param code Código a asignar.
 * @return OK si se asigna con éxito, ERROR en caso contrario.
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief Obtiene el código actual de un comando.
 * @author Unai y Rodrigo
 * @param command Puntero al comando.
 * @return El código del comando o NO_CMD si hay error.
 */
CommandCode command_get_code(Command* command);

/**
 * @brief Lee el comando introducido por el usuario desde teclado.
 * @author Unai y Rodrigo
 * @param command Puntero al comando donde se guardará la entrada.
 * @return OK si se lee con éxito, ERROR en caso contrario.
 */
Status command_get_user_input(Command* command);

#endif