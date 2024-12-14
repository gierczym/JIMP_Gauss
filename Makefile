all:
	gcc -Wall --pedantic src/main.c src/mat_io.c src/gauss.c src/backsubst.c -o bin/gauss

test: all
	bin/gauss dane/A dane/b -t
