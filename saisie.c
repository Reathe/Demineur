#include <stdio.h>
#include "structure.h"
#include "GestionProfiles/tadlst.h"
#include "GestionProfiles/tadpro.h"
#include "GestionProfiles/io.h"
#include "string.h"

void clearBuffer()
//vide le buffer de l'entree standard
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
        return false;
    }
    return true;
}

void ChoixTaille(int *largeur, int *longueur, int *nbMines)
//saisie la taille de la grille et le nombre de mines
{
    char diff;
    bool bufferVide;
    system("clear");
    do
    {
        printf("Choisissez la difficulte: Facile (f), Moyen (m), Difficile (d), ou personalise (p)\n");
        diff = getchar();
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
    bool res;
    do
    {
        clearBuffer();
        printf("Rejouer ? (o/n)\n");
        scanf("%c", &rejouer);
        clearBuffer();
        if (rejouer == 'o')
            res = true;
        else if (rejouer == 'n')
            res = false;
        else
            printf("Saisie invalide.\n");
    } while (rejouer != 'o' && rejouer != 'n');
    return res;
}
char *getFilename(int largeur, int longueur, int nbMines)
//restitue le nom du fichier pour une taille de grille et un nombre de mine donne
{
    char ch[30];
    sprintf(ch, "save/%d_%d_%d.txt", largeur, longueur, nbMines);
    char *res = calloc(1 + strlen(ch), sizeof(char));
    strcpy(res, ch);
    return res;
}
void ScanNom(char *nom)
//saisie le nom et prenom d'un joueur
{
    printf("Entrez votre nom\n");
    clearBuffer();
    scanf("%s", nom);
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
bool FichierExiste(char *FileName)
//retourne vrai si le fichier existe et faux sinon
{
    FILE *fichier = fopen(FileName, "r+");
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
//Demande à l'utilisateur s'il veut enregistrer son score, si oui, le fait.
{
    char enregistrer;
    char nom[sz];
    char *FileName = getFilename(largeur, longueur, nbMines);
    lst_t L = consVide();
    int classement = 1;

    if (FichierExiste(FileName))
        L = fscanLst(FileName);

    classement = Classement(score, L);
    printf("Vous avez fait le demineur %dx%d avec %d bombes en %d secondes. Vous etes classe numero %d Voulez vous enregister votre score ? (o/n)\n",
           largeur, longueur, nbMines, score, classement);

    do
    {
        scanf("%c", &enregistrer);
        if (enregistrer == 'o')
        {
            ScanNom(nom);
            profile_t *pro = consProfile(nom, score);
            ins(&L, pro, classement);
            fprintLst(L, FileName);
        }
    } while (enregistrer != 'o' && enregistrer != 'n');
    free(FileName);
    freeLst(&L);
}
void AfficherClassement(int largeur, int longueur, int nbMines)
//affiche le classement pour une largeur, longueur et un nb de mine donne
{
    system("clear");
    char *filename = getFilename(largeur, longueur, nbMines);
    if (!FichierExiste(filename))
    {
        printf("Il n'y a aucune donnee pour le classement demande.\n");
        free(filename);
    }
    else
    {
        lst_t L = consVide();
        L = fscanLst(filename);
        printLst(L);
        free(filename);
        freeLst(&L);
    }
    printf("\n");
}

int ChoixMenu()
//affiche le menu et saisie la reponse de l'utilisateur
{
    int choix = -1;
    do
    {
        printf("Que voulez-vous faire ?\n\
1. Jouer\n\
2. Consulter les scores\n\
3. Consulter les règles\n\
4. Quitter\n");
        scanf("%d", &choix);
        clearBuffer();
        if (choix < 1 || choix > 4)
            printf("Saisie invalide.\n");
    } while (choix < 1 || choix > 4);
    return choix;
}

void Bienvenue()
{
    printf("Bienvenue dans El Famoso Demineur © Boucksom/Bachourian.\n");
}
void Regles()
{
    printf("Les règles sont simples. Survivez, ou mourrez. Vous devez trouver l'emplacement de toutes les mines sans tout faire exploser...\
Vos outils seront les suivants: \n\
-Votre clavier \n\
-votre ordinateur (sous linux pour la meilleure experience utilsateur)\n\
-un cerveau\n\
Même si ça n'est pas donne à tout le monde, nous auront besoin de ces trois choses !\n\
Vous utiliserez les fleches (ou zqsd) pour vous deplacer,la touche %c pour decouvrir une case, la touche %c pour poser un drapeau, et la touche %c pour quitter.\n\n",
           DecouvrirCase, PoserDrapeau, Quitter);
}