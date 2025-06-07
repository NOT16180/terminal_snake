#ifndef _FONCTION_JEU_2_H
#define _FONCTION_JEU_2_H

// Inclusion des fichiers d'en-tête nécessaires
#include "grille.h"
#include "matrice.h"
#include "liste_section.h"
#include "liste_mouvement.h"

// Déclaration de la fonction pour jouer au serpent à deux joueurs
int jouer_serpent_2(int n, int m, int delai, char joueur1[256], char joueur2[256]);

// Déclaration de la fonction pour remplir la grille avec les têtes des serpents
void grille_remplir_2(struct grille *grille, struct tete *tete, struct tete *tete2, struct matrice *matrice);

// Déclaration de la fonction pour tester le retour d'une touche
int test_retour_2(int ch, int ch_dern, int ch_dern2);

#endif // _FONCTION_JEU_2_H
