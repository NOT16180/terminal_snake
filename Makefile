all: main

main: grille.o main.o liste_section.o liste_mouvement.o matrice.o serpent.o fonction_jeu.o fonction_jeu_2.o fonction_jeu_1_serpent.o fonction_jeu_2_serpent.o fonction_jeu_3_serpent.o
	gcc grille.o main.o liste_section.o liste_mouvement.o matrice.o serpent.o fonction_jeu.o fonction_jeu_2.o fonction_jeu_1_serpent.o fonction_jeu_2_serpent.o fonction_jeu_3_serpent.o -o main -lncurses

grille.o: grille.c grille.h
	gcc -c -Wall grille.c

liste_section.o: liste_section.c liste_section.h
	gcc -c -Wall liste_section.c

liste_mouvement.o: liste_mouvement.c liste_mouvement.h
	gcc -c -Wall liste_mouvement.c

serpent.o: serpent.c serpent.h
	gcc -c -Wall serpent.c

fonction_jeu_1_serpent.o: fonction_jeu_1_serpent.c  
	gcc -c -Wall fonction_jeu_1_serpent.c

fonction_jeu_2_serpent.o: fonction_jeu_2_serpent.c  
	gcc -c -Wall fonction_jeu_2_serpent.c

fonction_jeu_3_serpent.o: fonction_jeu_3_serpent.c  
	gcc -c -Wall fonction_jeu_3_serpent.c

fonction_jeu.o: fonction_jeu.c  fonction_jeu.h 
	gcc -c -Wall fonction_jeu.c

fonction_jeu_2.o: fonction_jeu_2.c  fonction_jeu_2.h 
	gcc -c -Wall fonction_jeu_2.c

matrice.o: matrice.c matrice.h
	gcc -c -Wall matrice.c

main.o: main.c grille.h
	gcc -c -Wall main.c

clean : 
	rm -f *.o main
