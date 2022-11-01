#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

// Declaracion de variables globales a utilizar (Dimensiones de las matrices)

int fila, columna, fila2, columna2;

int main()
{
    // Declaracion de variables a utilizar

    int f, col, v, escalar, validacion, operacion;
    validacion = 0; // Variable a usar como key del ciclo del menu de procedimientos y operaciones

    // Solicitud de las dimensiones de la matriz

    printf("****** Ingrese la cantidad de filas de la 1era matriz ******\n");
    scanf("%d", &fila);
    printf("\n");
    printf("****** Ingrese la cantidad de columnas de la 1era matriz ******\n");
    scanf("%d", &columna);
    printf("\n");
    printf("****** Ingrese la cantidad de filas de la 2nda matriz ******\n");
    scanf("%d", &fila2);
    printf("\n");
    printf("****** Ingrese la cantidad de columnas de la 2nda matriz ******\n");
    scanf("%d", &columna2);
    printf("\n");

    if (fila < 0 || columna < 0 || fila2 < 0 || columna2 < 0)
        printf("Error: Filas o columnas no pueden ser menor a 0\n");
    else
    {
        while (!validacion)
        {
            // Antes de esto se deben crear las matrices
            // Menu de operaciones a utilizar en el programa

            printf("\n*** Indique el tipo de operacion a realizar *** \n");
            printf("\n1 = Imprimir Matriz\n");
            printf("\n2 = Buscar elemento dentro de una Matriz\n");
            printf("\n3 = Asignar elemento en una posicion dada de una Matriz\n");
            printf("\n4 = Multiplicar una Matriz por un escalar\n");
            printf("\n5 = Sumar Matrices\n");
            printf("\n6 = Transponer una Matriz\n");
            printf("\n7 = Multiplicar Matrices\n");
            printf("\nCualquier otro numero = Salir del Programa\n\n");
            scanf("%d", &operacion);

            // Condiciones del menu

            if (operacion < 1 || operacion > 7)
            {
                printf("\nHa decidido salir del programa.\n");
                validacion = 1;
            }
        }
    }
}