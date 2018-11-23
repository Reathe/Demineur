#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "structure.h"

void clearBuffer()
//vide le buffer de l'entrée standard
{
    while (getchar() != '\n')
        ;
}

bool checkBuffer()
//retourne Faux si le buffer n'est pas vide et Vrai sinon
{
    if (getchar() != '\n')
    {
        clearBuffer();
        return Faux;
    }
    return Vrai;
}

int Partie(int largeur, int longueur, int nbMines)
{
    system("/bin/stty -icanon"); //Permet d'éviter d'appuyer sur Enter
    char dir;
    TTMines *T;
    TCurseur *C;
    bool defaite = Faux;
    C = consCurseur();
    //Debut de partie (avant que les bombes soient générées)
    while (dir != 'g' && dir!='c' && !defaite && nombCasesRest(T) != nombMines(T))
    {
        system("clear");
        printf("Nombre de mines restantes : %d\n", nombMines(T) - nombDrapeau(T));
        aff_TTMines(T, C, Debut);
        printf("Lin=%d, col=%d\n", Lin(C) + 1, Col(C) + 1);
        dir = getc(stdin);
        instruction(T, C, dir, &defaite);
    }

    T = init_TTMines(largeur, longueur, nbMines);
    
    while (dir != 'g' && !defaite && nombCasesRest(T) != nombMines(T))
    {
        system("clear");
        printf("Nombre de mines restantes : %d\n", nombMines(T) - nombDrapeau(T));
        aff_TTMines(T, C, Milieu);
        printf("Lin=%d, col=%d\n", Lin(C) + 1, Col(C) + 1);
        dir = getc(stdin);
        instruction(T, C, dir, &defaite);
    }
    system("/bin/stty cooked"); //Remet les paramètres par défaut de la console
    system("clear");
    aff_TTMines(T, C, Fin);
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
    bool bufferVide;
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
            bufferVide = checkBuffer();
        } while (*longueur < 4 || *longueur > 256 || !bufferVide);
        do
        {
            printf("Entrez la largeur du champ de mines (nombre de lignes)\n");
            scanf("%d", largeur);
            bufferVide = checkBuffer();
        } while (*largeur < 4 || *largeur > 256 || !bufferVide);
        do
        {
            printf("Entrez le nombre de mines\n");
            scanf("%d", nbMines);
            bufferVide = checkBuffer();
        } while (*nbMines < 1 || *nbMines >= (*largeur) * (*longueur) - 9 || !bufferVide);
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
