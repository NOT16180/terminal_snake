#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h> // Ajout pour la fonction strcpy
#include <unistd.h> // Ajout pour la fonction sleep
#include <ncurses.h>

#include "serpent.h"
#include "fonction_jeu.h"
#include "fonction_jeu_2.h"
#include "matrice.h"
#include "grille.h"
#include "liste_section.h"
#include "liste_mouvement.h"

extern int score;
extern int score2;

// Fonction principale pour jouer au jeu du serpent
int jouer_serpent_2(int n, int m, int delai, char joueur1[256], char joueur2[256])
{
    int couleur;

    int first = 0;
    int ch, ch_dern = KEY_UP; // Variable pour stocker la touche pressée par l'utilisateur

    int ch_dern2 = 's';

    int prevx = 0, prevy = 0; // Variables pour stocker les coordonnées précédentes de la tête du serpent

    int prevx2 = 0, prevy2 = 0; // Variables pour stocker les coordonnées précédentes de la tête du serpent

    // Allouer la grille et initialiser la tête du serpent
    struct grille *grille = grille_allouer(n, m);
    if (grille == NULL)
    {
        printf("Erreur lors de l'allocation de la grille.\n");
        return EXIT_FAILURE;
    }

    // Allouer la matrice
    struct matrice *matrice = matrice_allouer(n, m);

    // Initialiser la tête du serpent
    struct tete *tete = malloc(sizeof(struct tete));
    struct liste_section *ls = creer_liste_section();
    struct liste_mouvement *lm = creer_liste_mouvement();
    tete->x = n - 2;
    tete->y = m - 2;
    tete->couleur = 46;
    tete->liste_section = ls;
    tete->liste_mouvement = lm;

    // Initialiser la tête du serpent
    struct tete *tete2 = malloc(sizeof(struct tete));
    struct liste_section *ls2 = creer_liste_section();
    struct liste_mouvement *lm2 = creer_liste_mouvement();
    tete2->x = 1;
    tete2->y = 1;
    tete2->couleur = 44;
    tete2->liste_section = ls2;
    tete2->liste_mouvement = lm2;

    // Initialiser la position du fruit dans la grille
    grille_tirage_fruit(grille);

    // Initialiser la position de la tête du serpent dans la grille

    // Initialiser ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    halfdelay(delai);

    do
    {
        // Sauvegarder les coordonnées précédentes de la tête du serpent
        prevy = tete->y;
        prevx = tete->x;

        prevy2 = tete2->y;
        prevx2 = tete2->x;
        // Détecter la touche pressée par l'utilisateur
        ch = getch();

        ch = test_retour_2(ch, ch_dern, ch_dern2);

        if (ch == -1)
        { /* Si aucune touche utilisee, getch renvoie -1 */
            /* Comme aucune touche n'a ete utilisee
               le programme peut faire autre chose */

            if (first % 2 == 0)
            {
                ch = ch_dern2;
            }
            else
            {
                ch = ch_dern;
            }
            first++;
        }

        switch (ch)
        {

        case KEY_UP:
            tete->y--;
            break;
        case KEY_DOWN:
            tete->y++;
            break;
        case KEY_LEFT:
            tete->x--;
            break;
        case KEY_RIGHT:
            tete->x++;
            break;

        case 'z':
            tete2->y--;
            break;
        case 's':
            tete2->y++;
            break;
        case 'q':
            tete2->x--;
            break;
        case 'd':
            tete2->x++;
            break;

        default:
            break;
        }

        // Mettre à jour les coordonnées de la tête du serpent en fonction de la touche pressée

        // Vérifier si la tête du serpent est en dehors de la grille
        if (!est_dans_grille(tete->x, tete->y, n, m))
        {
            endwin();
            printf("\n\n*Bordure touchée par %s !*\n", joueur2);
            printf("\n\n*Fin du jeu!*\n");
            printf("\n\n*Au revoir !*\n");
            return EXIT_SUCCESS;
        }

        if (!est_dans_grille(tete2->x, tete2->y, n, m))
        {
            endwin();
            printf("\n\n*Bordure touchée par %s !*\n", joueur1);
            printf("\n\n*Fin du jeu!*\n");
            printf("\n\n*Au revoir !*\n");
            return EXIT_SUCCESS;
        }

        // Vérifier si la tête du serpent a rencontré un fruit
        if (pos_tete_fruit(tete, matrice))
        {

            couleur = rand() % 4 + 44;
            grille_tirage_fruit(grille);
            while (apparition_fruit_serpent(grille, matrice))
            {
                grille_tirage_fruit(grille);
            }
            for (int i = 0; i <= (rand() % 5 + 1); i++)
            {

                struct maillon_section *tmp = nouveau_maillon_section(couleur, 1);
                ajouter_queue_section(tete->liste_section, tmp);
                score++;
            }
        }

        if (pos_tete_fruit(tete2, matrice))
        {

            couleur = rand() % 4 + 44;
            grille_tirage_fruit(grille);
            while (apparition_fruit_serpent(grille, matrice))
            {
                grille_tirage_fruit(grille);
            }
            for (int i = 0; i <= (rand() % 4); i++)
            {

                struct maillon_section *tmp = nouveau_maillon_section(couleur, 1);
                ajouter_queue_section(tete2->liste_section, tmp);
                score2++;
            }
        }

        // Vérifier si la tête du serpent est entrée en collision avec son propre corps
        if (ch == 'z' || ch == 's' || ch == 'q' || ch == 'd')
        {
            if (collision_corps_serpent(tete2, matrice))
            {
                endwin();
                printf("\n\nCollision corps %s!\n", joueur1);
                printf("\n\n*Fin du jeu!*\n");
                printf("\n\nAu revoir !\n");
                return EXIT_SUCCESS;
            }
        }

        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
        {
            if (collision_corps_serpent(tete, matrice))
            {
                endwin();
                printf("\n\nCollision corps %s !\n", joueur2);
                printf("\n\n*Fin du jeu!*\n");
                printf("\n\nAu revoir !\n");
                return EXIT_SUCCESS;
            }
        }

        // Vider la matrice avant de remplir les nouvelles positions du serpent

        // Ajouter le mouvement actuel à la liste des mouvements du serpent
        if (ch == 'z' || ch == 's' || ch == 'q' || ch == 'd')
        {
            ajouter_tete_mouvement(tete2->liste_mouvement, nouveau_maillon_mouvement(prevx2, prevy2, ch));
            ch_dern2 = ch;
        }

        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
        {
            ajouter_tete_mouvement(tete->liste_mouvement, nouveau_maillon_mouvement(prevx, prevy, ch));
            ch_dern = ch;
        }

        // Mettre à jour la grille avec les nouvelles positions du serpent et du fruit
        grille_remplir_2(grille, tete, tete2, matrice);

        printf("\n score de %s : %d\33[1E score de %s : %d\n", joueur1 ,score2, joueur2 ,score);

        fflush(stdout);

    } while (ch != '#');

    // Nettoyer et libérer la mémoire
    grille_desallouer(&grille);
    matrice_desallouer(&matrice);
    struct liste_section **tmp = &tete->liste_section;
    detruire_liste_section(tmp);

    struct liste_mouvement **tmp2 = &tete->liste_mouvement;
    detruire_liste_mouvement(tmp2);
    free(tete);

    struct liste_section **tmp3 = &tete2->liste_section;
    detruire_liste_section(tmp3);

    struct liste_mouvement **tmp4 = &tete2->liste_mouvement;
    detruire_liste_mouvement(tmp4);
    free(tete2);

    printf("\n\n*Fin de jeu !*\n");
    printf("\n\n*Au revoir !*\n");

    return EXIT_SUCCESS;
}
