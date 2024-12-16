all:
	@gcc -Wall --pedantic src/main.c src/mat_io.c src/gauss.c src/backsubst.c -o bin/gauss

test: all
	@echo
	@echo "OCZEKIWANIE: Dane poprawne, program powinien policzyc poprawnie wynik"
	@bin/gauss dane/A_1_1 dane/b_1_1 -t
	@echo
	@echo "OCZEKIWANIE: Dane poprawne, program powinien policzyc poprawnie wynik"
	@bin/gauss dane/A_1_2 dane/b_1_2 -t
	@echo
	@echo "OCZEKIWANIE: (element 1x1 (na diagonali) jest równy 0): Dane poprawne, program powinien policzyc poprawnie wynik"
	@bin/gauss dane/A_2 dane/b_2 -t
	@echo
	@echo "OCZEKIWANIE: (macierz osobliwa): Program powinien to wykryc i powiadomic o tym."
	@bin/gauss dane/A_3 dane/b_3 -t
	@echo
	@echo "OCZEKIWANIE: (macierz podana nie jako jeden wiersz, tylko kazdy wiersz pod soba): Program powinien mimo wszystko policzyc poprawny wynik."
	@bin/gauss dane/A_4_1 dane/b_4_1 -t
	@echo
	@echo "OCZEKIWANIE: (zbyt dużo elementów macierzy): Program powinien to wykryc i powiadomic uzytkownika o niewlasciwym rozmiarze."
	@bin/gauss dane/A_4_2 dane/b_4_2 -t
	@echo
	@echo "OCZEKIWANIE: (zbyt mało elementów macierzy): Program powinien to wykryc i powiadomic uzytkownika o niewlasciwym rozmiarze."
	@bin/gauss dane/A_4_3 dane/b_4_3 -t
	@echo
	@echo "OCZEKIWANIE: (macierz sprzeczna): Program powinien to wykryc i powiadomic uzytkownika."
	@bin/gauss dane/A_5 dane/b_5 -t
	@echo
