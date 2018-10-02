#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.c"
#include "structure.c"

/*//Fonctions disponibles
TTMines* init_TTMines (TTMines* T ,char* difficulte);
void free_TTMines(TTMines* T);
void aff_TTMines (TTMines* T);
int somme_autour(int t[][],int lin,int col);
TTMines * deplace_curseur (TTMines * T,char dir);
//Fin*/

int main()
{
    srand(time(NULL));
    char dir;
    TTMines *T;
    T = init_TTMines(T, "");
    while (dir != 'g')
    {
        system("clear");
        aff_TTMines(T);
        printf("Lin=%d, col=%d\n", T->lin, T->col);
        //scanf("%c",&dir);
        fflush(stdin);
        dir = getc(stdin);
        T = deplace_curseur(T, dir);
    }

    free_TTMines(T);
    //aff_TTMines(T);
    exit(0);
}