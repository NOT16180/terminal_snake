#include <stdio.h>
#include <stdlib.h>
#include "liste_section.h"

/* Alloue sur le tas de la mémoire pour un maillon de valeur v */
/* et renvoie l'adresse du maillon */
struct maillon_section *nouveau_maillon_section(char couleur, int taille)
{
    struct maillon_section *m = malloc(sizeof(struct maillon_section));
    m->couleur = couleur;
    m->taille = taille;
    m->suivant = NULL;
    return m;
}

/* Libère l'espace mémoire occupé sur le tas par le maillon d'adresse m */
void detruire_maillon_section(struct maillon_section **m)
{
    if (*m != NULL)
    {
        free(*m);
        *m = NULL;
    }
}

/** Teste si la liste est vide */
/* renvoie un entier ≠ 0 si la liste d'adresse l est vide, 0 sinon */
int est_vide_liste_section(const struct liste_section *l)
{
    return (l->premier == NULL);
}

/** Renvoie le nombre de maillons dans la liste d'adresse l */
int longueur_liste_section(const struct liste_section *l)
{
    return l->longueur;
}

/* Insère le maillon d'adresse m au début de la liste d'adresse l */
void ajouter_tete_section(struct liste_section *l, struct maillon_section *m)
{

    if (est_vide_liste_section(l))
    {
        l->dernier = m;
    }
    m->suivant = l->premier;
    l->premier = m;
    ++l->longueur;
}

/* Insère le maillon d'adresse m à la fin de la liste d'adresse l */
void ajouter_queue_section(struct liste_section *l, struct maillon_section *m)
{
    m->suivant = NULL;
    if (est_vide_liste_section(l))
    {
        l->premier = m;
    }
    else
    {
        l->dernier->suivant = m;
    }
    l->dernier = m;
    ++l->longueur;
}

/** Extrait le premier maillon de la liste d'adresse l */
/* et renvoie l'adresse du maillon extrait */
/** Renvoie NULL si la liste est vide */
struct maillon_section *extraire_maillon_debut_liste_section(struct liste_section *l)
{
    struct maillon_section *m = l->premier;
    if (m != NULL)
    {
        l->premier = m->suivant;
        --l->longueur;
        if (est_vide_liste_section(l))
        {
            l->dernier = NULL;
        }
        m->suivant = NULL;
    }
    return m;
}

/** Extrait le dernier maillon de la liste d'adresse l */
/* et renvoie l'adresse du maillon extrait */
/* Renvoie NULL si la liste est vide */
struct maillon_section *extraire_maillon_fin_liste_section(struct liste_section *l)
{
    // Vérifier si la liste est vide
    if (est_vide_liste_section(l))
        return NULL;

    struct maillon_section *m = l->premier;
    struct maillon_section *prev = NULL;

    // Parcours de la liste jusqu'au dernier maillon
    while (m->suivant != NULL)
    {
        prev = m;
        m = m->suivant;
    }

    // Si la liste ne contient qu'un seul maillon
    if (prev == NULL)
    {
        l->premier = NULL;
        l->dernier = NULL;
    }
    else
    {
        prev->suivant = NULL;
        l->dernier = prev;
    }

    // Réduction de la longueur de la liste
    l->longueur--;

    return m;
}

/** Libère l'espace mémoire occupé sur le tas par la liste et tous ses maillons */
void detruire_liste_section(struct liste_section **l)
{
    if (*l != NULL)
    {
        while (!est_vide_liste_section(*l))
        {
            struct maillon_section *m = extraire_maillon_debut_liste_section(*l);
            detruire_maillon_section(&m);
        }
        free(*l);
        *l = NULL;
    }
}
