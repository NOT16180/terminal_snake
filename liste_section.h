#ifndef _LISTE_SECTION_H
#define _LISTE_SECTION_H




struct maillon_section
{
    int couleur;                     /* couleur du maillon */
    int taille;                      /* taille du maillon */
    struct maillon_section *suivant; /* adresse du maillon suivant */
};

struct liste_section
{
    struct maillon_section *premier; /* adresse du premier maillon de la liste, NULL si la liste est vide */
    struct maillon_section *dernier; /* adresse du dernier maillon de la liste NULL si la liste est vide */
    int longueur;                    /* nombre de maillons dans la liste */
};

/* allocation sur le tas pour un maillon de valeur v */
/* et renvoi de l'adresse du maillon */
struct maillon_section *nouveau_maillon_section(char couleur, int taille);

/* libération de l'espace mémoire occupé par le maillon */
void detruire_maillon_int(struct maillon_section **m);

/* allocation sur le tas pour une liste vide */
/* et renvoi de l'adresse de la liste */
struct liste_section *nouvelle_liste_section();

/* test de la vacuité de la liste d'adresse l */
int est_vide_liste_section(const struct liste_section *l);

/* renvoi du nombre de maillons dans la liste */
int longueur_liste_section(const struct liste_section *l);

/* insertion du maillon d'adresse m au début de la liste d'adresse l */
void ajouter_tete_section(struct liste_section *l, struct maillon_section *m);

/* insertion d'un maillon d'adresse m à la fin de la liste d'adresse l */
void ajouter_queue_section(struct liste_section *l, struct maillon_section *m);

/* extraction du premier maillon de la liste d'adresse l */
/* et renvoi de l'adresse du maillon extrait */
struct maillon_section *extraire_maillon_debut_liste_section(struct liste_section *l);

/* extraction du dernier maillon de la liste d'adresse l */
/* et renvoi de l'adresse du maillon extrait */
struct maillon_section *extraire_maillon_fin_liste_section(struct liste_section *l);

/* libération de l'espace occupé par la liste et tous ses maillons */
void detruire_liste_section(struct liste_section **l);

#endif