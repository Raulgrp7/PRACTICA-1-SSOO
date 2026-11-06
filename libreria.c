#include "libreria.h"
#include <stdio.h>

int head(int N) {

    char (*linea)[1024];
    char *linea= malloc(N *sizeof(char));
    int i;

    for (i = 0; i < N; i++) {
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            break;  // Ya no quedan más líneas
        }
        fputs(linea, stdout);
    }
    free(buffer);

    return 0;
    
    
    }
    
    
    


int tail(int N) {
    char (*linea)[1024];
    char *linea= malloc(N *sizeof(char));
    for (int i = 0; i < N; i++) {
        if (fgets(linea, sizeof(linea), stdin) == NULL){
            break;

        }




    }

    
    return 0;
}

int longlines(int N) {
    (void)N;
    //parecido a tail donde guardo en memoria las lineas mas largas y veo dentro de esa lista la mas corta, cada vez que lea una uso una funcion que haga algo parecido a .length pero en c y que cuando pase eso guarde el valor dentro del array y lo ordene por tamaño otra vez
    return 0;
}