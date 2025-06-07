#ifndef _LISTE_MOUVEMENT_H
#define _LISTE_MOUVEMENT_H

// Énumération des directions possibles
enum direction
{
    HAUT,
    BAS,
    GAUCHE,
    DROITE
};

// Structure d'un maillon de mouvement
struct maillon_mouvement
{
    int x;
    int y;
    enum direction direction;
    struct maillon_mouvement *suivant;
};

// Structure d'une liste chaînée de mouvements
struct liste_mouvement
{
    struct maillon_mouvement *premier;
    struct maillon_mouvement *dernier;
    int longueur;
};

// Crée un nouveau maillon de mouvement avec les coordonnées (x, y) et la direction spécifiées
struct maillon_mouvement *nouveau_maillon_mouvement(int x, int y, enum direction d);

// Libère la mémoire allouée pour un maillon de mouvement
void detruire_maillon_mouvement(struct maillon_mouvement **m);

// Initialise une liste chaînée de mouvements vide
void initialiser_liste_mouvement(struct liste_mouvement *l);

// Vérifie si la liste chaînée de mouvements est vide
int est_vide_liste_mouvement(const struct liste_mouvement *l);

// Retourne la longueur de la liste chaînée de mouvements
int longueur_liste_mouvement(const struct liste_mouvement *l);

// Insère un maillon de mouvement au début de la liste chaînée de mouvements
void ajouter_tete_mouvement(struct liste_mouvement *l, struct maillon_mouvement *m);

// Insère un maillon de mouvement à la fin de la liste chaînée de mouvements
void ajouter_queue_mouvement(struct liste_mouvement *l, struct maillon_mouvement *m);

// Extrait le premier maillon de mouvement de la liste chaînée de mouvements
struct maillon_mouvement *extraire_maillon_debut_liste_mouvement(struct liste_mouvement *l);

// Extrait le dernier maillon de mouvement de la liste chaînée de mouvements
struct maillon_mouvement *extraire_maillon_fin_liste_mouvement(struct liste_mouvement *l);

// Libère la mémoire allouée pour la liste chaînée de mouvements et tous ses maillons
void detruire_liste_mouvement(struct liste_mouvement **l);

#endif // _LISTE_MOUVEMENT_H
