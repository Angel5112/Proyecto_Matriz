#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Funcion para crear los nodos de las filas

nodef *new_nodef(nodef *m, int f);

// Funcion para crear los nodos en la lista de columnas

nodecol *new_nodecol(nodecol *l, int col, int v);

// Funcion para agregar un nodo al final (columnas)

nodecol* add_endj(nodecol* link, nodecol* l);

// Funcion para crear numeros aleatorios (Usar para asignar a la matriz)

int valor_aleatorio();

// Funcion para crear una nueva matriz

nodef *new_matrix(nodef *M, nodecol *tj, int i, int j, int op);

// Funcion para imprimir una Matriz (1/7)

void Imprimir(nodef *M);

// Funcion para buscar un elemento en una Matriz (2/7)

int ObtenerElemento(int i, int j, nodef *M);

// Funcion para Asignar un elemento de una matriz en determinada posicion (3/7)

void AsignarElemento(int i, int j, int x, nodef *M);