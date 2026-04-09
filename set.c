/**
 * @brief Implementa el módulo de conjunto (set)
 *
 * @file set.c
 * @author Unai
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDS 100 /* Define un tamaño máximo para el conjunto */

/**
 * @brief Estructura de Conjunto (Set)
 * Almacena una lista de identificadores y la cantidad actual.
 */
struct Set {
    Id ids[MAX_IDS]; /*!< Array interno de identificadores */
    int n_ids;       /*!< Número actual de identificadores almacenados */
};

/**
 * @brief Crea un nuevo conjunto vacío
 * @author Unai
 * @return Puntero al nuevo conjunto o NULL si hay error
 */
Set *set_create() {
    Set *s = NULL;
    int i;

    /* Reservamos memoria para la estructura Set */
    s = (Set *)malloc(sizeof(Set));
    if (s == NULL) {
        return NULL;
    }

    /* Un nuevo conjunto se inicializa vacío */
    s->n_ids = 0;
    
    /* Rellenamos todo el array de IDs con NO_ID por seguridad */
    for (i = 0; i < MAX_IDS; i++) {
        s->ids[i] = NO_ID;
    }

    return s;
}

/**
 * @brief Destruye un conjunto y libera su memoria
 * @author Unai
 * @param s Puntero al conjunto a destruir
 * @return OK si se destruye con éxito, ERROR en caso contrario
 */
Status set_destroy(Set *s) {
    if (s == NULL) {
        return ERROR; /* Control de error para puntero NULL */
    }
    
    /* Liberamos la memoria de la estructura principal */
    free(s);
    return OK;
}

/**
 * @brief Añade un nuevo Id al conjunto evitando duplicados
 * @author Unai
 * @param s Puntero al conjunto
 * @param id Identificador a añadir
 * @return OK si se añade con éxito, ERROR si ya existe o el conjunto está lleno
 */
Status set_add(Set *s, Id id) {
    if (s == NULL || id == NO_ID || s->n_ids >= MAX_IDS) {
        return ERROR;
    }

    /* PREVENCIÓN DE DUPLICADOS: Si set_find devuelve OK, el ID ya está guardado */
    if (set_find(s, id) == OK) {
        return ERROR; 
    }

    /* ASIGNACIÓN: Lo guardamos en la primera posición libre y aumentamos el contador */
    s->ids[s->n_ids] = id;
    s->n_ids++;

    return OK;
}

/**
 * @brief Elimina un Id específico del conjunto y reordena el array
 * @author Unai
 * @param s Puntero al conjunto
 * @param id Identificador a eliminar
 * @return OK si se elimina, ERROR si no existe
 */
Status set_del(Set *s, Id id) {
    int i, j;

    if (s == NULL || id == NO_ID) {
        return ERROR;
    }

    for (i = 0; i < s->n_ids; i++) {
        if (s->ids[i] == id) {
            /* REORDENACIÓN: Desplazamos los elementos hacia la izquierda para tapar el hueco */
            for (j = i; j < s->n_ids - 1; j++) {
                s->ids[j] = s->ids[j + 1];
            }
            
            /* Limpiamos la última posición que queda duplicada y restamos 1 al total */
            s->ids[s->n_ids - 1] = NO_ID;
            s->n_ids--;
            
            return OK;
        }
    }

    return ERROR; /* Retorna error si termina el bucle sin encontrarlo */
}

/**
 * @brief Búsqueda secuencial para comprobar si un Id existe en el conjunto
 * @author Unai
 * @param s Puntero al conjunto
 * @param id Identificador a buscar
 * @return OK si se encuentra, ERROR si no existe
 */
Status set_find(Set *s, Id id) {
    int i;
    
    if (s == NULL || id == NO_ID) {
        return ERROR;
    }

    /* Búsqueda en los elementos actualmente válidos del array */
    for (i = 0; i < s->n_ids; i++) {
        if (s->ids[i] == id) {
            return OK; /* Encontrado */
        }
    }
    
    return ERROR; /* No encontrado */
}

/**
 * @brief Imprime el conjunto por salida estándar
 * @author Unai
 * @param s Puntero al conjunto
 */
void set_print(Set *s) {
    int i;
    
    if (s == NULL) {
        return;
    }
    
    for (i = 0; i < s->n_ids; i++) {
        printf(" %ld", s->ids[i]);
    }
}

/**
 * @brief Devuelve el Id almacenado en un índice concreto
 * @author Unai
 * @param s Puntero al conjunto
 * @param indx Índice dentro del array
 * @return El Id almacenado o NO_ID si hay un error
 */
Id set_get_id(Set *s, int indx) {
    if (s == NULL || indx < 0 || indx >= s->n_ids) {
        return NO_ID;
    }
    
    return s->ids[indx];
}

/**
 * @brief Devuelve la cantidad actual de IDs en el conjunto
 * @author Unai
 * @param s Puntero al conjunto
 * @return El número de IDs (0 si el conjunto es NULL)
 */
int set_get_numberid(Set *s) {
    if (s == NULL) {
        return 0; /* Un conjunto NULL se interpreta con 0 elementos */
    }
    
    return s->n_ids;
}

/**
 * @brief Devuelve el puntero al array interno de IDs
 * @author Unai
 * @param s Puntero al conjunto
 * @return Puntero al array o NULL si está vacío
 */
Id* set_get_ids(Set *s) {
    if (s == NULL || s->n_ids == 0) {
        return NULL; /* Devuelve NULL si no hay elementos */
    }

    /* IMPORTANTE: Devuelve el puntero interno del Set. 
       El módulo que lo llame NO debe hacer un free() de este valor. */
    return s->ids;
}