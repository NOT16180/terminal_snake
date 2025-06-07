#ifndef _FONCTION_JEU_H
#define _FONCTION_JEU_H

#include "matrice.h"
#include "serpent.h"
#include "grille.h"

/* Fonction principale du jeu de serpent, prenant en paramètres la taille de la grille (n x m) et le délai entre chaque mouvement */
int jouer_serpent(int n, int m, int delai);

int jouer_serpent_3(int n, int m, int delai);

/* Vérifie si les coordonnées (x, y) sont à l'intérieur de la grille de taille n x m */
int est_dans_grille(int x, int y, int n, int m);

/* Vérifie si la tête du serpent est sur un fruit */
int pos_tete_fruit(struct tete *tete, struct matrice *matrice);

/* Vérifie si la tête du serpent est en collision avec son propre corps */
int collision_corps_serpent(struct tete *tete, struct matrice *matrice);

/* Vérifie si un fruit apparaît sur le corps du serpent */
int apparition_fruit_serpent(struct grille *grille, struct matrice *matrice);

/* Vérifie si le caractère de la touche actuelle et la touche précédente correspondent à des mouvements inverses */
int test_retour(int ch, int ch_dern);

#endif // _FONCTION_JEU_H
