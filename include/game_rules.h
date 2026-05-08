/**
 * @brief Define la interfaz de las reglas del juego
 *
 * @file game_rules.h
 * @author Unai.G
 * @version 1.0
 * @date 04/05/26
 * @copyright GNU Public License
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "command.h"
#include "game.h"
#include "types.h"

/**
 * @brief Actualiza el estado del juego según el comando introducido.
 * @param game Puntero al juego principal.
 * @param cmd Puntero al comando a ejecutar.
 * @return OK si se actualiza con éxito, ERROR en caso contrario.
 */
Status game_rules_update(Game *game, Command *cmd);

#endif