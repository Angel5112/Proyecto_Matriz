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

nodef *AsignarElemento(int i, int j, int x, nodef *M);

// Funcion para determinar la matriz resultante del producto por un escalar (4/7)

nodef *ProductoPorEscalar(int e, nodef *M);

// Funcion para determinar la matriz resultante de la suma de dos matrices dadas (5/7)

nodef *Suma(nodef *M1, nodef *M2);

// Funcion para determinar la matriz transpuesta (6/7)

nodef *Transponer(nodef *M);

// Funcion para determinar el producto de dos matrices (7/7)

nodef *Producto(nodef *M1, nodef *M2);