#include <stdio.h>
#include <stdlib.h>


// void test_new_matrix() {
// 	new_matrix(matriz2, tempcol2, fila2, columna2, operacion);
// }

typedef struct Dimensions
{
    int nro_filas;
    int nro_columnas;
}dimensions;

void main() {
	dimensions *dimensiones = (dimensions*)malloc(sizeof(dimensions));
	dimensiones->nro_filas = 10;
	dimensiones->nro_columnas = 12;

	printf("nro_filas: %d", dimensiones->nro_filas);
	printf("nro_columnas: %d", dimensiones->nro_columnas);
}