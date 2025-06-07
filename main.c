// CHAUVET Darren 12205390 / LI Christophe 12205895

#include "fonction_jeu.h"
#include "fonction_jeu_2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int score = 0;
int score2 = 0;

int main(int argc, char *argv[]) {

  srand(time(NULL)); // Initialise le générateur de nombres aléatoires avec une
                     // nouvelle graine basée sur l'heure actuelle

  int n, m;

  // Vérifie si le nombre d'arguments est correct
  if (argc != 5) {
    printf("Usage: %s <n> <m> <version> <speed>\n", argv[0]);
    return EXIT_FAILURE; // Quitte le programme si les arguments ne sont pas
                         // corrects
  }

  // Convertit les arguments en entiers pour les dimensions de la grille
  n = atoi(argv[1]);
  m = atoi(argv[2]);

  int jeu = atoi(argv[3]); // Récupère le paramètre indiquant le choix du jeu
                           // (peut-être pour sélectionner le type de jeu)
  int delai =
      atoi(argv[4]); // Récupère le paramètre indiquant le délai entre chaque
                     // mouvement (peut-être pour régler la vitesse du jeu)

  // Vérifie si la grille est carrée (même nombre de lignes et de colonnes)
  if (n != m) {
    printf("Usage: il faut une matrice a dimension carrée.\n <ligne> = "
           "<colonne>\n");
    return EXIT_FAILURE; // Quitte le programme si les arguments ne sont pas
                         // corrects
  }

  // Si le jeu choisi est le serpent, lance la fonction jouer_serpent avec les
  // paramètres donnés
  if (jeu == 1) {
    jouer_serpent(n, m, delai);
    printf("Score final: %d\n", score);
  }

  if (jeu == 3) {
    jouer_serpent_3(n, m, delai);
    printf("Score final: %d\n", score);
  }

  if (jeu == 2) {
    char joueur1[256], joueur2[256];
    printf("Nom du joueur 1: ");
    scanf("%s", joueur1);
    printf("Nom du joueur 2: ");
    scanf("%s", joueur2);

    jouer_serpent_2(n, m, delai, joueur1, joueur2);
    printf("Score de %s final: %d\n", joueur1, score2);
    printf("Score de %s final: %d\n", joueur2, score);
  }
  return EXIT_SUCCESS;
}
