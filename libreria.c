#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int head(int N) {
    char *linea;
    int i;
    linea = (char *)malloc(1024 * sizeof(char));

    for (i = 0; i < N; i++) {
        if (fgets(linea, 1024, stdin) == NULL) {
            break;  // Ya no quedan más líneas
        }
        fputs(linea, stdout);
    }
    free(linea);
    return 0;
    }
    
    
    


int tail(int N) {
    char **lineas;
    int i, pos, total, inicio, a_imprimir, indice;
    lineas = (char **)malloc(N * sizeof(char *));
    if (lineas == NULL) {
        return 1;
    }
    for (i = 0; i < N; i++) {
        lineas[i] = (char *)malloc(1024 * sizeof(char));
    }

    pos = 0;
    total = 0;

    while (fgets(lineas[pos], 1024, stdin) != NULL) {
        pos++;
        if (pos == N) {
            pos = 0; 
        }
        total++;
    }

    if (total < N) {
        inicio = 0;
        a_imprimir = total;
    } else {
        inicio = pos;
        a_imprimir = N;
    }

    for (i = 0; i < a_imprimir; i++) {
        indice = inicio + i;
        if (indice >= N) {
            indice = indice - N; // Si nos pasamos, damos la vuelta al 0
        }
        fputs(lineas[indice], stdout);
    }

    for (i = 0; i < N; i++) {
        free(lineas[i]); 
    }
    free(lineas);        
    return 0;
}









static char *duplicar_cadena(const char *src) {
    size_t len = strlen(src);
    char *dest = malloc(len + 1);
    if (dest) {
        memcpy(dest, src, len + 1);
    }
    return dest;
}

/* Comparador para ordenar de mayor a menor longitud con qsort */
int comparar_longitud_desc(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len2 > len1) return 1;
    if (len2 < len1) return -1;
    return 0;
}

int longlines(int N) {
    // Declaración de variables locales al principio
    char buffer[1024];
    char *linea;
    char **lineas;
    size_t longitud_actual;
    int contador = 0;
    size_t longitud_mas_pequena = 0;
    int posicion_min = 0;
    int i;

    if (N <= 0) return 0;

    // un array que guarda en cada posición las lineas con comprobación de memoria
    lineas = malloc((size_t)N * sizeof *lineas);
    if (!lineas) {
        return -1;
    }

    // mientras se pueda leer una linea (C estándar puro usando fgets)
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // eliminar el salto de línea final (\n o \r\n) para no contarlo
        longitud_actual = strlen(buffer);
        if (longitud_actual > 0 && buffer[longitud_actual - 1] == '\n') {
            buffer[longitud_actual - 1] = '\0';
            longitud_actual--;
        }
        if (longitud_actual > 0 && buffer[longitud_actual - 1] == '\r') {
            buffer[longitud_actual - 1] = '\0';
            longitud_actual--;
        }

        // guardo el texto en la variable linea con comprobación de memoria
        linea = duplicar_cadena(buffer);
        if (!linea) {
            for (i = 0; i < contador; i++) free(lineas[i]);
            free(lineas);
            return -1;
        }

        // si el contador es menor que N
        if (contador < N) {
            // poner la linea en el array en la posición contador
            lineas[contador] = linea;

            // si no es la primera línea (contador != 0), comparamos
            if (contador != 0) {
                // comparar longitud mas pequeña con longitud actual
                //     si longitud actual es mas pequeña
                if (longitud_actual < longitud_mas_pequena) {
                    // actualizar longitud mas pequeña a longitud actual
                    longitud_mas_pequena = longitud_actual;
                    // actualizar posición min al valor de la linea del contador
                    posicion_min = contador;
                }
            }
            // si es la primera línea (contador == 0): inicializamos mínimo
            else {
                // longitud mas pequeña es longitud actual
                longitud_mas_pequena = longitud_actual;
                // posición min es la primera posición del array
                posicion_min = 0;
            }
            // incrementar en uno el contador
            contador++;
        }
        // si no (el contador ya ha alcanzado al valor N):
        else {
            // si la longitud actual es mayor que longitud mas pequeña
            if (longitud_actual > longitud_mas_pequena) {
                // con la posición de posición min se cambia el valor por la linea actual
                free(lineas[posicion_min]);
                lineas[posicion_min] = linea;

                // longitud mas p es igual al strlen de lineas[0]
                longitud_mas_pequena = strlen(lineas[0]);
                posicion_min = 0;

                // se recorre de 0 a N el array de líneas para recalcular el nuevo mínimo
                for (i = 0; i < N; i++) {
                    if (strlen(lineas[i]) < longitud_mas_pequena) {
                        longitud_mas_pequena = strlen(lineas[i]);
                        posicion_min = i;
                    }
                }
            } else {
                // si la línea no entra al array, liberamos para no fugar memoria
                free(linea);
            }
        }
    }

    // qsort(lineas, N, sizeof *lineas, comparar_longitud_desc);
    qsort(lineas, (size_t)contador, sizeof *lineas, comparar_longitud_desc);

    // hacer un fputs de lineas
    for (i = 0; i < contador; i++) {
        fputs(lineas[i], stdout);
        fputc('\n', stdout);
        free(lineas[i]);
    }

    free(lineas);
    return 0;
}