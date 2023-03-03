#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Définir les constantes M et N

const int M = 9;
const int N = 9;

// Définir les constantes HORIZ et VERT qui correspondent aux sens de parcours de la grille (ligne ou colonne)

const int HORIZ = 0;
const int VERT = 1;

// Définir la fonction print() qui prend en paramètre la grille et qui affiche la grille

void print(int grille[M][N]){
    int i, j;
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
            printf("%d ", grille[i][j]);
        }
        printf("\n");
    }
}

// Définir la fonction generer() qui prend en paramètre la grille et qui renvoie le nombre d'éléments non nuls

int generer(int grille[M][N]){
    int i, j, k;
    int remplissage = 0;
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
            k = rand() % 2;
            if (k == 1){
                grille[i][j] = rand() % 9 + 1;
                remplissage++;
            }
        }
    }
    return remplissage;
}

// Définir la fonction verifierLigneColonne() qui vérifie si chaque valeur de la ligne ou de la colonne est présente une et une seule fois. La fonction prend en paramètre la grille, un indice i et un sens (HORIZ ou VERT). La fonction renvoie 1 si chaque valeur de la ligne ou de la colonne est présente une et une seule fois, 0 sinon.

int verifierLigneColonne(int grille[M][N], int i, int sens){
    int j;
    int tab[9] = {0};
    if (sens == HORIZ){
        for (j = 0; j < N; j++){
            if (grille[i][j] != 0){
                tab[grille[i][j] - 1] = 1;
            }
        }
    }
    else{
        for (j = 0; j < M; j++){
            if (grille[j][i] != 0){
                tab[grille[j][i] - 1] = 1;
            }
        }
    }
    for (j = 0; j < 9; j++){
        if (tab[j] == 0){
            return 0;
        }
    }
    return 1;
}

// Définir la fonction verifierRegion() qui prend en paramètre deux indices k et l qui correspondent à la région (k,l) et qui renvoie 1 si chaque valeur de la région est présente une et une seule fois, 0 sinon.

int verifierRegion(int grille[M][N], int k, int l){
    int i, j;
    int tab[9] = {0};
    for (i = 3 * (k / 3); i < 3 * (k / 3) + 3; i++){
        for (j = 3 * (l / 3); j < 3 * (l / 3) + 3; j++){
            if (grille[i][j] != 0){
                tab[grille[i][j] - 1] = 1;
            }
        }
    }
    for (i = 0; i < 9; i++){
        if (tab[i] == 0){
            return 0;
        }
    }
    return 1;
}


// Définir la fonction saisir() qui demande à l'utilisateur de saisir au clavier les indices i et j et la valeur v à placer à l'emplacement (i,j). La fonction doit vérifier la validité des indices et de la valeur avec la fonction verifierLigneColonne() et verifierRegion(). La fonction renvoie 1 si la valeur a été placée, 0 sinon.

int saisir(int grille[M][N]){
    int i, j, v;
    printf("Saisir i : ");
    scanf("%d", &i);
    printf("Saisir j : ");
    scanf("%d", &j);
    printf("Saisir v : ");
    scanf("%d", &v);
    if (i >= 0 && i < M && j >= 0 && j < N && v >= 1 && v <= 9){
        if (verifierLigneColonne(grille, i, 0) == 1 && verifierLigneColonne(grille, j, 1) == 1 && verifierRegion(grille, i, j) == 1){
            grille[i][j] = v;
            return 1;
        }
    }
    return 0;
}



// Définir la fonction resolue() qui prend en paramètre la grille et qui renvoie 1 si la grille est résolue, 0 sinon. Une grille est résolue si elle est correctement remplie et si chaque valeur de la grille est présente une et une seule fois par ligne, par colonne et par région.

int resolue(int grille[M][N]){
    int i, j;
    for (i = 0; i < M; i++){
        if (verifierLigneColonne(grille, i, 0) == 0){
            return 0;
        }
    }
    for (i = 0; i < M; i++){
        if (verifierLigneColonne(grille, i, 1) == 0){
            return 0;
        }
    }
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
            if (verifierRegion(grille, i, j) == 0){
                return 0;
            }
        }
    }
    return 1;
}

//Écrire la fonction verifierGrille() qui renvoie 1 si la grille est correctement remplie et 0 sinon

int verifierGrille(int grille[M][N]){
    int i, j;
    for (i = 0; i < M; i++){
        if (verifierLigneColonne(grille, i, 0) == 0){
            return 0;
        }
    }
    for (i = 0; i < M; i++){
        if (verifierLigneColonne(grille, i, 1) == 0){
            return 0;
        }
    }
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
            if (verifierRegion(grille, i, j) == 0){
                return 0;
            }
        }
    }
    return 1;
}

//Ecrire la fonction copie() qui copie des valeurs de la grille solution dans la grille à résoudre

void copie(int grille[M][N], int solution[M][N]){
    int i, j;
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
            grille[i][j] = solution[i][j];
        }
    }
}

//Ecrire la fonction afficherGrille() qui affiche la grille

void afficherGrille(int grille[M][N]){
    int i, j;
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
            printf("%d ", grille[i][j]);
        }
        printf("\n");
    }
}


//Écrire le programme principal, en supposant que la seule condition d’arrêt est la réussite du sudoku (ce test ne devra être fait que si nécessaire)


int main(){
    // Ne pas toucher le code entre les commentaires
    srand( time( NULL ) );


    int i, j, k;
    int solution[9][9];
    printf("SOLUTION");
    printf("\n");
    printf("---------------------------------");
    printf("\n");
    for(j=0;j<9; ++j)
    {
        for(i=0; i<9; ++i)
            solution[j][i] = (i + j*3 +j /3) %9 +1 ;
    }

    for(i=0;i<9; ++i)
    {
        for(j=0; j<9; ++j)
            printf("%d ", solution[i][j]);
        printf("\n");
    }
    printf("---------------------------------");
    printf("\n");
    //toucher le code entre les commentaires

    printf("%d",rand() % 2);

    /* 1. Afficher la grille solution
     * 2. Generer une grille vide et y placer des valeurs de la grille solution
     * 3. Afficher la grille à résoudre
     * 4. Tant que vérifierGrille() renvoie 0
     *     4.1. Demander à l'utilisateur de saisir une valeur
     *     4.2. Si saisir() renvoie 0, afficher un message d'erreur
     *     4.3. Sinon, afficher la grille avec la nouvelle valeur
     *     4.4. Si resoudre() renvoie 1, afficher la grille solution et un message de réussite du sudoku et quitter le programme
     *     4.5. Sinon, recommencer à l'étape 4.1
     */

    int grille[9][9];
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            grille[i][j] = 0;
        }
    }
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            if (rand() % 2 == 0){
                grille[i][j] = solution[i][j];
            }
        }
    }
    printf("GRILLE A RESOUDRE");
    printf("\n");
    printf("---------------------------------");
    printf("\n");
    afficherGrille(grille);
    printf("---------------------------------");
    printf("\n");
    while (verifierGrille(grille) == 0){
        if (saisir(grille) == 0){
            printf("Erreur de saisie");
            printf("\n");
            afficherGrille(grille);
        }
        else{
            afficherGrille(grille);
        }
        if (resolue(grille) == 1){
            printf("Sudoku resolu");
            printf("\n");
            copie(grille, solution);
            afficherGrille(grille);
            break;
        }
    }


    //Ne pas toucher au code ci dessous
    system("pause");
    return 0;
}



// Après avoir galérer pendant trop longtemps j'ai laissé le programme tel qui l'est.
// La seule solution que je trouve pour le faire peût fonctionner serai de comparer grille[i][j] avec solution[i][j].
// Si le résultat concorde alors on affiche v dans la grille mais je trouve que la vérification n'est pas authentique.
