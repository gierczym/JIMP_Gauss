#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char ** argv) {
	int res;
	Matrix * A = readFromFile(argv[1]);
	Matrix * b = readFromFile(argv[2]);
	Matrix * x;
	
	int flag_test = 0; // set to 1 when program called with -t flag as third argument

	if( (argc > 3) && (0 == strcmp("-t", argv[3])) )
		flag_test = 1;


	if( flag_test ) {
		printf( "\n=====================================================\n" );
		printf( "TEST: Plik A: \"%s\", Plik b: \"%s\"\n", argv[1], argv[2] );
	}

	if (A == NULL) {
		if( flag_test )
			printf( "[!] FAILED: nie udalo sie wczytac macierzy A\n");
		return -1;
	}
	if (b == NULL) {
		if( flag_test )
			printf( "[!] FAILED: nie udalo sie wczytac macierzy b\n");
	       	return -2;
	}

	if( !flag_test ) {
		printf( "Wczytane dane:\n" );
		printToScreen(A);
		printToScreen(b);
	}

	if( !flag_test ) {
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
		
		res = eliminate(A,b);
		if( res != 0 ) {
			fprintf( stderr, "[!] FAILED main.c: eliminacja nieudana, zwrocono kod %d\n", res );
			return EXIT_FAILURE;
		}
		x = createMatrix(b->r, 1);
		if ( NULL == x) {
			fprintf( stderr,"[!] FAILED main.c: Nie mogłem utworzyć wektora wynikowego x\n" );
			return EXIT_FAILURE;
		}
		res = backsubst(x,A,b);
		if ( res != 0 ) {
			fprintf( stderr, "[!] FAILED main.c: Nie udalo sie wykonac podstawienia\n" );
			return EXIT_FAILURE;
		}

		freeMatrix(x);
	}

	

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
