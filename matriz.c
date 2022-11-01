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