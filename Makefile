all:
	gcc -Wall --pedantic src/main.c src/mat_io.c src/gauss.c src/backsubst.c -o bin/gauss

test: all
	@bin/gauss dane/A dane/b -t
	@bin/gauss dane/A2 dane/b2 -t
	@bin/gauss dane/A_niepopr1 dane/b_niepopr1 -t
