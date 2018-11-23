#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
//Changer la valeur à 0 si votre tableau est décalé... (parce que la bombe peut prendre 2 charactères à être affiché)
#define Decalage 1
TTMines *consTTMines(int largeur, int longueur, int nbombe){
    TTMines *T;
    T = malloc(sizeof(TTMines));
    T->largeur = largeur;
    T->longueur = longueur;
    T->nbMines = nbombe;
    T->nbDrapeau = 0;
    T->nbCasesRestantes = Larg(T) * Long(T);
    T->TMine = calloc(Larg(T) * Long(T), sizeof(TCase));
    return T;
}
void init_TTMines(TTMines *T, TCurseur *C)
{
    int i, j;
    //Création des mines//
    int *mines = calloc(Larg(T) * Long(T), sizeof(int));

    //On met des 2 à la case de départ et ses voisines pour ne pas y mettre de bombe
    remplirCaseEtVoisines(mines, C, 2, Larg(T), Long(T));

    int lin, col;
    for (i = 0; i < nombMines(T); i++)
    {
        do
        {
            lin = rand() % (Larg(T));
            col = rand() % (Long(T));
        } while (mines[col + lin * Long(T)] == 1 && mines[col + lin * Long(T)] == 2);
        mines[col + lin * Long(T)] = 1;
    }
    
    //On remet des 0 à la place des 2
    remplirCaseEtVoisines(mines, C, 0, Larg(T), Long(T));

    //Copie des mines dans la structure de données
    for (i = 0; i < Larg(T); i++)
        for (j = 0; j < Long(T); j++)
            if (mines[j + i * Long(T)] == 1)
                modifTabCase(T, i, j, 'M');
            else
                modifTabCase(T, i, j, '0' + somme_autour(mines, i, j, Larg(T), Long(T)));
    free(mines);
}

void remplirCaseEtVoisines(int *t, TCurseur *C, int val, int wid, int len)
{
    int i, j;
    for (i = Lin(C) - 1; i <= Lin(C) + 1; i++)
        for (j = Col(C) - 1; j <= Col(C) + 1; j++)
            if (i >= 0 && i < wid && j >= 0 && j < len)
                //Si à l'intérieur du tableau
                t[j + i * len] = val;
}

void decouvrir_case(TTMines *T, int lin, int col, bool *defaite)
{ //Rend la case visible à (lin,col) visible, et si c'est un 0,
    //elle rend visible toutes les cases autour jusqu'à avoir des chiffres
    if (valTabCase(T, lin, col) == '0')
        visible_0(T, lin, col);
    else
    {
        modifTabVisible(T, lin, col, Vrai);
        decrementNombCasesRest(T);
        if (valTabCase(T, lin, col) == 'M')
            *defaite = Vrai;
    }
}
void drapeau_case(TTMines *T, TCurseur *C)
{
    //Si la case est déjà un drapeau, l'enlève
    //Si c'est une case non Visible, met un drapeau
    if (valTabVisible(T, Lin(C), Col(C)) == Drapeau)
    {
        modifTabVisible(T, Lin(C), Col(C), Faux);
        modifNombDrapeau(T, nombDrapeau(T) - 1);
    }
    else if (valTabVisible(T, Lin(C), Col(C)) == Faux)
    {
        modifTabVisible(T, Lin(C), Col(C), Drapeau);
        modifNombDrapeau(T, nombDrapeau(T) + 1);
    }
}

void aff_TTMines(TTMines *T, TCurseur *C, TMomentPartie moment)
{
    int i, j;
    for (i = 0; i < (Larg(T)); i++)
    {
        if (Col(C) == 0 && i == Lin(C))
            printf("|");
        else
            printf(" ");
        for (j = 0; j < Long(T); j++)
        {
            if (moment == Milieu)
            {
                //Pendant la partie
                if (valTabVisible(T, i, j) == Faux)
                    printf(charCase);
                else if (valTabVisible(T, i, j) == Drapeau)
                    printf(charDrapeau);
                else if (valTabCase(T, i, j) == '0')
                    printf(charCaseOuverte);
                else
                    printf("%c", valTabCase(T, i, j));
            }
            else if (moment == Fin)
            {
                //Après la partie (si on affiche tout)
                if (valTabCase(T, i, j) == '0')
                    printf(charCaseOuverte);
                else if (valTabCase(T, i, j) == 'M')
                    printf(charMine);
                else
                    printf("%c", valTabCase(T, i, j));
                //L'affichage des bombes prend deux charactères
                //Donc on ne met pas l'espace d'après pour ne pas décaler le tableau
                if (valTabCase(T, i, j) != 'M' || Decalage)
                    printf(" ");
            }
            else if (moment == Debut)
            {
                printf(charCase);
            }
            
            if ((i == Lin(C) && j == Col(C)) || (i == Lin(C) && j == Col(C) - 1))
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void instruction(TTMines *T, TCurseur *C, char dir, bool *defaite)
{
    int lin = Lin(C),
        col = Col(C),
        wid = Larg(T),
        len = Long(T);
    switch (dir)
    {
    case 'A': //Fall through
    case 'z':
        if (lin > 0)
            modifCurseur(C, lin - 1, col);
        break;
    case 'D': //Fall through
    case 'q':
        if (col > 0)
            modifCurseur(C, lin, col - 1);
        break;
    case 'B': //Fall through
    case 's':
        if (lin < wid - 1)
            modifCurseur(C, lin + 1, col);
        break;
    case 'C': //Fall through
    case 'd':
        if (col < len - 1)
            modifCurseur(C, lin, col + 1);
        break;
    case 'c':
        if (valTabVisible(T, lin, col) && valTabCase(T, lin, col) != '0')
            //Si la case est déjà visible et
            //qu'elle est différente de '0'
            Verif_drapeau(T, C, defaite);
        else if (valTabVisible(T, lin, col) != Drapeau)
            decouvrir_case(T, lin, col, defaite);
        break;
    case 'f':
        drapeau_case(T, C);
        break;
    }
}
int somme_autour(int *t, int lin, int col, int wid, int len)
{
    //Retourne la somme des entiers autour de la case t[lin][col]
    int somme = 0, i, j;
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i >= 0 && i < wid && j >= 0 && j < len))
                //Si pas au milieu et à l'intérieur du tableau
                somme += t[j + i * len];
    return somme;
}
void visible_0(TTMines *T, int lin, int col)
{ //Rend visible toutes les cases
    int i, j;
    modifTabVisible(T, lin, col, Vrai);
    decrementNombCasesRest(T);
    if (valTabCase(T, lin, col) == '0')
    {
        for (i = lin - 1; i <= lin + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                if ((i != lin || j != col) && (i >= 0 && i < Larg(T) && j >= 0 && j < Long(T)) && (valTabVisible(T, i, j) == Faux))
                    //Si pas au milieu et si à l'intérieur du tableau et si la case est invisible
                    visible_0(T, i, j);
    }
}
void Verif_drapeau(TTMines *T, TCurseur *C, bool *defaite)
{
    //Si le nombre de drapeaux autour de la case est égal à sa valeur
    //On Rend visible toutes les cases autour de celle-ci
    int lin = Lin(C), col = Col(C), i, j;
    int nbDrapeau = 0;
    //Calcul du nombre de drapeaux autour de la case lin,col
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i >= 0 && i < Larg(T) && j >= 0 && j < Long(T)) && (valTabVisible(T, i, j) == Drapeau))
                //Si pas au milieu et à l'intérieur du tableau et si la case i,j est un drapeau
                nbDrapeau++;

    //Si le nombre de drapeaux est égal au nombre de drapeaux qu'indique la case
    //On rend visible toutes les cases autour
    if (nbDrapeau == valTabCase(T, Lin(C), Col(C)) - '0')
    {
        for (i = lin - 1; i <= lin + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                if ((i >= 0 && i < Larg(T) && j >= 0 && j < Long(T)) && valTabVisible(T, i, j) == Faux)
                    decouvrir_case(T, i, j, defaite);
    }
}

//Primitives Curseur
TCurseur *consCurseur()
{
    TCurseur *C = calloc(1, sizeof(TCurseur));
    return C;
}
void modifCurseur(TCurseur *C, int lin, int col)
{
    C->ligne = lin;
    C->colonne = col;
}
void free_TCurseur(TCurseur *C)
{
    free(C);
}
int Lin(TCurseur *C)
{
    return C->ligne;
}
int Col(TCurseur *C)
{
    return C->colonne;
}

//Primitives TTMines
//Consultation TTMines
int Larg(TTMines *T)
{
    return T->largeur;
}
int Long(TTMines *T)
{
    return T->longueur;
}
int valTabVisible(TTMines *T, int lin, int col)
{
    return T->TMine[col + lin * Long(T)].Visible;
}
char valTabCase(TTMines *T, int lin, int col)
{
    return T->TMine[col + lin * Long(T)].Case;
}
int nombMines(TTMines *T)
{
    return T->nbMines;
}
int nombDrapeau(TTMines *T)
{
    return T->nbDrapeau;
}
int nombCasesRest(TTMines *T)
{
    return T->nbCasesRestantes;
}

//Modif TTMines
void modifTabVisible(TTMines *T, int lin, int col, int nouvVal)
{
    T->TMine[col + lin * Long(T)].Visible = nouvVal;
}
void modifTabCase(TTMines *T, int lin, int col, char nouvVal)
{
    T->TMine[col + lin * Long(T)].Case = nouvVal;
}
void modifNombDrapeau(TTMines *T, int nouvVal)
{
    T->nbDrapeau = nouvVal;
}
void decrementNombCasesRest(TTMines *T)
{
    T->nbCasesRestantes--;
}

void free_TTMines(TTMines *T)
{
    free(T->TMine);
    free(T);
}
