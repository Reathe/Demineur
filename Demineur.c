#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "structure.h"

int Partie()
{
    char dir;
    TTMines *T;
    TCurseur *C;
    bool defaite = Faux;
    int largeur = 25;
    int longueur = 50;
    T = init_TTMines(largeur, longueur, largeur * longueur / 10);
    C = consCurseur();
    system("/bin/stty -icanon"); //Permet d'éviter d'appuyer sur Enter
    while (dir != 'g' && !defaite && nombCasesRest(T) != nombMines(T))
    {
        system("clear");
        printf("Nombre de mines restantes : %d\n", nombMines(T) - nombDrapeau(T));
        aff_TTMines(T, C);
        printf("Lin=%d, col=%d\n", Lin(C) + 1, Col(C) + 1);
        //scanf("%c",&dir);
        //fflush(stdin);
        dir = getc(stdin);
        T = instruction(T, C, dir, &defaite);
    }
    system("/bin/stty cooked");
    system("clear");
    aff_TTMines(T, C);
    if (defaite)
        printf("Vous avez perdu.\n");
    else if (nombCasesRest(T) == nombMines(T))
        printf("Vous avez gagné !\n");
    else if (dir == 'g')
        printf("Vous avez quitté la partie en cours.\n");
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
