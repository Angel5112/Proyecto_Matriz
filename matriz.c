#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"

int fila, columna, fila2, columna2;

// Funcion para crear los nodos de las filas

nodef *new_nodef(nodef *m, int f)
{
    nodef *auxp;
    auxp = (nodef*)malloc(sizeof(nodef));
    auxp->fila = f;
    auxp->nextf = NULL;
    auxp->nextcol = NULL;
    return auxp;
}

// Funcion para crear los nodos en la lista de columnas

nodecol *new_nodecol(nodecol *l, int col, int v)
{
    nodecol* auxp2;
    auxp2 = (nodecol*)malloc(sizeof(nodecol));
    auxp2->columna = col;
    auxp2->valor = v;
    auxp2->next = NULL;
    return auxp2;
}

// Funcion para agregar un nodo al final (columnas)

nodecol* add_endj(nodecol* link, nodecol* l)
{
    nodecol *p;
	if (link == NULL)
		return l;
	for (p = link; p->next != NULL; p = p->next);
	p->next = l;
	return link;
}

// Funcion para crear numeros aleatorios (Usar para asignar a la matriz)

int valor_aleatorio()
{
    int valor;
    valor = rand() % 5 - 2;
    return valor;
}

// Funcion para crear una nueva matriz

nodef *new_matrix(nodef *M, nodecol *tj, int i, int j, int op)
{
    register int x, y;
    int value;
    nodef *matp, *matprev;     // matp = Auxiliar a usar para recorrer la lista de filas

    if (i == 0 || j == 0)
    {
        printf("Nota: Las dimensiones introducidas son igual a cero, se retornara Matriz = NULL\n");
        return M;
    }
    else
    {
        // Creacion y enlace de nodos del resto de la lista

        M = new_nodef(M, 0);
        matp = matprev = M;
        for (x = 0; x < i; x++)
        {
            for (y = 0; y < j; y++)
            {
                if (op == 1 || op < 1 || op > 2)
                {
                    // Llamada a funcion para generar valores aleatorios (I = [-2, 2])
                    value = valor_aleatorio();
                }
                else if (op == 2) // Operacion 2 = Asignacion manual
                {
                    printf("Valor numerico de la columna %d en la fila %d: ", y, x);
                    scanf("%d", &value);
                }

                if (value != 0)
                {
                    tj = new_nodecol(tj, y, value);
                    matp->nextcol = add_endj(matp->nextcol, tj);
                }
            }
            if (matp->nextcol == NULL)
            {
                free(matp);
                matp = matprev;
            }
            matp->nextf = new_nodef(matp, x + 1);
            matprev = matp;
            matp = matp->nextf;
        }
        printf("\n");
        return M;
    }
}

// Funcion para imprimir una Matriz (1/7)

void Imprimir(nodef *M)
{
    nodef *auxpf = M;
    nodecol *auxpc;
    while (auxpf != NULL)
    {
        auxpc = auxpf->nextcol;
        while (auxpc != NULL)
        {
            printf("\nFila: %d, Columna: %d, Valor: %d\n", auxpf->fila, auxpc->columna, auxpc->valor);
            auxpc = auxpc->next;
        }
        auxpf = auxpf->nextf;     
    }
    printf("\n");
}

// Funcion para buscar un elemento en una Matriz (2/7)

int ObtenerElemento(int i, int j, nodef *M)
{
    if (i < 0 || j < 0)
    {
        printf("\nError: fila o columna introducida es menor a 0. Elemento imposible de encontrar.\n");
        return 0;
    }
    else if (M == NULL)
    {
        printf("\nAdvertencia: La matriz es nula, por lo tanto, el elemento a buscar es 0\n");
        return 0;
    }
    else
    {
        nodef *auxp = M;
        nodecol *tempj = NULL;
        while (auxp->fila != i)
        {
            if (auxp->fila > i)
            {
                printf("\nAdvertencia: Se esta buscando un elemento en una fila no existente (Valor 0). Elemento imposible de encontrar\n\n");
                return 0;
            }
            auxp = auxp->nextf;
        }
        tempj = auxp->nextcol;
        while (tempj->columna != j)
        {
            if (tempj->next == NULL && tempj->columna < j)
            {
                printf("\nError: se esta tratando de acceder una posicion no existente (Al crear la matriz se le asigno de valor numerico un 0)\n");
                return 0;
            }
            if (tempj->columna < j)
                tempj = tempj->next;
            else if (tempj->columna > j)
            {
                printf("\nError: se esta tratando de acceder una posicion no existente (Al crear la matriz se le asigno de valor numerico un 0)\n");
                return 0;
            }
        }
       return tempj->valor;
    }
}

// Funcion para Asignar un elemento de una matriz en determinada posicion (3/7)

void AsignarElemento(int i, int j, int x, nodef *M)
{
    if (i < 0 || j < 0)
    {
        printf("\nError: fila o columna introducida es menor a 0. Elemento imposible de asignar.\n");
        return;
    }
    else if (M == NULL)
    {
        printf("\nAdvertencia: Matriz es nula, por lo atento el elemento es imposible de asignar.\n");
        return;
    }
    else
    {
        nodef *auxfp = M;
        nodecol *auxcp = NULL;
        while (auxfp->fila != i)
        {
            if (auxfp->fila > i)
            {
                printf("\nAdvertencia: Se esta buscando un elemento en una fila no existente (Valor 0). Elemento imposible de encontrar\n");
                return;
            }
            auxfp = auxfp->nextf;
        }

        auxcp = auxfp->nextcol;

        while (auxcp->columna != j)
        {
            if (auxcp->next == NULL && auxcp->columna < j)
            {        
                printf("\nError: se esta tratando de acceder una posicion no registrada (Al crear la matriz se le asigno de valor numerico un 0)\n");
                return;
            }
            if (auxcp->columna < j)
                auxcp = auxcp->next;
            else if (auxcp->columna > j)
            {
                printf("\nError: se esta tratando de acceder una posicion no registrada (Al crear la matriz se le asigno de valor numerico un 0)\n");
                return;
            }
        }
        auxcp->valor = x; // Asignar condicion cuando x = 0 (Usar free y linkear el siguiente valido)
        printf("\nEl valor %d ha sido asignado en la fila %d columna %d\n", x, i, j);
        return;
    }
}