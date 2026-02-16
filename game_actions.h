/**
 * @brief Define la interfaz de actualización del juego (acciones)
 *
 * @file game_actions.h
 * @author Unai
 * @version 1.0
 * @date 15-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"

/**
 * @brief Actualiza el estado del juego según el comando introducido.
 * @param game Puntero al juego principal.
 * @param cmd Puntero al comando a ejecutar.
 * @return OK si se actualiza con éxito, ERROR en caso contrario.
 */
Status game_actions_update(Game *game, Command *cmd);

#endif