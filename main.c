#include <stdio.h>
#include <stdlib.h>
#include "jeu.h" //toutes les fonctions du jeu sauf le menu pour pouvoir lancer de nouvelles configurations de parties

int main() {

    int choix;
    do {
        printf("\n\t\t   JEU MASTERMIND\n");
        printf("\t\t\tMENU\n");
        printf("0\t: Regle du jeu\n");
        printf("1\t: Niveau DEBUTANT  : 3 pions caches, 8 tentatives possibles, 5 couleurs - nombre 0,1,2,3,4\n");
        printf("2\t: Niveau CLASSIQUE : 5 pions caches, 12 tentatives possibles, 8 couleurs - nombre 0,1,2,3,4,6,7\n");
        printf("3\t: Niveau EXPERT    : 8 pions caches, 12 tentatives possibles, 9 couleurs - nombre 0,1,2,3,4,6,7,8\n");
        printf("4\t: Quitter \n");
        printf("Choisir le numero correspondant a votre choix : ");
        scanf("%d",&choix);
        switch (choix) {
        case 0 :
            reglesDuJeu();
            break;
        case 1 :
            partie(3,10,4,'4');
            break;
        case 2 :
            partie(5,12,7,'7');
            break;
        case 3 :
            partie(8,12,8,'8');
            break;
        case 4 :
            printf("Au revoir\n");
            break;
        default :
            printf("erreur de saisie");
            break;
        }
    } while(choix != 4);
    return 0;
}
