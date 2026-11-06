#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libreria.h"

int main(int argc, char *argv[]) {

    int numLineas = 10; // Si el usuario no introduce un segundo parametro(argc == 3 en este caso), el numero de lineas será 10 por defecto
    if (argc < 2 || argc > 3) { // Validamos que el usuario introduzca al menos 1 o 2 parametros, sino mostramos un mensaje de error y salimos
        printf("Error: Número de argumentos incorrecto.");
        return 1;
    }
    if (argc == 3) { // Si el usuario introduce un segundo parametro(argc == 3 en este caso), entonces usamos atoi para convertir el string a un entero y lo guardamos en la variable numLineas
        numLineas = atoi(argv[2]);
    }
    if (numLineas <= 0) { // Comprobamos que el nuemro de lineas sea positivo, sino mostramos un mensaje de error y salimos
        printf("Error: El número de líneas debe ser un número entero mayor que 0.");
        return 1;
    }

    // Comparampos el primer parametro(argv[1]) con las tres funciones validas usando strcmp, si coincide con alguna de ellas llamamos a la función correspondiente
    if (strcmp(argv[1], "-head") == 0) {
        head(numLineas);
    } 
    else if (strcmp(argv[1], "-tail") == 0) {
        tail(numLineas);
    } 
    else if (strcmp(argv[1], "-longlines") == 0) {
        longlines(numLineas);
    } 
    else { // Si no es ninguna de las opciones válidas, mostramos un mensaje de error y salimos
        printf("Error:Las opciones válidas son: -head, -tail, -longlines");
        return 1;
    }

    return 0;
}