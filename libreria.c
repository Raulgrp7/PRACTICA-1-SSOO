#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>

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

int longlines(int N) {
    (void)N;
    //parecido a tail donde guardo en memoria las lineas mas largas y veo dentro de esa lista la mas corta, cada vez que lea una uso una funcion que haga algo parecido a .length pero en c y que cuando pase eso guarde el valor dentro del array y lo ordene por tamaño otra vez
    return 0;
}