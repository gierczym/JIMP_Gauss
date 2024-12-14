#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char ** argv) {
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
	       	return -2;
	}
	printf( "Wczytane dane:\n" );
	printToScreen(A);
	printToScreen(b);

	eliminate(A,b);

	x = createMatrix(b->r, 1);
	if (x != NULL) {
		printf( "\nWyniki:\n");
		printToScreen(A);
		printToScreen(b);
		backsubst(x,A,b);
		printToScreen(x);
		freeMatrix(x);
	} else {
		fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
	}

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
