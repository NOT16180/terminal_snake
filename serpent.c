#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "serpent.h"
#include "liste_section.h"
#include "liste_mouvement.h"
#include "grille.h"

// Définition d'une structure pour une liste de sections
struct liste_section *creer_liste_section()
{
    // Allocation de mémoire pour la liste
    struct liste_section *l = malloc(sizeof(struct liste_section));
    // Initialisation des pointeurs de début et de fin à NULL
    l->premier = NULL;
    l->dernier = l->premier;
    // Initialisation de la longueur de la liste à 0
    l->longueur = 0;

    // Retourne un pointeur vers la liste créée
    return l;
}

// Définition d'une structure pour une liste de mouvements
struct liste_mouvement *creer_liste_mouvement()
{
    // Allocation de mémoire pour la liste
    struct liste_mouvement *l = malloc(sizeof(struct liste_mouvement));
    // Initialisation des pointeurs de début et de fin à NULL
    l->premier = NULL;
    l->dernier = l->premier;
    // Initialisation de la longueur de la liste à 0
    l->longueur = 0;

    // Retourne un pointeur vers la liste créée
    return l;
}
