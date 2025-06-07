#ifndef _GRILLE_H
#define _GRILLE_H

#include "serpent.h"
#include "matrice.h"

// pour les pouvoirs


struct fruit
{
    int x;
    int y;
};

struct grille
{
    int n;               // Nombre de rangées de la grille
    int m;               // Nombre de colonnes de la grille
    char ***tab;         // Tableau de chaînes de caractères représentant la grille
    struct fruit *fruit; // Coordonnées du fruit sur la grille
};

/* Alloue dynamiquement une structure grille et son tableau de chaînes de caractères de taille 8 */
struct grille *grille_allouer(int n, int m);

/* Remplit chaque case du tableau avec deux espaces de fond noir */
void grille_vider(struct grille *a);

/* Tire au sort une case pour y placer un fruit, stockant ses coordonnées dans la structure grille */
void grille_tirage_fruit(struct grille *a);

/* Remplit la case correspondant à la tête du serpent avec deux espaces de couleur de fond rouge */
void grille_remplir(struct grille *grille, struct tete *tete, struct matrice *matrice);

/* Désalloue la mémoire associée à la structure grille et son contenu */
void grille_desallouer(struct grille **a);

/* Redessine la grille avec ses éléments mis à jour */
void redessiner_grille(struct grille *a);

#endif // _GRILLE_H
