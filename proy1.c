#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
        srand(time(NULL));

        // Creacion de Matriz 1

        printf("\nComo desea asignarle valores a la Matriz 1?\n");
        printf("\n1 = Automaticamente (numeros del -2 al 2)\n");
        printf("\n2 = Manualmente\n\n");
        scanf("%d", &operacion);   // Si operacion es un valor diferente de 1 o 2, se asignaran valores automaticos como prevencion
        printf("\n");

        nodef *matriz1 = NULL;
        nodecol *tempcol = NULL;

        // Llamada a funcion para la creacion de la Matriz

        matriz1 = new_matrix(matriz1, tempcol, fila, columna, operacion);

        operacion = 0;

        // Creacion de Matriz 2

        printf("\nComo desea asignarle valores a la Matriz 2?\n");
        printf("\n1 = Automaticamente (numeros del -2 al 2)\n");
        printf("\n2 = Manualmente\n\n");
        scanf("%d", &operacion);   // Si operacion es un valor diferente de 1 o 2, se asignaran valores automaticos como prevencion
        printf("\n");

        nodef *matriz2 = NULL;
        nodecol *tempcol2 = NULL;

        // Llamada a funcion para la creacion de la Matriz 2

        matriz2 = new_matrix(matriz2, tempcol2, fila2, columna2, operacion);

        operacion = 0;

        while (!validacion)
        {
            // Antes de esto se deben crear las matrices
            // Menu de operaciones a utilizar en el programa

            printf("\n*** Indique el tipo de operacion a realizar *** \n");
            printf("\n1 = Imprimir Matriz\n");
            printf("2 = Buscar elemento dentro de una Matriz\n");
            printf("3 = Asignar elemento en una posicion dada de una Matriz\n");
            printf("4 = Multiplicar una Matriz por un escalar\n");
            printf("5 = Sumar Matrices\n");
            printf("6 = Transponer una Matriz\n");
            printf("7 = Multiplicar Matrices\n");
            printf("\nCualquier otro numero = Salir del Programa\n\n");
            scanf("%d", &operacion);

            // Condiciones del menu

            if (operacion == 1)  // Imprimir una Matriz
            {
                operacion = 0;
                printf("\nCual matriz desea imprimir?\n");
                printf("\n1 = Matriz 1\n");
                printf("2 = Matriz 2\n\n");
                scanf("%d", &operacion);

                // Condiciones de operacion en la seccion de Imprimir
                if (operacion == 1)
                {   
                    printf("\nImprenta de la Matriz 1: \n\n");
                    Imprimir(matriz1);
                }
                else if (operacion == 2)
                {
                    printf("\nImprenta de la Matriz 2: \n\n");
                    Imprimir(matriz2);
                }
                else
                    printf("\nError: Numero ingresado no corresponde a accion alguna, volviendo al menu principal\n");
            }
            else if (operacion < 1 || operacion > 7)
            {
                printf("\nHa decidido salir del programa.\n");
                validacion = 1;
            }
        }
    }
}