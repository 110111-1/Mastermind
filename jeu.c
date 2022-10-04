#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void print_tab(int tab[], int dim) {
    int i;
    for(i=0; i<dim; ++i) {
        printf("%d ",tab[i]);
    }
    printf("\n");
}
void tirage(int tab[], int dim, int nbCouleurs) { //tirage aléatoire
    int NbSec, vali, i;
    double valf;

    NbSec = time(NULL); /* nombre de secondes écoulées depuis le 1/1/70 */
    srand(NbSec); /* initialisation du générateur pseudo-aléatoire */
    vali = rand(); /* un coup pour rien. Le premier n'est pas aléatoire */

    for (i = 0; i < dim; i++) {
        valf = rand()/(RAND_MAX + 1.0); /* nombre flottant compris entre 0.0
                et 0.9999999 */
        vali = (int)(valf * nbCouleurs)+1; /* nombre entier compris entre 1 et NBCOULEURS */
        tab[i] = vali;
    }
}

int entree(int dim, int essai[],char charNbCouleurs) { //Vérification de la saisie
    /*
    * la fonction prend une chaine de caractère puis
        *  verifie :
            *  la taille de la combinaison et redemande une saisie si :
            * la combinaison est trop grande ou trop petite --> pas egale au nombre de cases choisi
            * l'utilisateur entre un nombre inferieur ou superieur au nombre de couleur choisi
            * l'utilisateur entre autre chose qu'un nombre --> symbole ou lettre

        * puis convertit chaque char en int pour les placer dans le tableau essai
    */
    char *saisie;
    int i, test, nb;
    saisie = malloc(dim*sizeof(char));
    if(saisie == NULL)
        exit(-1);
    do {
        printf("Saisir votre combinaison : ");
        scanf("%s",saisie);
        nb = 0;
        test = 0;
        for (i=0; saisie[i]!='\0'; i++) {
            nb = nb+1;
        }
        if(nb!=dim) {
            test=-1;
        }
        for(i=0; saisie[i]!='\0'; i++) {
            if((saisie[i]<'0')||(saisie[i]>charNbCouleurs)) {
                test=-1;
            }
        }
    } while(test==-1);
    for(i=0; i<dim; i++) {
        essai[i]=saisie[i]-'0';
    }
    return 0;
}

void analyse(int ref[], int essai[], int dim, int *BienPlaces, int *MalPlaces ) {
    /*
    * la fonction :
        * gère les couleurs bien placé
            * un jeton ne sert qu'une fois :
                * les biens placés sont prioritaires et remplacés par -1 dans REfTemp
                * mal placé : une fois compté toutes les occurences sont remplacés par -1 dans RefTemp - évite les doublons dans les comptes
        * affiche à l'utilisateur
            * le nombre de bien placé et de mal placé
    */
    int i, j;
    int RefTmp[dim];
    *BienPlaces=0;
    *MalPlaces=0;
    for(i=0; i<dim; i++) { //BienPlacé
        if(essai[i]==ref[i]) {
            *BienPlaces = *BienPlaces+1;
            RefTmp[i]=-1;
        } else {
            RefTmp[i]=ref[i];
        }
    }
    //Gere les occurences de mal places
    int n=0;
    for (i=0; i<dim; i++) {
        n=-1;
        for(j=0; j<dim; j++) {
            if(ref[i]==RefTmp[j]) {
                n=n+1;
                if(n!=0) {
                    RefTmp[j] = -1;
                }
            }
        }
    }
    for(i=0; i<dim; i++) { // Gere les mal place
        for(j=0; j<dim; j++) {
            if(essai[i]==RefTmp[j]) {
                *MalPlaces = *MalPlaces+1;
            }
        }
    }

    printf("Bien places \t: %d\n",*BienPlaces);
    printf("Mal places \t: %d\n",*MalPlaces);
}

int partie(int dim, int nbCoup, int nbCouleurs, char charNbCouleurs) {
    /*
    * Les parametres de la fonction permettent de gere plusieurs niveaux :
        * dim : nbCase
        * nbCoup
        * nbCouleur
        * charNbCouleur permet de gerer la saisie
    * la fonction :
        * ininitalise les tableaux et les valeurs
        * lance la fonction tirage pour avoir une combinaison
        * fait une boucle do while pour gerer le nombre de coup tant que la combinaison n'est pas trouvee ou que nbcoup nest pas atteint
            * lance la fonction entree
            * lance la fonction analyse
        * en fin de programme :
            * affiche la solution
            * libere l'espace memoire occuper par les tableaux ref et essai
    */
    int *ref, *essai;
    int BienPlaces=0, MalPlaces=0,i=0, status=0;
    ref=(int *)malloc(dim*sizeof(int));
    essai=(int *)malloc(dim*sizeof(int));
    if(ref==NULL || essai==NULL) {
        printf("pas assez de memoire\n");
        exit(-1);
    }
    tirage(ref,dim,nbCouleurs);
    do {
        entree(dim,essai,charNbCouleurs);
        analyse(ref, essai, dim, &BienPlaces, &MalPlaces);
        i=i+1;
        printf("Nb coups restants : %d\n",nbCoup-i);
        if(BienPlaces==dim) {
            status = 1;
            printf("BRAVO !! \nVous avez gagnez\n");
        }
    } while(i<nbCoup&&status==0);
    if (status==0) {
        printf("Vous avez Perdu....\n");
        printf("La bonne combinaison etait =\t");
    }
    //printf("\n\n\nFin de la partie \n");

    print_tab(ref,dim);
    printf("\n");
    free(ref);
    free(essai);
    return 0;
}
void reglesDuJeu() {
    printf("\n_____REGLE DU JEU _____\n");
    printf("Le but est de deviner, par deductions successives, la couleur et la position des 5 pions caches derriere un ecran.C'est une question de convention prealable.\n");
    printf(" Les debutants peuvent adopter une formule moins difficile en ne cachant que 3 ou 4 pions et en n'utilisant que 6 couleurs au lieu de 8.\n");
    printf("\n");
    printf("Le niveau 1 : DEBUTANT \n");
    printf("3 pions caches, 8 tentatives possibles, 5 couleurs - nombre 0,1,2,3,4 \n");
    printf("Le niveau 2 : CLASSIQUE\n");
    printf("5 pions caches, 12 tentatives possibles, 8 couleurs - nombre 0,1,2,3,4,6,7,8 \n");
    printf("Le niveau 3 : EXPERT\n");
    printf("8 pions caches, 12 tentatives possibles, 8 couleurs - nombre 0,1,2,3,4,6,7,8 \n");
    printf("______________________\n");
}

