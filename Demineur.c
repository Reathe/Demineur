#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "structure.h"

void clearBuffer()
//vide le buffer de l'entrée standard
{
    while (getchar() != '\n')
        ;
}

int Partie(int largeur, int longueur, int nbMines)
{
    char dir;
    TTMines *T;
    TCurseur *C;
    bool defaite = Faux;
    T = init_TTMines(largeur, longueur, nbMines);
    C = consCurseur();
    system("/bin/stty -icanon"); //Permet d'éviter d'appuyer sur Enter
    while (dir != 'g' && !defaite && nombCasesRest(T) != nombMines(T))
    {
        system("clear");
        printf("Nombre de mines restantes : %d\n", nombMines(T) - nombDrapeau(T));
        aff_TTMines(T, C, Faux);
        printf("Lin=%d, col=%d\n", Lin(C) + 1, Col(C) + 1);
        //scanf("%c",&dir);
        //fflush(stdin);
        dir = getc(stdin);
        instruction(T, C, dir, &defaite);
    }
    system("/bin/stty cooked"); //Remet les paramètres par défaut de la console
    system("clear");
    aff_TTMines(T, C, Vrai);
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
void ChoixTaille(int *largeur, int *longueur, int *nbMines)
{
    char diff;
    //system("clear");
    do
    {
        printf("Choisissez la difficulte: Facile (f), Moyen (m), Difficile (d), ou personalise (p)\n");
        scanf("%c", &diff);
        clearBuffer();
    } while (diff != 'F' && diff != 'f' && diff != 'M' && diff != 'm' && diff != 'D' && diff != 'd' && diff != 'P' && diff != 'p');

    switch (diff)
    {
    case 'F':
    case 'f':
        *longueur = *largeur = 10;
        *nbMines = 12;
        break;
    case 'M':
    case 'm':
        *longueur = 50;
        *largeur = 30;
        *nbMines = 170;
        break;
    case 'D':
    case 'd':
        *longueur = 90;
        *largeur = 50;
        *nbMines = 600;
        break;
    case 'P':
    case 'p':
        *longueur = *largeur = *nbMines = -1;
        do
        {
            printf("Entrez la longueur du champ de mines (nombre de colonnes)\n");
            scanf("%d", longueur);
            clearBuffer();
        } while (*longueur <= 1 || *longueur > 10000); //si on rentre des caracteres non-numeriques,
        do                                             //longueur peut avoir une valeur tres grande
        {
            printf("Entrez la largeur du champ de mines (nombre de lignes)\n");
            scanf("%d", largeur);
            clearBuffer();
        } while (*largeur <= 1 || *largeur > 10000); //si on rentre des caracteres non-numeriques,
        do                                           //largeur peut avoir une valeur tres grande
        {
            printf("Entrez le nombre de mines\n");
            scanf("%d", nbMines);
            clearBuffer();
        } while (*nbMines < 1 || *nbMines > 10000 || *nbMines >= (*largeur) * (*longueur)); //idem qu'au dessus
        break;
    }
}
int main()
{
    srand(time(NULL));
    int largeur, longueur, nbMines;
    ChoixTaille(&largeur, &longueur, &nbMines);
    Partie(largeur, longueur, nbMines);
    exit(0);
}
