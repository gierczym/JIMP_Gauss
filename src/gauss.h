#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b);

void norm_row(Matrix *mat, Matrix *b, int row2norm, int row2benorm, double normaliser); //normalizuje wiersz row2benorm za pomocą wiersza row2norm poprzez policzony wcześniej normalizer dla macierzy mat i b

void replace_rows(Matrix *mat, int r1, int r2); //zamienia w macierzy mat wiersz r1 z r2 (wskaźniki na nie)

int select_master_elem(Matrix *A, Matrix *b, int col); //wybiera maksymalny moduł elementów kolumny macierzy, zwraca 0 jeśli na diagonali i poniżej są tylko zera

#endif