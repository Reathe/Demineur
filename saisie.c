#include <stdio.h>
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

void ChoixTaille(int *largeur, int *longueur, int *nbMines)
//saisie la taille de la grille et le nombre de mines
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

void getFilename(int largeur, int longueur, int nbMines, char *fileName)
//restitue le nom du fichier pour une taille de grille et un nombre de mine donné
{
    sprintf(fileName, "%d_%d_%d.txt", largeur, longueur, nbMines);
}

void Bienvenue()
{
    printf("Bienvenue dans El Famoso Démineur © Boucksom/Bachourian.\n");
}
void Regles()
{
    printf("Les règles sont simples. Survivez, ou mourrez. Vous devez trouver l'emplacement de toutes les mines sans tout faire exploser...\
Vos outils seront les suivants: \n\
-Votre clavier \n\
-votre ordinateur (sous linux pour la meilleure expérience utilsateur)\n\
-un cerveau\n\
Même si ça n'est pas donné à tout le monde, nous auront besoin de ces trois choses !\n\
Vous utiliserez les fleches (ou zqsd) pour vous deplacer,la touche %c pour découvrir une case, la touche %c pour poser un drapeau, et la touche %c pour quitter.\n\n",
           DecouvrirCase, PoserDrapeau, Quitter);
}