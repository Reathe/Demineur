#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"

int Partie()
{
    char dir;
    TTMines *T;
    TCurseur *C;
    T = init_TTMines(50, 50,50*50/10);
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
    return 1;
}
int main()
{
    srand(time(NULL));
    Partie();
    //aff_TTMines(T);
    exit(0);
}
