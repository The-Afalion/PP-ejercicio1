/**
 * @brief Define la interfaz del motor gráfico textual
 *
 * @file graphic_engine.h
 * @author Unai
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/**
 * @brief Estructura de Motor Gráfico (implementación oculta en graphic_engine.c)
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Crea una nueva instancia del motor gráfico e inicializa la pantalla
 * @author Unai
 * @return Puntero al nuevo motor gráfico o NULL en caso de error
 */
Graphic_engine* graphic_engine_create();

/**
 * @brief Destruye el motor gráfico y libera la memoria de las áreas de pantalla
 * @author Unai
 * @param ge Puntero al motor gráfico que se debe destruir
 */
void graphic_engine_destroy(Graphic_engine* ge);

/**
 * @brief Dibuja el estado actual del juego en las diferentes áreas de la interfaz
 * @author Unai
 * @param ge Puntero al motor gráfico
 * @param game Puntero a la instancia del juego
 * @param last_cmd_status Estado de ejecución del último comando (OK/ERROR)
 */
void graphic_engine_paint_game(Graphic_engine* ge, Game* game, Status last_cmd_status);

#endif