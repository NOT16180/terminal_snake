#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Ajout pour la fonction strcpy
#include <time.h>
#include "grille.h"
#include "serpent.h"
#include "liste_section.h"
#include "liste_mouvement.h"
#include "matrice.h"

/* Alloue dynamiquement une grille de dimensions n x m */
struct grille *grille_allouer(int n, int m)
{
    // Allocation de mémoire pour la structure grille
    struct grille *p = malloc(sizeof(struct grille));

    // Vérification de l'allocation
    if (p == NULL)
    {
        perror("Erreur d'allocation de la grille\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des dimensions de la grille
    p->n = n;
    p->m = m;

    // Allocation de mémoire pour le tableau à deux dimensions
    p->tab = malloc(n * sizeof(char **)); // Allocation de n lignes

    p->fruit = malloc(sizeof(struct fruit));

    // Vérification de l'allocation
    if (p->tab == NULL)
    {
        perror("Erreur d'allocation pour le tableau\n");
        exit(EXIT_FAILURE);
    }

    // Allocation de mémoire pour chaque élément du tableau à deux dimensions
    for (int i = 0; i < n; i++)
    {
        p->tab[i] = malloc(m * sizeof(char *)); // Allocation de m colonnes pour chaque ligne

        // Vérification de l'allocation
        if (p->tab[i] == NULL)
        {
            perror("Erreur d'allocation pour le tableau 2\n");
            exit(EXIT_FAILURE);
        }

        // Allocation de mémoire pour chaque case du tableau
        for (int e = 0; e < m; e++)
        {
            p->tab[i][e] = malloc(8 * sizeof(char)); // Allocation de 8 caractères par case

            // Vérification de l'allocation
            if (p->tab[i][e] == NULL)
            {
                perror("Erreur d'allocation pour le tableau 3\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return p;
}

/* Vide la grille en mettant deux espaces dans chaque case */
void grille_vider(struct grille *a)
{
    for (int i = 0; i < a->n; i++)
    {
        for (int e = 0; e < a->m; e++)
        {
            strcpy(a->tab[i][e], "\033[43m  \033[00m"); // Copie deux espaces dans chaque case
        }
    }
}

/* Tire au sort une position pour le fruit et la stocke dans la grille */
void grille_tirage_fruit(struct grille *a)
{
    // Génère aléatoirement des coordonnées pour le fruit
    a->fruit->x = (rand() % a->n);
    a->fruit->y = (rand() % a->m);
}

/* Remplit une case de la grille avec une couleur de fond rouge */
void grille_remplir(struct grille *grille, struct tete *tete, struct matrice *matrice)
{
    // Vide d'abord la grille pour éviter tout contenu précédent
    grille_vider(grille);
    matrice_vider(matrice);

    // Récupère les coordonnées de la tête du serpent
    int x = tete->x;
    int y = tete->y;

    // Récupère les coordonnées du fruit
    int n = grille->fruit->x;
    int m = grille->fruit->y;

    // Place le fruit dans la grille avec une couleur de fond rouge
    strcpy(grille->tab[m][n], "\033[41m  \033[0m"); // Copie la couleur de fond rouge dans la case
    matrice->tab[m][n] = fruit;

    // Place la tête du serpent dans la grille avec sa couleur spécifiée
    sprintf(grille->tab[y][x], "\033[%dm--\033[0m", tete->couleur); // Copie la couleur de la tête dans la case
    matrice->tab[y][x] = serp;                                      // Met à jour la matrice pour refléter la présence de la tête du serpent

    // Place les sections du serpent dans la grille avec leurs couleurs respectives
    struct maillon_section *current_section = tete->liste_section->premier;
    struct maillon_mouvement *current_mouvement = tete->liste_mouvement->premier;
    for (int i = 0; i < tete->liste_section->longueur; i++)
    {
        // Place la section du serpent dans la grille avec sa couleur spécifiée
        sprintf(grille->tab[current_mouvement->y][current_mouvement->x], "\033[%dm  \033[0m", current_section->couleur);
        matrice->tab[current_mouvement->y][current_mouvement->x] = serp; // Met à jour la matrice pour refléter la présence de la section du serpent
        current_section = current_section->suivant;
        current_mouvement = current_mouvement->suivant;
    }

    // Redessine la grille pour refléter les changements effectués
    redessiner_grille(grille);
}

/* Désalloue la mémoire occupée par la grille */
void grille_desallouer(struct grille **a)
{
    if (a != NULL)
    {
        // Libération de la mémoire pour chaque case du tableau
        for (int i = 0; i < (*a)->n; i++)
        {
            for (int j = 0; j < (*a)->m; j++)
            {
                free((*a)->tab[i][j]);
            }
            free((*a)->tab[i]); // Libération de la mémoire pour chaque ligne
        }
        free((*a)->tab); // Libération de la mémoire pour le tableau à deux dimensions
        free(*a);        // Libération de la mémoire pour la structure grille
        *a = NULL;       // Définition du pointeur à NULL
    }
}

/* Affiche le contenu de la grille */
void redessiner_grille(struct grille *a)
{
    printf("\33[2J\33[H"); // Efface le contenu de la console

    for (int i = -1; i < a->n + 1; i++)
    {
        for (int e = -1; e < a->m + 1; e++)
        {
            if (e == -1 || i == -1 || i == a->n || e == a->m)
            {
                printf("\033[45m  \033[00m"); // Affichage de la ligne i du haut
            }
            else
            {
                printf("%s", a->tab[i][e]); // Affichage de chaque case
            }
        }
        printf("\33[1E"); // Nouvelle ligne à la fin de chaque ligne
    }

    fflush(stdout);
}
