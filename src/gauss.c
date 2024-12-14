#include "gauss.h"
#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.00000001

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 *
**/

void norm_row(Matrix *mat, Matrix *b, int row2norm, int row2benorm, double normaliser){
	for(int i = 0; i < mat -> c; i++){
		mat -> data[row2benorm][i] += normaliser * mat -> data[row2norm][i];
	}
	
	b -> data[row2benorm][0] += normaliser * b -> data[row2norm][0];
}
void fetch_results(Matrix *mat, Matrix *b){
	for(int i = 0; i < mat -> c; i++){
		b -> data[i][0] = b -> data[i][0] / mat -> data[i][i];
	}
}
int is_matrix_singular(Matrix *mat){
	if(mat -> r != mat -> c) //sprawdza, czy macierz jest kwadratowa
		return 1;
	for(int i = 0; i < mat -> c; i++){ //sprawdza, czy na diagonali jest 0
		if(mat -> data[i][i] == 0)
			return 1;
	}
	return 0;
}

int eliminate(Matrix *mat, Matrix *b){
	//
	/*============================================*/
	/* sprawdzam poprawnosc rozmiarow macierzy    */
	/*============================================*/
	//
	// 1. czy mat kwadratowa
	if( mat->r != mat->c ) {
		fprintf( stderr, "[!] gauss.c/eliminate: macierz A nie jest kwadratowa\n" );
		return 2;
	}
	//
	// 2. czy b ma prawidlowy rozmiar
	if( (b->r != mat->r) ||
	    (b->c != 1) )  {
		fprintf( stderr, "[!] gauss.c/eliminate: macierz b ma nieprawidlowy rozmiar\n" );
		return 2;
	 }
	//
	/*=========================================*/
	/* przeksztalcam macierz na dolnotrojkatna */
	/*=========================================*/
	//
	int ir;
	int ir_aux;
	int ir_swap;
	int ic;
	double val_max;
	double tmp;

	//
	// najpierw sortuje wiersze
	for( ir = 0; ir < mat->r; ir++ ) {
		//
		// szukam wiersza z elementem o najwiekszym module w kolumnie ir-tej
		val_max = fabs( mat->data[ir][ir] );
		ir_swap = ir;
		for( ir_aux = ir+1; ir_aux < mat->r; ir_aux++ )
			if( fabs(mat->data[ir_aux][ir]) > val_max ) {
				val_max = fabs(mat->data[ir_aux][ir]);
				ir_swap = ir_aux;
			}
		//
		if( val_max < EPSILON ) {
			fprintf( stderr, "[!] gauss.c/eliminate: zero na diagonali, same elementy zerowe w kolumnie %d-tej ponizej badanego wiersza\n", ir+1 );
			return 1;
		}	
		//
		// jesli znalazlem wiersz o wiekszym elemencie w badanej kolumnie to zamieniam wiersze
		if( ir_swap != ir ) {
			for( ic = 0; ic < mat->c; ic++ ) {
				tmp = mat->data[ir][ic];
				mat->data[ir][ic] = mat->data[ir_swap][ic];
				mat->data[ir_swap][ic] = tmp;
			}
			tmp = b->data[ir][0];
			b->data[ir][0] = b->data[ir_swap][0];
			b->data[ir_swap][0] = tmp;
		}
			
	}
	//
	// teraz robie macierz dolnotrojkatna
	double fac;
	for( ir = 0; ir < mat->r; ir++ ) {
		for( ir_aux = ir+1; ir_aux < mat->r; ir_aux++ ) {
			fac = mat->data[ir_aux][ir] / mat->data[ir][ir];
			for( ic = 0; ic < mat->c; ic ++ )
				mat->data[ir_aux][ic] -= fac * mat->data[ir][ic];
			b->data[ir_aux][0] -= fac * b->data[ir][0];
		}
	}

	return 0;
}


