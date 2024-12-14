#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "backsubst.h"

#define EPSILON 0.00000001

/* SCIAGAWKA
typedef struct _Matrix {
	int r;
	int c;
	double **data;
} Matrix;
*/


/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
						
	int ir;
	int ic;
	double tmp;


	for( ir = mat->r-1; ir >=0; ir-- ) { // podstawienie wsteczne, zaczynam od ostatniego wiersza
		tmp = b->data[ir][0]; // zachowuje wartosc b dla danego wiersza
		for( ic = mat->c-1; ic > ir; ic-- ){
			tmp -= x->data[ic][0] * mat->data[ir][ic];
		}
		if( fabs(mat->data[ir][ir]) < EPSILON ) {
			fprintf( stderr, "[!] backsubst: wykryto zero na diagonali\n" );
			return 1;
		}
		x->data[ir][0] = tmp / mat->data[ir][ir];
	}



	return 0;
}


