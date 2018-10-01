#include <stdio.h>
#include <stdlib.h>
typedef struct {
    //Le tableau 2d de mines allant de [1][1] à [n][n]
    int ** TMines;
    int n;
} TTMines;

TTMines* init_TTMines (TTMines* T ,char* difficulte){
    int nbombe;
    T=(TTMines*) malloc(sizeof(TTMines));
    if (difficulte=="facile") {
        (*T).n=10;
        nbombe=10;
    }
    else if (difficulte=="moyen"){
        T->n=10;
        nbombe=10;
    } else if (difficulte=="difficile"){
        T->n=10;
        nbombe=10;
    } else {
        T->n=10;
        nbombe=10;
    }
    //Allocation de mémoire
    T->TMines=(int **)malloc((T->n+2)*sizeof(int*));

    for (int i = 0; i < ((*T).n)+2; i++) {
        T->TMines[i]=(int*) malloc((T->n+2)*sizeof(int));
    }
    //Initialisation à 0

    for(int i = 0; i < T->n+2; i++) {
        for(int j = 0; j < T->n+2; j++) {
            T->TMines[i][j]=0;
        }
    }
    
    //Création des bombes//
    
    for(int i = 0; i < nbombe; i++)
    {
        /* code */
    }
    return T;
}
void free_TTMines(TTMines* T){
    free(T->TMines);
    free(T);
}

void aff_TTMines (TTMines* T){
    for(int i = 0; i < (T->n)+2; i++) {
        for(int j = 0; j < T->n+2; j++) {
            
            if (T->TMines[i][j]==0) {
                printf("%c ",0x10);;
            }else 
                printf("%d ",T->TMines[i][j]);;
        }
        printf("\n");
    }
}