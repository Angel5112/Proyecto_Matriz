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
                return 0;
            }
            auxp = auxp->nextf;
        }
        if (auxp->nextcol == NULL)
            return 0;
        tempj = auxp->nextcol;
        while (tempj->columna != j)
        {
            if (tempj->next == NULL && tempj->columna < j)
            {
                return 0;
            }
            if (tempj->columna < j)
                tempj = tempj->next;
            else if (tempj->columna > j)
            {
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
    nodef *auxfprev = NULL;
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
        if (x != 0)
        {
            auxfp->nextcol = add_endj(auxfp->nextcol, auxcp);
            return M;
        }
        else
        {
            free(auxcp);
            M = NULL;
            return M;
        }
    }
    else
    {
        auxfp = M;
        while (auxfp->nextf != NULL && auxfp->fila != i) // Aqui hacer lo mismo, es auxfp->next != NULL segurisimo
        {
            auxfp = auxfp->nextf;

            if (auxfp->fila > i)
            {
                printf("\nFila no encontrada (Valor intermedio), se creara espacio para asignarla\n");

                auxfprev = M;
                while (auxfprev->nextf != auxfp)
                {
                    auxfprev = auxfprev->nextf;
                }
                auxfprev->nextf = NULL;               
                auxfp2 = new_nodef(auxfp2, i);

                auxcp2 = new_nodecol(auxcp2, j, x);
                auxfp2->nextcol = add_endj(auxfp2->nextcol, auxcp2);

                auxfprev->nextf = auxfp2;
                auxfp2->nextf = auxfp;
                return M; 
            }

            if (auxfp->nextf == NULL && auxfp->fila < i)
            {
                printf("\nFila no encontrada, se creara espacio para asignarla\n");
                auxfp2 = new_nodef(auxfp2, i);

                auxcp2 = new_nodecol(auxcp2, j, x);
                auxfp2->nextcol = add_endj(auxfp2->nextcol, auxcp2);
                auxfp->nextf = auxfp2;
                return M; 
            }
        }

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
    return NULL;
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

// Funcion para determinar la matriz resultante de la suma de dos matrices dadas (5/7)

nodef *Suma(nodef *M1, nodef *M2) {
    nodef *M3; // Matriz resultante
    nodef *auxpM1, *auxpM2, *auxpM3, *auxpPrevM3; // Punteros Aux.
    nodecol *newCol = NULL;

    auxpM1 = M1;
    auxpM2 = M2;
    int m = 0, n = 0, res = 0;  // Valores a sumar

    M3 = new_nodef(M3, 1); // Agregar Nodo Fila inicial a Matriz resultante
    auxpM3 = auxpPrevM3 = M3;

    for (int i=1; i<=fila; i++) {

        for (int j=1; j<=columna; j++) {

            m = ObtenerElemento(i, j, auxpM1);
            n = ObtenerElemento(i, j, auxpM2);

            res = m + n;

            if (res != 0) {
                newCol = new_nodecol(newCol, j, res);
                auxpM3->nextcol = add_endj(auxpM3->nextcol, newCol);
            }
        }

        if (auxpM3->nextcol == NULL) { // Liberar espacio de fila de solo 0 ceros
            free(auxpM3);
            auxpM3 = auxpPrevM3;
        }
        auxpM3->nextf = new_nodef(auxpM3, i + 1); // Agregar Siguiente fila a Matriz resultante
        auxpPrevM3 = auxpM3;
        auxpM3 = auxpM3->nextf;
    }

    return M3;
}

// Funcion para determinar la matriz transpuesta (6/7)

nodef *Transponer(nodef *M) {

    int value, auxFila, auxColumna;
    nodef *MR;  // Matriz resultante
    nodef *auxpM, *auxpMR, *auxpPrevMR; // Punteros Aux.
    nodecol *newCol = NULL;

    auxpM = M;

    MR = new_nodef(MR, 1); // Agregar Nodo Fila inicial a Matriz resultante
    auxpMR = auxpPrevMR = MR;

    auxFila = fila;
    auxColumna = columna;
    if (fila != columna) {
        value = auxColumna;
        auxColumna = auxFila;
        auxFila = value;
        value = 0;
    }

    for (int i=1; i<=auxFila; i++) {

        for (int j=1; j<=auxColumna; j++) {

            if (fila > columna && i > columna)
                value = ObtenerElemento(i, j, auxpM);
            else
                value = ObtenerElemento(j, i, auxpM);

            if (value != 0) {
                newCol = new_nodecol(newCol, j, value);
                auxpMR->nextcol = add_endj(auxpMR->nextcol, newCol);
            }
        }

        if (auxpMR->nextcol == NULL) { // Liberar espacio de fila de solo 0 ceros
            free(auxpMR);
            auxpMR = auxpPrevMR;
        }
        auxpMR->nextf = new_nodef(auxpMR, i + 1); // Agregar Siguiente fila a Matriz resultante
        auxpPrevMR = auxpMR;
        auxpMR = auxpMR->nextf;
    }

    return MR;
}

// Funcion para determinar el producto de dos matrices (7/7)

nodef *Producto(nodef *M1, nodef *M2) {
    //
}