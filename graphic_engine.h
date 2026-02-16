/**
 * @brief Define la interfaz del motor gráfico textual
 *
 * @file graphic_engine.h
 * @author Unai y Rodrigo
 * @version 1.0
 * @date 15-02-2026
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/**
 * @brief Estructura opaca del motor gráfico
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Crea e inicializa el motor gráfico.
 * @author Unai y Rodrigo
 * @return Puntero al motor gráfico creado o NULL en caso de error.
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief Libera la memoria utilizada por el motor gráfico.
 * @author Unai y Rodrigo
 * @param ge Puntero al motor gráfico.
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief Dibuja el estado actual del juego en la terminal.
 * @author Unai y Rodrigo
 * @param ge Puntero al motor gráfico.
 * @param game Puntero al juego a representar.
 */
void graphic_engine_paint_game(Graphic_engine * ge, Game * game);

#endif