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
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
						
	int ir;
	int ic;
	double tmp;

	//
	/*============================================*/
	/* sprawdzam poprawnosc rozmiarow macierzy    */
	/*============================================*/
	//
	// 1. czy mat kwadratowa
	if( mat->r != mat->c ) {
		fprintf( stderr, "[!] backsubst: macierz A nie jest kwadratowa\n" );
		return 2;
	}
	//
	// 2. czy b oraz x maja prawidlowy rozmiar
	if( (x->r != mat->r) ||
	    (x->c != 1)      ||
            (b->r != mat->r) ||
	    (b->c != 1) )  {
		fprintf( stderr, "[!] backsubst: macierz b lub x ma nieprawidlowy rozmiar\n" );
		return 2;
	 }

	for( ir = mat->r-1; ir >=0; ir-- ) { // podstawienie wsteczne, zaczynam od ostatniego wiersza
		tmp = b->data[ir][0]; // zachowuje wartosc b dla danego wiersza
		for( ic = mat->c-1; ic > ir; ic-- ){
			if( fabs(mat->data[ir][ic]) < EPSILON ) {
				printf( "[?] wykryto element zero powyzej diagonali, [wiersz: %d] [kolumna %d]\n", ir+1, ic+1 );
				continue;
			}
			tmp -= x->data[ir][0] / mat->data[ir][ic];
		}
		if( fabs(mat->data[ir][ir]) < EPSILON ) {
			fprintf( stderr, "[!] backsubst: wyryto zero na diagonali\n" );
			return 1;
		}
		x->data[ir][0] = tmp / mat->data[ir][ir];
	}



	return 0;
}


