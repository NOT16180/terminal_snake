#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Ajout pour la fonction strcpy
#include <ncurses.h>

#include "fonction_jeu_2.h"
#include "grille.h"
#include "matrice.h"
#include "liste_section.h"
#include "liste_mouvement.h"

void grille_remplir_2(struct grille *grille, struct tete *tete, struct tete *tete2, struct matrice *matrice)
{
    // Vide d'abord la grille pour éviter tout contenu précédent
    grille_vider(grille);
    matrice_vider(matrice);

    // Récupère les coordonnées de la tête du serpent
    int x = tete->x;
    int y = tete->y;

    int x2 = tete2->x;
    int y2 = tete2->y;

    // Récupère les coordonnées du fruit
    int n = grille->fruit->x;
    int m = grille->fruit->y;

    // Place le fruit dans la grille avec une couleur de fond rouge
    strcpy(grille->tab[m][n], "\033[41m  \033[0m"); // Copie la couleur de fond rouge dans la case
    matrice->tab[m][n] = fruit;

    // Place la tête du serpent dans la grille avec sa couleur spécifiée
    sprintf(grille->tab[y][x], "\033[%dm--\033[0m", tete->couleur); // Copie la couleur de la tête dans la case
    matrice->tab[y][x] = serp;                                      // Met à jour la matrice pour refléter la présence de la tête du serpent

    // Place la tête du serpent dans la grille avec sa couleur spécifiée
    sprintf(grille->tab[y2][x2], "\033[%dm--\033[0m", tete2->couleur); // Copie la couleur de la tête dans la case
    matrice->tab[y2][x2] = serp;                                       // Met à jour la matrice pour refléter la présence de la tête du serpent

    // Place les sections du serpent dans la grille avec leurs couleurs respectives
    struct maillon_section *current_section = tete->liste_section->premier;
    struct maillon_mouvement *current_mouvement = tete->liste_mouvement->premier;
    struct maillon_section *current_section2 = tete2->liste_section->premier;
    struct maillon_mouvement *current_mouvement2 = tete2->liste_mouvement->premier;
    for (int i = 0; i < tete->liste_section->longueur; i++)
    {
        // Place la section du serpent dans la grille avec sa couleur spécifiée
        sprintf(grille->tab[current_mouvement->y][current_mouvement->x], "\033[%dm  \033[0m", current_section->couleur);
        matrice->tab[current_mouvement->y][current_mouvement->x] = serp; // Met à jour la matrice pour refléter la présence de la section du serpent
        current_section = current_section->suivant;
        current_mouvement = current_mouvement->suivant;
    }

    for (int i = 0; i < tete2->liste_section->longueur; i++)
    {
        // Place la section du serpent dans la grille avec sa couleur spécifiée
        sprintf(grille->tab[current_mouvement2->y][current_mouvement2->x], "\033[%dm  \033[0m", current_section2->couleur);
        matrice->tab[current_mouvement2->y][current_mouvement2->x] = serp; // Met à jour la matrice pour refléter la présence de la section du serpent
        current_section2 = current_section2->suivant;
        current_mouvement2 = current_mouvement2->suivant;
    }

    // Redessine la grille pour refléter les changements effectués
    redessiner_grille(grille);
}

// Vérifier si le joueur entre une touche differente de l'inverse de la précédente
int test_retour_2(int ch, int ch_dern, int ch_dern2)
{
    if (ch_dern == KEY_UP && ch == KEY_DOWN)
    {
        return KEY_UP;
    }

    if (ch_dern == KEY_DOWN && ch == KEY_UP)
    {
        return KEY_DOWN;
    }

    if (ch_dern == KEY_RIGHT && ch == KEY_LEFT)
    {
        return KEY_RIGHT;
    }

    if (ch_dern == KEY_LEFT && ch == KEY_RIGHT)
    {
        return KEY_LEFT;
    }

    if (ch_dern2 == 'z' && ch == 's')
    {
        return 'z';
    }

    if (ch_dern2 == 's' && ch == 'z')
    {
        return 's';
    }

    if (ch_dern2 == 'q' && ch == 'd')
    {
        return 'q';
    }

    if (ch_dern2 == 'd' && ch == 'q')
    {
        return 'd';
    }

    else
    {
        return ch;
    }
}
