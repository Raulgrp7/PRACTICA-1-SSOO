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
    int i, pos, total, inicio, nImprimir, indice;

    lineas = (char **)malloc(N * sizeof(char *)); //
    if (lineas == NULL) {
        return 1;
    }
    for (i = 0; i < N; i++) {
        lineas[i] = (char *)malloc(1024 * sizeof(char));
    }

    pos = 0; // Variable donde vamos a escribir la siguiente linea, es decir su posicion
    total = 0; //Variable del total de lineas leidas

    while (fgets(lineas[pos], 1024, stdin) != NULL) { //Hacemos un while, mientras se le introduzcan lineas a fgets, sea distinto de null por entrada estandar y almacenamos en la memoria lineas
        pos++; //Incrementamos la variable posicion
        if (pos == N) { //Si la variable posicion es igual al nuemro de lineas que quiere el usuario, se pone la variable a 0
            pos = 0; 
        }
        total++; //Incrementamos la variable total de lineas totales leidas
    }

    if (total < N) { //Si la variable total(numero de lineas leidas) es menor a N
        inicio = 0;  //Ponemos la variable inicio a 0
        nImprimir = total; //Ponemos la variable nImprimir que sea hasta el total de lineas leidas (ya que no hemos llegado hasta N)
    } else {
        inicio = pos; //Ponemos la variable inicio a donde se ha quedado apuntando la variable pos
        nImprimir = N; //Y la variable nImprimir que sea hasta N
    }

    for (i = 0; i < nImprimir; i++) { //Hacemos un bucle para imprimir desde i = 0 hasta la variable nImprimir
        indice = inicio + i; //Incrementamos la variable indice, con inicio + i, para saber que posicion de la memoria es
        if (indice >= N) { //Si la variable indice es mayor o igual a N
            indice = indice - N; // Le restamos a indice N
        }
        fputs(lineas[indice], stdout); //Imprimimos lineas[indice] por la salida estandar
    }

    for (i = 0; i < N; i++) { //Liberamos la memoria
        free(lineas[i]); 
    }
    free(lineas);        
    return 0;
}









int comparar(const void *a, const void *b) {
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;

    if (strlen(s1) < strlen(s2)) {
        return 1;
    }
    if (strlen(s1) > strlen(s2)) {
        return -1;
    }
    return 0;
}

int longlines(int N) {
    char buffer[1024];
    char *linea;
    char **lineas;
    size_t longitud_actual;
    int contador;
    size_t longitud_mas_pequena;
    int posicion_min;
    int i;

    if (N <= 0) {
        return 0;
    }

    // Inicializo variables
    contador = 0;
    longitud_mas_pequena = 0;
    posicion_min = 0;

    // Reservo el array de lineas
    lineas = malloc(N * sizeof(char *));
    if (lineas == NULL) {
        return -1;
    }

    // Leo linea a linea con fgets
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        // Quitar el \n del final si lo tiene
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }

        // Hago el malloc y strcpy a mano para copiar buffer en linea
        linea = malloc(strlen(buffer) + 1);
        if (linea == NULL) {
            return -1;
        }
        strcpy(linea, buffer);

        longitud_actual = strlen(linea);

        // Si todavia no hemos llenado el array (contador < N)
        if (contador < N) {
            lineas[contador] = linea;

            // Si es la primera linea que metemos
            if (contador == 0) {
                longitud_mas_pequena = longitud_actual;
                posicion_min = 0;
            } else {
                // Si la que acabamos de meter es mas pequeña que la minima
                if (longitud_actual < longitud_mas_pequena) {
                    longitud_mas_pequena = longitud_actual;
                    posicion_min = contador;
                }
            }
            contador = contador + 1;
        } 
        // Si ya tenemos N lineas guardadas
        else {
            // Solo nos interesa si es mas larga que la mas corta que tenemos
            if (longitud_actual > longitud_mas_pequena) {
                free(lineas[posicion_min]);
                lineas[posicion_min] = linea;

                // Busco otra vez el minimo recorriendo todo el array
                longitud_mas_pequena = strlen(lineas[0]);
                posicion_min = 0;

                for (i = 0; i < N; i = i + 1) {
                    if (strlen(lineas[i]) < longitud_mas_pequena) {
                        longitud_mas_pequena = strlen(lineas[i]);
                        posicion_min = i;
                    }
                }
            } else {
                // No cabe, la liberamos
                free(linea);
            }
        }
    }

    // Ordeno al final de mayor a menor con qsort
    qsort(lineas, contador, sizeof(char *), comparar);

    // Muestro las lineas por pantalla
    for (i = 0; i < contador; i = i + 1) {
        fputs(lineas[i], stdout);
        fputs("\n", stdout);
        free(lineas[i]);
    }

    free(lineas);
    return 0;
}