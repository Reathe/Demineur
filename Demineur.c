#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"
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
    TCurseur *C;
    T = init_TTMines("moyen");
    C = consCurseur();
    system("/bin/stty -icanon"); //Permet d'éviter d'appuyer sur Enter
    while (dir != 'g')
    {
        system("clear");
        aff_TTMines(T, C);
        printf("Lin=%d, col=%d\n", Lin(C) + 1, Col(C) + 1);
        //scanf("%c",&dir);
        //fflush(stdin);
        dir = getc(stdin);
        T = instruction(T, C, dir);
    }
    system("/bin/stty cooked");
    free_TTMines(T);
    free_TCurseur(C);
    //aff_TTMines(T);
    exit(0);
}