#include <stdio.h>
#include "structure.h"
#include "GestionProfiles/tadlst.h"
#include "GestionProfiles/tadpro.h"
#include "GestionProfiles/io.h"
#include "string.h"

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

bool Rejouer()
{
    char rejouer;
    clearBuffer();
    printf("Rejouer ? (o/n)\n");
    scanf("%c", &rejouer);
    clearBuffer();
    if (rejouer == 'o')
        return true;
    else
        return false;
}
char *getFilename(int largeur, int longueur, int nbMines)
//restitue le nom du fichier pour une taille de grille et un nombre de mine donné
{
    char ch[20];
    sprintf(ch, "%d_%d_%d.txt", largeur, longueur, nbMines);
    char *res = calloc(1 + strlen(ch), sizeof(char));
    strcpy(res, ch);
    return res;
}
void ScanNomPrenom(char *nom, char *prenom)
{
    printf("Entrez votre nom\n");
    clearBuffer();
    scanf("%s", nom);
    printf("Entrez votre prenom\n");
    clearBuffer();
    scanf("%s", prenom);
}
int Classement(int score, lst_t L)
//retourne le classement d'un joueur
{
    int Classement = 1;
    while (!estVide(L) && score > readScore(tete(L)))
    {
        Classement++;
        L = reste(L);
    }
    return Classement;
}
bool FichierExiste(char* FileName){
    FILE * fichier = fopen(FileName, "r+");
    if (fichier == NULL)
        /* Le fichier n'existe pas */
        return false;
    else
    {
        /* Le fichier existe et on le referme aussitôt */
        fclose(fichier);
        return true;
    }
}
void EnregistrerScore(int largeur, int longueur, int nbMines, int score)
{
    char enregister;
    char nom[sz], prenom[sz];
    char *FileName = getFilename(largeur, longueur, nbMines);
    lst_t L;
    int classement=1;

    printf("%s", FileName);
    if (FichierExiste(FileName))
        L = fscanLst(FileName);
    else
        L = consVide();
    classement = Classement(score, L);
    printf("Vous avez fait le démineur %dx%d avec %d bombes en %d secondes. Vous etes classe numéro %d Voulez vous enregister votre score ? (o/n)\n",
     largeur, longueur, nbMines, score/1000.0, classement);

    scanf("%c", &enregister);
    if (enregister == 'o')
    {
        ScanNomPrenom(nom, prenom);
        profile_t *pro = consProfile(nom, prenom, score);
        ins(&L, pro, classement);
        fprintLst(L, FileName);
    }
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