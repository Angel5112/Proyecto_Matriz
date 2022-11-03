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
    nodef *matriz_escalar = NULL;
    nodef *matriz_resultante;
    nodef *matriz_suma = NULL;
    nodef *matriz_producto = NULL;
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

    if (fila <= 0 || columna <= 0 || fila2 <= 0 || columna2 <= 0)
        printf("Error: Filas o columnas no pueden ser menor o iguales a 0\n");
    else
    {
        srand(time(NULL));

        // Creacion de Matriz 1

        printf("\n* Como desea asignarle valores a la Matriz 1?\n");
        printf("\n1 = Automaticamente (numeros del 0 al 2)\n");
        printf("\n2 = Manualmente\n\n");
        scanf("%d", &operacion);   // Si operacion es un valor diferente de 1 o 2, se asignaran valores automaticos como prevencion
        printf("\n");

        nodef *matriz1 = NULL;
        nodecol *tempcol = NULL;

        // Llamada a funcion para la creacion de la Matriz

        matriz1 = new_matrix(matriz1, tempcol, fila, columna, operacion);

        operacion = 0;

        // Creacion de Matriz 2

        printf("\n* Como desea asignarle valores a la Matriz 2?\n");
        printf("\n1 = Automaticamente (numeros del -1 al 1)\n");
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

            operacion = 0;
            f = 0;
            col = 0;
            v = 0;
            escalar = 0;

            printf("*** Indique el tipo de operacion a realizar *** \n");
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

            if (operacion == 1)  // Imprimir una Matriz (1/7)
            {
                operacion = 0;
                printf("\n* Cual matriz desea imprimir?\n");
                printf("\n1 = Matriz 1\n");
                printf("2 = Matriz 2\n");
                printf("3 = Matriz del Producto por Escalar de la Matriz 1\n");
                printf("4 = Matriz del Producto por Escalar de la Matriz 1\n\n");
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
                else if (operacion == 3)
                {
                    printf("\nImprenta de la Matriz del Producto por Escalar de la Matriz 1\n\n");
                    if (matriz_escalar == NULL)
                    {
                        printf("\nMatriz por escalar aun no ha sido creada o es nula, creando...\n\n");
                        printf("\n* Ingrese el escalar: ");
                        scanf("%d", &escalar);
                        matriz_escalar = ProductoPorEscalar(escalar, matriz1);
                        Imprimir(matriz_escalar);
                        printf("\n\n");
                    }
                    else
                    {
                        Imprimir(matriz_escalar);
                        printf("\n\n");
                    }
                }
                else if (operacion == 4)
                {
                    printf("\nImprenta de la Matriz del Producto por Escalar de la Matriz 2\n\n");
                    if (matriz_escalar == NULL)
                    {
                        printf("\nMatriz por escalar aun no ha sido creada o es nula, creando...\n\n");
                        printf("\n* Ingrese el escalar: ");
                        scanf("%d", &escalar);
                        matriz_escalar = ProductoPorEscalar(escalar, matriz2);
                        Imprimir(matriz_escalar);
                        printf("\n\n");
                    }
                    else
                    {
                        Imprimir(matriz_escalar);
                        printf("\n\n");
                    }
                }
                else
                    printf("\nError: Numero ingresado no corresponde a accion alguna, volviendo al menu principal\n");
            }
            else if (operacion == 2) // Busqueda de elemento (2/7)
            {
                operacion = 0;
                printf("\nIngrese la fila del elemento a buscar: ");
                scanf("%d", &f);
                printf("Ingrese la columna del elemento a buscar: ");
                scanf("%d", &col);

                printf("\n* Indique en que matriz desea buscar el elemento: \n");
                printf("\n1 = Matriz 1\n");
                printf("2 = Matriz 2\n\n");
                scanf("%d", &operacion);

                if (operacion == 1)
                {
                    if (f > fila || col > columna)
                        printf("Error: Fila o Columna no puede ser mayor a la dimension original de la matriz. Volviendo a menu principal.\n");
                    else
                    {
                        printf("\nSe buscara el elemento en la Matriz 1:\n");
                        printf("El elemento es: %d\n\n", ObtenerElemento(f, col, matriz1));
                    }
                }
                else if (operacion == 2)
                {
                    if (f > fila2 || col > columna2)
                        printf("Error: Fila o Columna no puede ser mayor a la dimension original de la matriz. Volviendo a menu principal.\n");
                    else
                    {
                        printf("\nSe buscara el elemento en la Matriz 2:\n");
                        printf("El elemento es: %d\n\n", ObtenerElemento(f, col, matriz2));
                    }
                }
                else
                    printf("\nError: Numero ingresado no corresponde a accion alguna. Volviendo a menu principal\n");
            }
            else if (operacion == 3) // Asignar Elemento (3/7)
            {
                printf("\n* Indique en que matriz desea asignar el elemento: \n");
                printf("\n1 = Matriz 1\n");
                printf("2 = Matriz 2\n\n");
                scanf("%d", &operacion);
                if (operacion == 1)
                {
                    printf("\nSe asignara el elemento en la Matriz 1\n");
                    printf("\nIngrese la fila del elemento a cambiar: ");
                    scanf("%d", &f);
                    printf("Ingrese la columna del elemento a cambiar: ");
                    scanf("%d", &col);
                    printf("\nIngrese el valor a asignar en la posicion indicada anteriormente: ");
                    scanf("%d", &v);
                    if (f > fila || col > columna)
                        printf("Error: Fila o Columna no puede ser mayor a la dimension original de la matriz. Volviendo a menu principal.\n");
                    else
                    {
                        matriz1 = AsignarElemento(f, col, v, matriz1);
                        printf("\nVolviendo al menu principal\n\n");
                    }
                }
                else if (operacion == 2)
                {
                    if (f > fila2 || col > columna2)
                        printf("Error: Fila o Columna no puede ser mayor a la dimension original de la matriz. Volviendo a menu principal.\n");
                    else
                    {
                        printf("\nSe asignara el elemento en la Matriz 2\n");
                        printf("\nIngrese la fila del elemento a cambiar: ");
                        scanf("%d", &f);
                        printf("Ingrese la columna del elemento a cambiar: ");
                        scanf("%d", &col);
                        printf("\nIngrese el valor a asignar en la posicion indicada anteriormente: ");
                        scanf("%d", &v);
                        matriz2 = AsignarElemento(f, col, v, matriz2);
                        printf("\nVolviendo al menu principal\n\n");
                    }
                }
                else
                    printf("\nError: Numero ingresado no corresponde a accion alguna. Volviendo a menu principal\n");
            }
            else if (operacion == 4)    // Producto por Escalar (4/7)
            {
                printf("\n* Ingrese el escalar: ");
                scanf("%d", &escalar);

                printf("\n* Ingrese la matriz a la cual desea calcular su producto por el escalar dado: \n");
                printf("\n1 = Matriz 1\n");
                printf("\n2 = Matriz 2\n\n");
                scanf("%d", &operacion);

                if (operacion == 1)
                {
                    printf("\nSe determinara el producto por escalar de la Matriz 1\n\n");
                    matriz_escalar = ProductoPorEscalar(escalar, matriz1);
                    printf("\nMatriz resultante del producto por escalar (%d) ha sido creada. Volviendo a menu principal\n\n", escalar);
                }
                else if (operacion == 2)
                {
                    printf("\nSe determinara el producto por escalar de la Matriz 2\n\n");
                    matriz_escalar = ProductoPorEscalar(escalar, matriz2);
                    printf("\nMatriz resultante del producto por escalar (%d) ha sido creada. Volviendo a menu principal\n\n", escalar);
                }
                else
                    printf("\nError: Numero ingresado no corresponde a accion alguna. Volviendo a menu principal\n");
            }
            else if (operacion == 5)    // Sumar (5/7)
            {
                matriz_resultante = NULL;
                if (fila != fila2 || columna != columna2)
                    printf("\nError: Las matrices deben tener las mismas dimensiones.\n");
                else
                {
                    printf("\n* Indique que matrices desea sumar: \n\n");
                    printf("\n1 = Matriz 1 + Matriz 2\n");
                    printf("2 = Matriz 1 + Matriz 1\n");
                    printf("3 = Matriz 2 + Matriz 2\n");
                    scanf("%d", &operacion);

                    if (operacion == 1)
                    {
                        printf("\nSe sumara Matriz 1 + Matriz 2\n\n");
                        matriz_resultante = Suma(matriz1, matriz2);
                        Imprimir(matriz_resultante);
                        printf("\n\n");
                    }
                    else if (operacion == 2)
                    {
                        printf("\nSe sumara Matriz 1 + Matriz 1\n\n");
                        matriz_resultante = Suma(matriz1, matriz1);
                        Imprimir(matriz_resultante);
                        printf("\n\n");
                    }
                    else if (operacion == 3)
                    {
                        printf("\nSe sumara Matriz 2 + Matriz 2\n\n");
                        matriz_resultante = Suma(matriz2, matriz2);
                        Imprimir(matriz_resultante);
                        printf("\n\n");
                    }
                    else
                        printf("\nError: Numero ingresado no corresponde a accion alguna. Volviendo a menu principal\n");
                }
            }
            else if (operacion == 6)    // Transponer (6/7)
            {
                matriz_resultante = NULL;
                operacion = 0;
                printf("\n¿Que matriz desea transponer la 1 o 2?.\n");
                scanf("%d", &operacion);
                if (operacion == 1)
                {
                    matriz_resultante = Transponer(matriz1);
                    Imprimir(matriz_resultante);
                }
                else if (operacion == 2)
                {
                    matriz_resultante = Transponer(matriz2);
                    Imprimir(matriz_resultante);
                }
                else
                    printf("\nError: Numero ingresado no corresponde a accion alguna. Volviendo a menu principal\n");
                printf("\n\n");
            }
            else if (operacion == 7)    // Multiplicar (7/7)
            {
                if (columna != fila2)
                    printf("\nError: Multiplicar matrices no es posible, pues la cantidad de columnas de matriz 1 es diferente a la cantidad de filas de la matriz 2\n\n");
                else
                {
                    matriz_producto = Producto(matriz1, matriz2);
                    Imprimir(matriz_producto);
                }

            }
            else if (operacion < 1 || operacion > 7)
            {
                printf("\nHa decidido salir del programa.\n");
                validacion = 1;
            }

        }
    }
}