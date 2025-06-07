#ifndef CASE_H
#define CASE_H

// Définition de l'énumération pour les éléments de la case
enum Case
{
    vide, // Case vide
    serp, // Tête ou segment du serpent
    fruit // Fruit
};

// Structure représentant une matrice
struct matrice
{
    int n;           // Nombre de lignes
    int m;           // Nombre de colonnes
    enum Case **tab; // Tableau à deux dimensions de cases
};

// Fonction pour initialiser une matrice avec des cases vides
void matrice_vider(struct matrice *matrice);

// Fonction pour allouer dynamiquement une matrice avec n lignes et m colonnes
struct matrice *matrice_allouer(int n, int m);

// Fonction pour désallouer dynamiquement une matrice
void matrice_desallouer(struct matrice **matrice);

#endif
