/**
 * @brief Define la interfaz de la pantalla
 *
 * @file libscreen.h
 * @author Profesores PPROG
 * @version 3.5
 * @date 26-01-2024
 * @copyright GNU Public License
 */

#ifndef LIBSCREEN_H
#define LIBSCREEN_H

typedef struct _Area Area;

/**
 * @brief Crea una nueva pantalla
 * @author Profesores PPROG
 *
 * Esta función debe ser llamada al principio del programa,
 * para que la pantalla completa sea asignada antes de empezar a definir áreas.
 * @param rows el número de filas que tendrá la pantalla completa
 * @param columns el número de columnas que tendrá la pantalla completa
 */
void screen_init(int rows, int columns);

/**
 * @brief Destruye un área de pantalla nueva
 * @author Profesores PPROG
 *
 * Como libera la pantalla, debe ser llamada al final del programa,
 * una vez que las áreas creadas han sido liberadas.
 */
void screen_destroy();

/**
 * @brief Pinta en la terminal la composición actual de la pantalla
 * @author Profesores PPROG
 *
 * Esta función debe ser llamada cuando se quieran mostrar
 * algunas actualizaciones en la pantalla.
 */
void screen_paint();

/**
 * @brief Crea una nueva área dentro de una pantalla
 * @author Profesores PPROG
 *
 * screen_area_init asigna memoria para una nueva área
 * e inicializa sus miembros.
 * @param x la coordenada x de la esquina superior izquierda del área
 * @param y la coordenada y de la esquina superior izquierda del área
 * @param width el ancho del área
 * @param height la altura del área
 * @return una nueva área, inicializada
 */
Area *screen_area_init(int x, int y, int width, int height);

/**
 * @brief Destruye un área de pantalla nueva
 * @author Profesores PPROG
 *
 * Esta función debe ser llamada una vez que el área ya no es necesaria,
 * antes de terminar el programa.
 * @param area el área a ser liberada
 */
void screen_area_destroy(Area *area);

/**
 * @brief Limpia un área, borrando todo su contenido
 * @author Profesores PPROG
 *
 * Esta función debe ser llamada para borrar toda la información en un área,
 * antes de introducir un nuevo estado de la misma.
 * @param area el área a ser limpiada
 */
void screen_area_clear(Area *area);

/**
 * @brief Reinicia el cursor de un área
 * @author Profesores PPROG
 *
 * Esta función reinicia el cursor a la esquina superior izquierda del área.
 * @param area el área involucrada
 */
void screen_area_reset_cursor(Area *area);

/**
 * @brief Introduce alguna información dentro de un área
 * @author Profesores PPROG
 *
 * Esta función establece la cadena que se mostrará en un área.
 * Cada cadena introducida será una línea en el área especificada.
 * @param area el área a ser modificada
 * @param str una cadena que contiene la información a ser incluida en un área particular
 */
void screen_area_puts(Area *area, char *str);

#endif