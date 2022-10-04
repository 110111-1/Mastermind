#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
void tirage(int tab[], int dim, int nbCouleurs);
void print_tab(int [], int dim);
int entree(int dim, int essai[],char charNbCouleurs);
void analyse(int ref[], int essai[], int dim, int *BienPlaces, int *MalPlaces );
int partie(int dim, int nbCoup, int nbCouleurs, char charNbCouleurs);
void reglesDuJeu();

#endif // JEU_H_INCLUDED
