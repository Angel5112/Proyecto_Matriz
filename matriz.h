#include <stdio.h>
#include <stdlib.h>

// Estructura de los nodos de la lista de columnas

typedef struct Nodecol
{
    int valor;
    int columna;
    struct Nodecol *next;
}nodecol;

// Estructura de los nodos de la lista de filas

typedef struct Nodef
{
    int fila;
    struct Nodef *nextf;
    struct Nodecol *nextcol;
}nodef;