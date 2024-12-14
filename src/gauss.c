#include "gauss.h"
#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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

void replace_rows(Matrix *mat, int r1, int r2){
	double *tmp = mat -> data[r1];
	mat -> data[r1] = mat -> data[r2];
	mat -> data[r2] = tmp;
}

int select_master_elem(Matrix *A, Matrix *b, int col){
	int max_elem_row_index = -1;
	double max_elem_val = 0;
	for(int i = col; i < A -> r; i++){
		if(fabs(A -> data[i][col]) > max_elem_val){
			max_elem_val = fabs(A -> data[i][col]);
			max_elem_row_index = i;
		}
	}
	if(max_elem_val == 0){
		printf("[!] select_master_elem: wszystkie wiersze w kolumnie %d od diagonali w dół mają współczynniki równe zero\n", col);
		return 1;
	}
	replace_rows(A, col, max_elem_row_index);
	replace_rows(b, col, max_elem_row_index);
	return 0;
}

int eliminate(Matrix *mat, Matrix *b){
	double dodajnik = 0;
	for(int i = 0; i < mat -> c; i++){ // zamienia macierz na dolnotrójkątną
		if(select_master_elem(mat, b, i) == 1)
			return 1;
		for(int j = i+1; j < mat -> r; j++){
			dodajnik = -1 * (mat -> data[j][i]/mat -> data[i][i]);
			norm_row(mat, b, i, j, dodajnik);
		}
	}
	return 0;
}
