#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Zwraca <> NULL - udalo sie wczytac
 * Zwraca == NULL - podczas wczytywania wystapil blad
 */
Matrix * readFromFile(char * fname) {
	int r,c;
	int ir, ic;
	FILE * fin =  fopen(fname,"r");
	Matrix * mat = NULL;

	if (fin != NULL) {
		fscanf(fin,"%d %d",&r,&c);
		mat = createMatrix(r,c);
		if (mat != NULL) {
			for (ir = 0; ir < r; ir++) 
				for (ic = 0; ic < c; ic++) {
					if( EOF == fscanf(fin, "%lf",&(mat->data[ir][ic])) ) {
						fprintf( stderr, "[!] readFromFile: podano zbyt malo elementow macierzy\n" );
						return NULL;
				}
			}
			double aux;
			if( EOF != fscanf(fin, "%lf",&aux) ) {
				fprintf( stderr, "[!] readFromFile: podano zbyt duzo elementow macierzy\n" );
				return NULL;
			}
		} else {
			fprintf(stderr,"Wystąpił problem podczas tworzenia macierzy o rozmiarach %d x %d dla danych z pliku: %s\n", r, c, fname);		}

			fclose(fin);
		} else {
			fprintf(stderr,"Nie mogę otworzyć pliku o nazwie: %s\n", fname);
		}

		return mat;
}

void printToScreen(Matrix *mat) {
	int i,j;
	printf("[ \n");
	for (i = 0; i<mat->r; i++) {
		printf("  ");
		for (j = 0; j < mat->c; j++) {
			printf("%f ", mat->data[i][j]);
		}
		printf("; \n");
	}
	printf("]\n");
}

Matrix * createMatrix(int r, int c) {
		int i;
		Matrix * mat = (Matrix*) malloc(sizeof(Matrix));
		if (mat != NULL) {
			mat->r = r;
			mat->c = c;
			mat->data = (double**) malloc(sizeof(double*) * r);
			for (i=0; i < r; i++) {
					mat->data[i] = (double*) malloc(sizeof(double) * c);
			}
		}

		return mat;
}

Matrix * copyMatrix( Matrix *mat ) {
	Matrix *mat_copy = createMatrix( mat->r, mat->c );
	if( NULL == mat_copy ) {
		fprintf( stderr, "[!] copyMatrix: nie udalo sie zaalokowac pamieci na kopie macierzy\n" );
		return NULL;
	}
	int ir;
	int ic;
	for( ir = 0; ir < mat->r; ir++ ) {
		for( ic = 0; ic < mat->c; ic++ ) {
			mat_copy->data[ir][ic] = mat->data[ir][ic];
		}
	}
	return mat_copy;
}

void freeMatrix(Matrix * mat) {
  int i;
	for (i=0;i < mat->r; i++)
		free(mat->data[i]);
	free(mat->data);
	free(mat);
}

