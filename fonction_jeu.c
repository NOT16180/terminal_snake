#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "grille.h"
#include "serpent.h"
#include "matrice.h"
#include "liste_mouvement.h"
#include "liste_section.h"

// Vérifie si les coordonnées (x, y) sont à l'intérieur de la grille de taille n x m
int est_dans_grille(int x, int y, int n, int m)
{
    return (x >= 0 && x < n && y >= 0 && y < m);
}

// Vérifie si la tête du serpent est sur un fruit
int pos_tete_fruit(struct tete *tete, struct matrice *matrice)
{
    return (matrice->tab[tete->y][tete->x] == fruit);
}

// Vérifie si la tête du serpent est en collision avec son propre corps
int collision_corps_serpent(struct tete *tete, struct matrice *matrice)
{
    return (matrice->tab[tete->y][tete->x] == serp);
}

// Vérifie si un fruit apparaît sur le corps du serpent
int apparition_fruit_serpent(struct grille *grille, struct matrice *matrice)
{
    return (matrice->tab[grille->fruit->y][grille->fruit->x] == serp);
}

// Vérifie si le caractère de la touche actuelle et la touche précédente correspondent à des mouvements inverses
int test_retour(int ch, int ch_dern)
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

    else
    {
        return ch;
    }
}
