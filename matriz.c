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

nodecol* add_endj(nodecol* link, nodecol* new_link)
{
    nodecol *auxp;
	if (link == NULL)
		return new_link;
	for (auxp = link; auxp->next != NULL; auxp = auxp->next);
	auxp->next = new_link;
	return link;
}

// Funcion para crear numeros aleatorios (Usar para asignar a la matriz)

int valor_aleatorio()
{
    int valor;
    valor = rand() % 2 - 1;
    return valor;
}

// Funcion para crear una nueva matriz

nodef *new_matrix(nodef *M, nodecol *tj, int i, int j, int op)
{
    register int x, y;
    int value;
    nodef *matp, *matprev;     // matp = Auxiliar a usar para recorrer la lista de filas

    // Creacion y enlace de nodos del resto de la lista

    M = new_nodef(M, 1);
    matp = matprev = M;
    for (x = 1; x < i + 1; x++)
    {
        for (y = 1; y < j + 1; y++)
        {
            if (op == 1 || op < 1 || op > 2)
            {
                // Llamada a funcion para generar valores aleatorios (I = -1, 0, 1])
                value = valor_aleatorio();
            }
            else if (op == 2) // Operacion 2 = Asignacion manual
            {
                printf("Valor numerico de la fila %d columna %d: ", x, y);
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
    matp = M;
    if (matp->nextcol == NULL)
        {
            M = NULL;
            free(matp);
        }
    printf("\n");
    return M;

}

// Funcion para imprimir una Matriz (1/7)

void Imprimir(nodef *M)
{
    nodef *auxpf = M;
    nodecol *auxpc;
    if (M == NULL)
    {
        printf("\nAdvertencia: La matriz es nula, por lo tanto no tiene imprenta. Volviendo al menu principal\n");
        return;
    }
    printf("i  j      Valor\n\n");
    while (auxpf != NULL)
    {
        auxpc = auxpf->nextcol;
        while (auxpc != NULL)
        {
            printf("%d  %d      %d\n", auxpf->fila, auxpc->columna, auxpc->valor);
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

nodef *AsignarElemento(int i, int j, int x, nodef *M)
{
    nodef *auxfp = NULL;
    nodef *auxfp2 = NULL;
    nodecol *auxcp = NULL;
    nodecol *auxcp2 = NULL;
    nodecol *auxcprev = NULL;

    if (i <= 0 || j <= 0)
    {
        printf("\nError: Dimensiones no pueden ser menores o iguales a 0");
        return M;
    }
    else if (M == NULL)
    {
        printf("\nAdvertencia: La matriz es nula, creando espacio para asignar el elemento\n\n");
        M = new_nodef(M, i);
        auxfp = M;
        auxcp = new_nodecol(auxcp, j, x);
        auxfp->nextcol = add_endj(auxfp->nextcol, auxcp);
        return M;
    }
    else
    {
        auxfp = M;
        while (auxfp->nextf != NULL && auxfp->fila != i) // Aqui hacer lo mismo, es auxfp->next != NULL segurisimo
        {
            auxfp = auxfp->nextf;
            if (auxfp->nextf == NULL && auxfp->fila < i);
            {
                printf("\nFila no encontrada, se creara espacio para asignarla\n");
                auxfp2 = new_nodef(auxfp2, i);
                auxfp->nextf = auxfp2;

                auxcp2 = new_nodecol(auxcp2, j, x);
                auxfp2->nextcol = add_endj(auxfp2->nextcol, auxcp2);
                return M; 
            }
        }
        if (auxfp->fila > i)
        {

        }
        else
        {

            auxcp = auxfp->nextcol;
            while (auxcp->next != NULL && auxcp->columna != j)
            {
                auxcp = auxcp->next;
            }
            if (auxcp->columna < j)
            {
                printf("\nColumna no encontrada, se creara espacio para asignarla\n");
                auxcp2 = new_nodecol(auxcp2, j, x);
                auxcp->next = auxcp2;
                return M;
            }
            else if (auxcp->columna > j)
            {
                // Se necesita un prev en el anterior para crear un nodo intermedio y enlazarlos todos
                printf("\nColumna no encontrada, se creara espacio para asignarla\n");
                auxcprev = auxfp->nextcol;
                while (auxcprev->next != auxcp)
                {
                    auxcprev = auxcprev->next;
                }
                auxcprev->next = NULL;
                auxcprev->next= new_nodecol(auxcprev->next, j, x);
                auxcprev = auxcprev->next;
                auxcprev->next = auxcp;
                return M;  
            }
        }
    }
}

// Funcion para determinar la matriz resultante del producto por un escalar (4/7)

nodef *ProductoPorEscalar(int e, nodef *M)
{
    nodef *Me = NULL;
    if (e == 0)   // Condicion de e = 0, resultado sera una matriz nula
    {
        return Me;
    }
    else
    {
        Me = new_nodef(Me, M->fila); // Crear el primer nodo con la fila del 1er nodo de la Matriz original
        nodef *auxpM, *auxpMe;
        nodecol *auxpcolM, *auxpcolMe;
        auxpM = M;
        auxpMe = Me;
        while (auxpM != NULL)  // Recorriendo las filas de la matriz original
        {
            auxpcolM = auxpM->nextcol;
            while (auxpcolM != NULL)    // Recorriendo las columnas de la matriz original
            {
                auxpcolMe = new_nodecol(auxpcolMe, auxpcolM->columna, (auxpcolM->valor * e)); // Asigna los mismos valores de la matriz original en la matriz nueva, pero ya con el producto por escalar aplicado
                auxpMe->nextcol = add_endj(auxpMe->nextcol, auxpcolMe); // PROBLEMA ENCONTRADO, NUNCA SALE DE ESTA ITERACION!
                auxpcolM = auxpcolM->next;
            }
            auxpM = auxpM->nextf;           // Cambiando a la siguiente fila de la matriz original
            if (auxpM == NULL)      // Cortafuegos para evitar violacion de segmento
                break;
            else
            {
                auxpMe->nextf = new_nodef(auxpMe, auxpM->fila);     // Copiando el siguiente nodo de fila en la Matriz escalar
                auxpMe = auxpMe->nextf;  
            }
        }
        return Me;
    }
}

// Funcion para Sumar dos Matrices (5/7)

nodef *Sumar(nodef *M1, nodef *M2)
{
    int contf, contcol;
    contf = contcol = 1;
    nodef *Ms = NULL;
    nodef *auxpf, *auxpf2, *auxpfMs;
    nodecol *auxpcol, *auxpcol2, *auxpcolMs;
    if (M1 == NULL)
    {
        printf("\nLa matriz 1 es nula, por lo tanto la suma sera igual a la matriz 2\n\n");
        return M2;
    }
    else if (M2 == NULL)
    {
        printf("\nLa matriz 2 es nula, por lo tanto la suma sera igual a la matriz 1\n\n");
        return M1;
    }
    else if (M1 == NULL && M2 == NULL)
    {
        printf("\nAmbas matrices son nulas, por lo tanto, la suma sera una matriz nula\n\n");
        return Ms;
    }
    else
    {
        // Asignar los apuntadores auxiliares y crear espacio para Ms y su primer nodo
        auxpf = M1;
        auxpf2 = M2;
        auxpcol = auxpcol2 = auxpcolMs = NULL;

        if (M1->fila < M2->fila)
            Ms = new_nodef(Ms, M1->fila);
        else if (M2->fila < M1->fila)
            Ms = new_nodef(Ms, M2->fila);
        else
            Ms = new_nodef(Ms, M1->fila);
        auxpfMs = Ms;

        while (contf < fila + 1)      // NOTA: Como M1 y M2 tienen la misma dimension, se puede tomar el valor de dichas dimensiones sin temor a afectar la estructura
        {
            auxpcol = auxpf->nextcol;
            auxpcol2 = auxpf2->nextcol;

            // Condiciones de cortafuegos para evitar violacion de segmento
            if (auxpf == NULL && auxpf2 != NULL)    // auxpf ya llego al final pero auxpf2 no
            {
                auxpfMs->fila = auxpf->fila;
                while (auxpcol2 != NULL)
                    {
                        auxpcolMs = new_nodecol(auxpcolMs, auxpcol2->columna, auxpcol2->valor);
                        auxpfMs->nextcol = add_endj(auxpfMs->nextcol, auxpcolMs);
                        auxpcol2 = auxpcol2->next;
                    }

                    contf += 1;   
                    auxpfMs->nextf = new_nodef(auxpfMs, contf);
                    auxpfMs = auxpfMs->nextf;
                    auxpf2 = auxpf2->nextf;
            }
            else if (auxpf2 == NULL && auxpf != NULL)   // auxpf2 ya llego al final pero auxpf no
            {
                auxpfMs->fila = auxpf->fila;
                    while (auxpcol != NULL)
                    {
                        auxpcolMs = new_nodecol(auxpcolMs, auxpcol->columna, auxpcol->valor);
                        auxpfMs->nextcol = add_endj(auxpfMs->nextcol, auxpcolMs);
                        auxpcol = auxpcol->next;
                    }
                    contf += 1;   
                    auxpfMs->nextf = new_nodef(auxpfMs, contf);
                    auxpfMs = auxpfMs->nextf;
                    auxpf = auxpf->nextf;
            }
            else if (auxpf->fila == auxpf2->fila)    // Condicion 1: Fila con elementos en M1 y M2
            {
                while (auxpcol != NULL && auxpcol2 != NULL)
                {
                    if (auxpcol->columna == auxpcol2->columna)
                    {
                        auxpcolMs = new_nodecol(auxpcolMs, auxpcol->columna, auxpcol->valor + auxpcol2->valor);
                        auxpfMs->nextcol = add_endj(auxpfMs->nextcol, auxpcolMs);
                    }
                    else if (auxpcol->columna > auxpcol2->columna)
                    {
                        auxpcolMs = new_nodecol(auxpcolMs, auxpcol2->columna, auxpcol2->valor);
                        auxpfMs->nextcol = add_endj(auxpfMs->nextcol, auxpcolMs);
                    }
                    else if (auxpcol2->columna > auxpcol->columna)
                    {
                        auxpcolMs = new_nodecol(auxpcolMs, auxpcol->columna, auxpcol->valor);
                        auxpfMs->nextcol = add_endj(auxpfMs->nextcol, auxpcolMs);
                    }

                    if (auxpcol == NULL && auxpcol2 != NULL)
                        auxpcol2 = auxpcol2->next;
                    else if (auxpcol2 == NULL && auxpcol != NULL)
                        auxpcol = auxpcol->next;
                    else
                    {
                        auxpcol = auxpcol->next;
                        auxpcol2 = auxpcol2->next;
                    }
                }
                auxpf = auxpf->nextf;
                auxpf2 = auxpf2->nextf;
                auxpfMs->nextf = new_nodef(auxpfMs, auxpf->fila);
                auxpfMs = auxpfMs->nextf;
                contf += 1;
            }
                else if (auxpf->fila > auxpf2->fila)    // Condicion 2: Una fila de M1 no existe pero en M2 si
                {
                    auxpfMs->fila = auxpf2->fila;
                    while (auxpcol2 != NULL)
                    {
                        auxpcolMs = new_nodecol(auxpcolMs, auxpcol2->columna, auxpcol2->valor);
                        auxpfMs->nextcol = add_endj(auxpfMs->nextcol, auxpcolMs);
                        auxpcol2 = auxpcol2->next;
                    }

                    contf += 1;   
                    auxpfMs->nextf = new_nodef(auxpfMs, contf);
                    auxpfMs = auxpfMs->nextf;
                    auxpf2 = auxpf2->nextf;
                }
                else if (auxpf2->fila > auxpf->fila)  // Condicion 3: Una fila de M2 no existe pero en M1 si
                {
                    auxpfMs->fila = auxpf->fila;
                    while (auxpcol != NULL)
                    {
                        auxpcolMs = new_nodecol(auxpcolMs, auxpcol->columna, auxpcol->valor);
                        auxpfMs->nextcol = add_endj(auxpfMs->nextcol, auxpcolMs);
                        auxpcol = auxpcol->next;
                    }
                    contf += 1;   
                    auxpfMs->nextf = new_nodef(auxpfMs, contf);
                    auxpfMs = auxpfMs->nextf;
                    auxpf = auxpf->nextf;
                }
        }
        return Ms;
    }
}