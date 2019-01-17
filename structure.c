#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

TTMines *consTTMines(int largeur, int longueur, int nbombe)
//Construit un TTMines avec une grille vide et sa largeur, longueur et nombre de bombe
{
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
//Initialise la grille du demineur
{
    int i, j;
    //Creation des mines//
    int *mines = calloc(Larg(T) * Long(T), sizeof(int));

    //On met des 2 à la case de depart et ses voisines pour ne pas y mettre de bombe
    remplirCaseEtVoisines(mines, C, 2, Larg(T), Long(T));

    int lin, col;
    for (i = 0; i < nombMines(T); i++)
    {
        do
        {
            lin = rand() % (Larg(T));
            col = rand() % (Long(T));
        } while (mines[col + lin * Long(T)] == 1 || mines[col + lin * Long(T)] == 2);
        mines[col + lin * Long(T)] = 1;
    }

    //On remet des 0 à la place des 2
    remplirCaseEtVoisines(mines, C, 0, Larg(T), Long(T));

    //Copie des mines dans la structure de donnees
    for (i = 0; i < Larg(T); i++)
        for (j = 0; j < Long(T); j++)
            if (mines[j + i * Long(T)] == 1)
                modifTabCase(T, i, j, 'M');
            else
                modifTabCase(T, i, j, '0' + somme_autour(mines, i, j, Larg(T), Long(T)));
    free(mines);
}

void aff_TTMines(TTMines *T, TCurseur *C, TMomentPartie moment)
//Affiche la grille avec le curseur en fonction du moement de la partie
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
            }
            else if (moment == Debut)
            {
                if (valTabVisible(T, i, j) == Drapeau)
                    printf(charDrapeau);
                else
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
