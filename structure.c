#include <stdio.h>
#include <stdlib.h>
typedef struct {
    //Le tableau 2d de mines allant de [1][1] à [n][n]
    int ** TMines;
    int n,lin,col;
} TTMines;

TTMines* init_TTMines (TTMines* T ,char* difficulte){
    int nbombe;
    T=malloc(sizeof(TTMines));
    T->lin=T->col=1;
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
    T->TMines=malloc((T->n+2)*sizeof(int*));

    for (int i = 0; i < ((*T).n)+2; i++) {
        T->TMines[i]= malloc((T->n+2)*sizeof(int));
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
    for(int i = 1; i <= (T->n); i++) {
        for(int j = 1; j <= T->n; j++) {
            if (i==T->lin && j==T->col){
                printf("* ");
            } else if (T->TMines[i][j]==0) {
                printf("%c ",0x10);
            }else 
                printf("%d ",T->TMines[i][j]);
        }
        printf("\n");
    }
}

void deplace_curseur (TTMines * T,char dir){
    switch (dir){
        case 'z': 
            if (T->lin>1)
                T->lin--;
            break;
        case 'q': 
            if (T->col>1)
                T->lin--;
            break;
        case 's': 
            if (T->lin < T->n-1)
                T->lin--;
            break;
        case 'd': 
            if (T->col < T->n-1)
                T->lin--;
            break;

    }
}