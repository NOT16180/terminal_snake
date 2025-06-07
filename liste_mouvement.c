
#include <stdlib.h>
#include <stdio.h>
#include "liste_mouvement.h"

/* Crée un nouveau maillon de mouvement avec les coordonnées (x, y) et la direction spécifiées */
struct maillon_mouvement *nouveau_maillon_mouvement(int x, int y, enum direction d)
{
    struct maillon_mouvement *m = malloc(sizeof(struct maillon_mouvement));
    if (m != NULL)
    {
        m->x = x;
        m->y = y;
        m->direction = d;
        m->suivant = NULL;
    }
    return m;
}

/* Libère la mémoire allouée pour un maillon de mouvement */
void detruire_maillon_mouvement(struct maillon_mouvement **m)
{
    if (*m != NULL)
    {
        free(*m);
        *m = NULL;
    }
}

/* Initialise une liste chaînée de mouvements vide */
void initialiser_liste_mouvement(struct liste_mouvement *l)
{
    l->premier = NULL;
    l->dernier = NULL;
    l->longueur = 0;
}

/* Vérifie si la liste chaînée de mouvements est vide */
int est_vide_liste_mouvement(const struct liste_mouvement *l)
{
    return (l->premier == NULL);
}

/* Retourne la longueur de la liste chaînée de mouvements */
int longueur_liste_mouvement(const struct liste_mouvement *l)
{
    return l->longueur;
}

/* Insère un maillon de mouvement au début de la liste chaînée de mouvements */
void ajouter_tete_mouvement(struct liste_mouvement *l, struct maillon_mouvement *m)
{
    if (est_vide_liste_mouvement(l))
    {
        l->dernier = m;
    }
    m->suivant = l->premier;
    l->premier = m;
    ++l->longueur;
}

/* Insère un maillon de mouvement à la fin de la liste chaînée de mouvements */
void ajouter_queue_mouvement(struct liste_mouvement *l, struct maillon_mouvement *m)
{
    m->suivant = NULL;
    if (est_vide_liste_mouvement(l))
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

/* Extrait le premier maillon de mouvement de la liste chaînée de mouvements */
struct maillon_mouvement *extraire_maillon_debut_liste_mouvement(struct liste_mouvement *l)
{
    struct maillon_mouvement *m = l->premier;
    if (m != NULL)
    {
        l->premier = m->suivant;
        --l->longueur;
        if (est_vide_liste_mouvement(l))
        {
            l->dernier = NULL;
        }
        m->suivant = NULL;
    }
    return m;
}

/* Extrait le dernier maillon de mouvement de la liste chaînée de mouvements */
struct maillon_mouvement *extraire_maillon_fin_liste_mouvement(struct liste_mouvement *l)
{
    if (est_vide_liste_mouvement(l))
        return NULL;

    struct maillon_mouvement *m = l->premier;
    struct maillon_mouvement *prev = NULL;
    while (m->suivant != NULL)
    {
        prev = m;
        m = m->suivant;
    }

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

    l->longueur--;
    return m;
}

/* Libère la mémoire allouée pour la liste chaînée de mouvements et tous ses maillons */
void detruire_liste_mouvement(struct liste_mouvement **l)
{
    if (*l != NULL)
    {
        while (!est_vide_liste_mouvement(*l))
        {
            struct maillon_mouvement *m = extraire_maillon_debut_liste_mouvement(*l);
            detruire_maillon_mouvement(&m);
        }
        free(*l);
        *l = NULL;
    }
}
