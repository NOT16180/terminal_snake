#include <stdlib.h>
#include <stdio.h> // Ajout pour la fonction printf.h>
#include "matrice.h"

// Fonction pour allouer dynamiquement une matrice avec n lignes et m colonnes
struct matrice *matrice_allouer(int n, int m)
{
    // Allocation de mémoire pour la structure de matrice
    struct matrice *matrice = malloc(sizeof(struct matrice));

    // Vérification si l'allocation de mémoire a réussi
    if (matrice == NULL)
    {
        perror("Erreur d'allocation pour la matrice\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des dimensions de la matrice
    matrice->n = n;
    matrice->m = m;

    // Allocation de mémoire pour le tableau à deux dimensions de cases
    matrice->tab = malloc(n * sizeof(enum Case *));

    // Vérification si l'allocation de mémoire a réussi
    if (matrice->tab == NULL)
    {
        perror("Erreur d'allocation pour le tableau de cases\n");
        exit(EXIT_FAILURE);
    }

    // Allocation de mémoire pour chaque ligne du tableau
    for (int i = 0; i < n; i++)
    {
        matrice->tab[i] = malloc(m * sizeof(enum Case));

        // Vérification si l'allocation de mémoire a réussi
        if (matrice->tab[i] == NULL)
        {
            perror("Erreur d'allocation pour une ligne du tableau de cases\n");
            exit(EXIT_FAILURE);
        }
    }

    return matrice;
}

// Fonction pour initialiser chaque case de la matrice avec l'élément vide
void matrice_vider(struct matrice *matrice)
{
    // Parcours de chaque case de la matrice
    for (int i = 0; i < matrice->n; i++)
    {
        for (int e = 0; e < matrice->m; e++)
        {
            matrice->tab[i][e] = vide;
        }
    }
}

// Fonction pour désallouer dynamiquement la mémoire allouée pour une matrice
void matrice_desallouer(struct matrice **matrice)
{
    if (matrice != NULL)
    {
        // Libération de la mémoire pour chaque ligne du tableau
        for (int i = 0; i < (*matrice)->n; i++)
        {
            free((*matrice)->tab[i]);
        }
        // Libération de la mémoire pour le tableau à deux dimensions
        free((*matrice)->tab);
        // Libération de la mémoire pour la structure matrice
        free(*matrice);
        // Définition du pointeur à NULL pour éviter les références invalides
        *matrice = NULL;
    }
}
