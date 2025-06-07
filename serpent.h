#ifndef SERPENT_H
#define SERPENT_H

// Structure représentant la tête du serpent
struct tete
{
    int x;                                   // Position x de la tête
    int y;                                   // Position y de la tête
    int couleur;                             // Couleur de la tête (potentiellement pour l'affichage)
    struct liste_section *liste_section;     // Pointeur vers la liste des sections du serpent
    struct liste_mouvement *liste_mouvement; // Pointeur vers la liste des mouvements du serpent
};

//  fonction pour créer une nouvelle liste de sections pour le serpent
struct liste_section *creer_liste_section();

// fonction pour créer une nouvelle liste de mouvements pour le serpent
struct liste_mouvement *creer_liste_mouvement();

#endif /* SERPENT_H */
