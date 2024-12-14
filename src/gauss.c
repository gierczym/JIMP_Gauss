#include "gauss.h"
#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>
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
	double dodajnik = 0;
	if(is_matrix_singular(mat) == 1)
		return 1;
	for(int i = 0; i < mat -> c; i++){ // zamienia macierz na dolnotrójkątną
		for(int j = i+1; j < mat -> r; j++){
			dodajnik = -1 * (mat -> data[j][i]/mat -> data[i][i]);
			norm_row(mat, b, i, j, dodajnik);
		}
	}
	fetch_results(mat, b);
	return 0;
}


