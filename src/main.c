#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define EPSILON 0.00000001

int main(int argc, char ** argv) {
	int res;
	Matrix * A = readFromFile(argv[1]);
	Matrix * b = readFromFile(argv[2]);
	Matrix * x;
	
	int flag_test = 0; // set to 1 when program called with -t flag as third argument

	if( (argc > 3) && (0 == strcmp("-t", argv[3])) )
		flag_test = 1;


	if( flag_test ) {
		printf( "=====================================================\n" );
		printf( "TEST: Plik A: \"%s\", Plik b: \"%s\"\n", argv[1], argv[2] );
	}

	if (A == NULL) {
		printf( "[!] FAILED: nie udalo sie wczytac macierzy A\n");
		return -1;
	}
	if (b == NULL) {
		printf( "[!] FAILED: nie udalo sie wczytac macierzy b\n");
	       	return -2;
	}


	if( !flag_test ) {
		printf( "Wczytane dane:\n" );
		printToScreen(A);
		printToScreen(b);
		res = eliminate(A,b);
		if( res != 0 ) {
			fprintf( stderr, "[!] main.c: eliminacja nieudana, zwrocono kod %d\n", res );
			return EXIT_FAILURE;
		}
		x = createMatrix(b->r, 1);
		if (x != NULL) {
			printf( "\nWyniki:\n");
			printToScreen(A);
			printToScreen(b);
			res = backsubst(x,A,b);
			printToScreen(x);	
			freeMatrix(x);
		} else {
			fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
		}
	} else {
		printf( "PASSED - wczytywanie danych - Macierz A [%dx%d], macierz b [%dx%d]\n", A->r, A->c, b->r, b->c );
		Matrix *A_copy = copyMatrix( A );
		Matrix *b_copy = copyMatrix( b );
		if( NULL == A_copy ) {
			fprintf( stderr, "[!] FAILED main.c: nie udalo sie skopiowac macierzy A\n" );
			return 0;
		}
		if( NULL == b_copy ) {
			fprintf( stderr, "[!] FAILED main.c: nie udalo sie skopiowac macierzy b\n" );
			return 0;
		}
		res = eliminate(A,b);
		if( res != 0 ) {
			fprintf( stderr, "[!] FAILED main.c: eliminacja nieudana, zwrocono kod %d\n", res );
			return 0;
		}
		x = createMatrix(b->r, 1);
		if ( NULL == x) {
			fprintf( stderr,"[!] FAILED main.c: Nie mogłem utworzyć wektora wynikowego x\n" );
			return 0;
		}
		res = backsubst(x,A,b);
		if ( res != 0 ) {
			fprintf( stderr, "[!] FAILED main.c: Nie udalo sie wykonac podstawienia\n" );
			return 0;
		}
		int ir;
		int ic;
		double res_check;
		printf( "---------------------------------------\n" );
		printf( "| Sprawdzam poprawnosc wyniku:        |\n" );
		printf( "---------------------------------------\n" );
		printf( "| wynik | zmienna | powinno |   jest  |\n");
		printf( "---------------------------------------\n" );
		for( ir = 0; ir < x->r; ir++ ) { // sprawdzanie poprawnosci wyniku
			res_check = 0.0;
			for( ic = 0; ic < A_copy->c; ic++ )
				res_check += x->data[ic][0] * A_copy->data[ir][ic];
		        if( fabs(res_check - b_copy->data[ir][0]) > EPSILON ) {
				printf( "| FAIL  |");
			} else {
				printf( "| PASS  |");
			}	
			printf( " x%-6d | %7g | %7g |\n", ir+1, b_copy->data[ir][0], res_check );		
			printf( "---------------------------------------\n" );
		}

		freeMatrix(x);
	}

	

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
