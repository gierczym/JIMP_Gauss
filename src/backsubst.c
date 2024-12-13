#include <stdio.h>
#include <stdlib.h>

#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
						
	int ir;
	int ic;
	double tmp;

	for( ir = mat->r-1; ir >=0; ir-- ) {
		tmp = b->data[ir][0];
		for( ic = mat->c-1; ic > ir; ic-- )
			tmp -= x->data[ir][0] / mat->data[ir][ic];
		x->data[ir][0] = tmp / mat->data[ir][ir];
	}



	return 0;
}


