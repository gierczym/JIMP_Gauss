#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b);

void norm_row(Matrix *mat, Matrix *b, int row2norm, int row2benorm, double normaliser); //normalizuje wiersz row2benorm za pomocą wiersza row2norm poprzez policzony wcześniej normalizer dla macierzy mat i b

void fetch_results(Matrix *mat, Matrix *b); //dzieli każdy element macierzy wyników b przez odpowiadający jej element macierzy diagonalnej A

int is_matrix_singular(Matrix *mat); //sprawdza, czy macierz jest kwadratowa i czy na diagonali nie leży 0

#endif
