#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h> // Ajout pour la fonction strcpy
#include <unistd.h> // Ajout pour la fonction sleep
#include <ncurses.h>

#include "serpent.h"
#include "fonction_jeu.h"
#include "matrice.h"
#include "grille.h"
#include "liste_section.h"
#include "liste_mouvement.h"
extern int score;
// Fonction principale pour jouer au jeu du serpent
int jouer_serpent_3(int n, int m, int delai)
{
    int couleur, ch, ch_dern = 0; // Variable pour stocker la touche pressée par l'utilisateur

    int prevx = 0, prevy = 0; // Variables pour stocker les coordonnées précédentes de la tête du serpent

    int cpt = 0;

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
    tete->x = n / 2;
    tete->y = m / 2;
    tete->couleur = 46;
    tete->liste_section = ls;
    tete->liste_mouvement = lm;

    // Initialiser la position du fruit dans la grille
    grille_tirage_fruit(grille);

    // Initialiser la position de la tête du serpent dans la grille

    // Initialiser ncurses

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    ch_dern = KEY_RIGHT;
    grille_remplir(grille, tete, matrice);

    halfdelay(delai);

    cpt = 0;
    while (0 == 0)
    {

        while (tete->x != 0)
        { // placer dans la case 0,0

            // Sauvegarder les coordonnées précédentes de la tête du serpent
            prevy = tete->y;
            prevx = tete->x;
            // Détecter la touche pressée par l'utilisateur
            ch = getch();

            ch = test_retour(ch, ch_dern);

            if (ch == -1)
            { /* Si aucune touche utilisee, getch renvoie -1 */
                /* Comme aucune touche n'a ete utilisee
                le programme peut faire autre chose */
                ch = ch_dern;
            }

            ch = KEY_LEFT;

            if (cpt == 1)
            {
                ch = KEY_UP;
                cpt++;
            }

            else
            {
                /* Ici une touche a ete utilisee, getch a renvoyee son code
                le programme peut repondre a l'utilisateur du clavier*/
                ch_dern = ch; /* Par exemple ic, on sauvegarde la dernière touche utilisee pour l'afficher*/
            }

            // Mettre à jour les coordonnées de la tête du serpent en fonction de la touche pressée

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

            default:
                break;
            }

            // Vérifier si la tête du serpent est en dehors de la grille
            if (!est_dans_grille(tete->x, tete->y, n, m))
            {
                endwin();
                printf("\n\n*Bordure touchée !*\n");
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

            // Vérifier si la tête du serpent est entrée en collision avec son propre corps

            if (collision_corps_serpent(tete, matrice))
            {
                endwin();
                printf("\n\nCollision corps !\n");
                printf("\n\nAu revoir !\n");
                return EXIT_SUCCESS;
            }

            // Vider la matrice avant de remplir les nouvelles positions du serpent

            // Ajouter le mouvement actuel à la liste des mouvements du serpent
            ajouter_tete_mouvement(tete->liste_mouvement, nouveau_maillon_mouvement(prevx, prevy, ch));

            // Mettre à jour la grille avec les nouvelles positions du serpent et du fruit
            grille_remplir(grille, tete, matrice);
            printf("\n score : %d", score);

            fflush(stdout);

            // Attendre un court délai
        }

        cpt = 0;

        while ((tete->x != n - 1) || (tete->y != 1))
        {

            while (tete->y != m - 1)
            {
                // Sauvegarder les coordonnées précédentes de la tête du serpent
                prevy = tete->y;
                prevx = tete->x;
                // Détecter la touche pressée par l'utilisateur
                ch = getch();

                ch = test_retour(ch, ch_dern);

                if (ch == -1)
                { /* Si aucune touche utilisee, getch renvoie -1 */
                    /* Comme aucune touche n'a ete utilisee
                    le programme peut faire autre chose */
                    ch = ch_dern;
                }

                ch = KEY_DOWN;

                if (cpt == 1)
                {

                    ch = KEY_RIGHT;
                    cpt = 0;
                }

                else
                {
                    /* Ici une touche a ete utilisee, getch a renvoyee son code
                    le programme peut repondre a l'utilisateur du clavier*/
                    ch_dern = ch; /* Par exemple ic, on sauvegarde la dernière touche utilisee pour l'afficher*/
                }

                // Mettre à jour les coordonnées de la tête du serpent en fonction de la touche pressée

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

                default:
                    break;
                }

                // Vérifier si la tête du serpent est en dehors de la grille
                if (!est_dans_grille(tete->x, tete->y, n, m))
                {
                    endwin();
                    printf("\n\n*Bordure touchée !*\n");
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

                // Vérifier si la tête du serpent est entrée en collision avec son propre corps

                if (collision_corps_serpent(tete, matrice))
                {
                    endwin();
                    printf("\n\nCollision corps !\n");
                    printf("\n\nAu revoir !\n");
                    return EXIT_SUCCESS;
                }

                // Vider la matrice avant de remplir les nouvelles positions du serpent

                // Ajouter le mouvement actuel à la liste des mouvements du serpent
                ajouter_tete_mouvement(tete->liste_mouvement, nouveau_maillon_mouvement(prevx, prevy, ch));

                // Mettre à jour la grille avec les nouvelles positions du serpent et du fruit
                grille_remplir(grille, tete, matrice);
                printf("\n score : %d", score);

                fflush(stdout);

                // Attendre un court délai
            }

            while (tete->y != 1)
            {

                // Sauvegarder les coordonnées précédentes de la tête du serpent
                prevy = tete->y;
                prevx = tete->x;
                // Détecter la touche pressée par l'utilisateur
                ch = getch();

                ch = test_retour(ch, ch_dern);

                if (ch == -1)
                { /* Si aucune touche utilisee, getch renvoie -1 */
                    /* Comme aucune touche n'a ete utilisee
                    le programme peut faire autre chose */
                    ch = ch_dern;
                }

                ch = KEY_UP;

                if (cpt == 0)
                {
                    ch = KEY_RIGHT;
                    cpt++;
                }

                else
                {
                    /* Ici une touche a ete utilisee, getch a renvoyee son code
                    le programme peut repondre a l'utilisateur du clavier*/
                    ch_dern = ch; /* Par exemple ic, on sauvegarde la dernière touche utilisee pour l'afficher*/
                }

                // Mettre à jour les coordonnées de la tête du serpent en fonction de la touche pressée

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

                default:
                    break;
                }

                // Vérifier si la tête du serpent est en dehors de la grille
                if (!est_dans_grille(tete->x, tete->y, n, m))
                {
                    endwin();
                    printf("\n\n*Bordure touchée !*\n");
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

                // Vérifier si la tête du serpent est entrée en collision avec son propre corps

                if (collision_corps_serpent(tete, matrice))
                {
                    endwin();
                    printf("\n\nCollision corps !\n");
                    printf("\n\nAu revoir !\n");
                    return EXIT_SUCCESS;
                }

                // Vider la matrice avant de remplir les nouvelles positions du serpent

                // Ajouter le mouvement actuel à la liste des mouvements du serpent
                ajouter_tete_mouvement(tete->liste_mouvement, nouveau_maillon_mouvement(prevx, prevy, ch));

                // Mettre à jour la grille avec les nouvelles positions du serpent et du fruit
                grille_remplir(grille, tete, matrice);
                printf("\n score : %d", score);

                fflush(stdout);

                // Attendre un court délai
            }
        }
    }

    // Nettoyer et libérer la mémoire
    grille_desallouer(&grille);
    matrice_desallouer(&matrice);
    struct liste_section **tmp = &tete->liste_section;
    detruire_liste_section(tmp);

    struct liste_mouvement **tmp2 = &tete->liste_mouvement;
    detruire_liste_mouvement(tmp2);
    free(tete);

    // Terminer ncurses
    endwin();

    printf("\n\n*Fin de jeu !*\n");
    printf("\n\n*Au revoir !*\n");

    return EXIT_SUCCESS;
}
