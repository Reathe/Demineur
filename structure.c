#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "structure.h"

TTMines *init_TTMines(char *difficulte)
{
    TTMines *T;
    int nbombe, i, j;
    T = malloc(sizeof(TTMines));
    if (!strcmp(difficulte, "facile"))
    {
        T->largeur = 9;
        T->longueur = 9;
        nbombe = 10;
    }
    else if (!strcmp(difficulte, "moyen"))
    {
        T->largeur = 30;
        T->longueur = 40;
        nbombe = 150;
    }
    else if (!strcmp(difficulte, "difficile"))
    {
        T->largeur = 50;
        T->longueur = 50;
        nbombe = 250;
    }
    else
    {
        T->largeur = 100;
        T->longueur = 100;
        nbombe = 1000;
    }
    T->TMines = calloc(Larg(T), sizeof(char *));
    T->Visible = calloc(Larg(T), sizeof(int *));
    //Création des mines//
    int **mines = calloc(Larg(T), sizeof(*mines));
    for (i = 0; i < Larg(T); i++)
    {
        T->TMines[i] = calloc(Long(T), sizeof(char));
        T->Visible[i] = calloc(Long(T), sizeof(int));
        mines[i] = calloc(Long(T), sizeof(int));
    }

    //memset(mines, 0, sizeof(int) *(T->n*T->n + 4*T->n + 4) );
    int lin, col;
    for (i = 0; i < nbombe; i++)
    {
        do
        {
            lin = rand() % (Larg(T));
            col = rand() % (Long(T));
        } while (mines[lin][col] == 1);
        mines[lin][col] = 1;
    }

    for (i = 0; i < Larg(T); i++)
    {
        for (j = 0; j < Long(T); j++)
        {
            if (mines[i][j] == 1)
            {
                modifTabMines(T, i, j, 'M');
            }
            else
                modifTabMines(T, i, j, '0' + somme_autour(mines, i, j, Larg(T), Long(T)));
        }
    }

    for (i = 0; i < Larg(T); i++)
    {
        free(mines[i]);
    }
    free(mines);

    return T;
}
TTMines *decouvrir_case(TTMines *T, int lin, int col)
{ //Rend la case visible à (lin,col) visible, si c'est un 0,
    //elle rend visible toutes les cases autour jusqu'à avoir des chiffres
    modifTabVisible(T, lin, col, 1);
    if (valTabMines(T, lin, col) == '0')
        T = visible_0(T, lin, col);
    //else if (valTabMines(T, lin, col) == 'M')
    //perdu;
    return T;
}
TTMines *drapeau_case(TTMines *T, TCurseur *C)
{
    if (valTabVisible(T, Lin(C), Col(C)) == -1)
        modifTabVisible(T, Lin(C), Col(C), 0);
    else if (valTabVisible(T, Lin(C), Col(C)) == 0)
        modifTabVisible(T, Lin(C), Col(C), -1);
    return T;
}

void free_TTMines(TTMines *T)
{
    int i;
    for (i = 0; i < Larg(T); i++)
    {
        free(T->TMines[i]);
        free(T->Visible[i]);
    }
    free(T->TMines);
    free(T->Visible);
    free(T);
}

void aff_TTMines(TTMines *T, TCurseur *C)
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
            if (valTabVisible(T, i, j) == 0)
            {
                printf("◼");
            }
            else if (valTabVisible(T, i, j) == -1)
            {
                printf("⚑");
            }
            else if (valTabMines(T, i, j) == '0')
                printf("□");
            else
                printf("%c", valTabMines(T, i, j));
            if ((i == Lin(C) && j == Col(C)) || (i == Lin(C) && j == Col(C) - 1))
            {
                printf("|");
            }
            else
                printf(" ");
        }
        printf("\n");
    }
}

TTMines *instruction(TTMines *T, TCurseur *C, char dir)
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
            modifCurseur(C, Lin(C) - 1, Col(C));
        break;
    case 'D': //Fall through
    case 'q':
        if (col > 0)
            modifCurseur(C, Lin(C), Col(C) - 1);
        break;
    case 'B': //Fall through
    case 's':
        if (lin < wid - 1)
            modifCurseur(C, Lin(C) + 1, Col(C));
        break;
    case 'C': //Fall through
    case 'd':
        if (col < len - 1)
            modifCurseur(C, Lin(C), Col(C) + 1);
        break;
    case 'c':
        if (valTabVisible(T, lin, col) == 1 && valTabMines(T, lin, col) != '0')
        {
            T = Verif_drapeau(T, C);
        }
        else if (valTabVisible(T, lin, col) != -1)
        {
            T = decouvrir_case(T, lin, col);
        }
        break;
    case 'f':
        T = drapeau_case(T, C);
        break;
    }
    return T;
}
int somme_autour(int **t, int lin, int col, int wid, int len)
{
    //Retourne la somme des entiers autour de la case t[lin][col]
    int somme = 0, i, j;
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i >= 0 && i < wid && j >= 0 && j < len))
            { //Si pas au milieu et à l'intérieur du tableau
                somme += t[i][j];
            }
    return somme;
}
TTMines *visible_0(TTMines *T, int lin, int col)
{
    int i, j;
    modifTabVisible(T, lin, col, 1);
    if (valTabMines(T, lin, col) == '0')
    {
        for (i = lin - 1; i <= lin + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                if ((i != lin || j != col) && (i >= 0 && i < Larg(T) && j >= 0 && j < Long(T)) && (valTabVisible(T, i, j) == 0))
                { //Si pas au milieu et à l'intérieur du tableau
                    T = visible_0(T, i, j);
                }
    }
    return T;
}
TTMines *Verif_drapeau(TTMines *T, TCurseur *C)
{
    int lin = Lin(C), col = Col(C), i, j;
    //Retourne la somme des entiers autour de la case t[lin][col]
    int somme = 0;
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i >= 0 && i < Larg(T) && j >= 0 && j < Long(T)) && (valTabVisible(T, i, j) == -1))
            { //Si pas au milieu et à l'intérieur du tableau
                somme++;
            }
    if (somme == valTabMines(T, Lin(C), Col(C)) - '0')
    {
        for (i = lin - 1; i <= lin + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                if ((i >= 0 && i < Larg(T) && j >= 0 && j < Long(T)) && valTabVisible(T, i, j) == 0)
                    T = decouvrir_case(T, i, j);
    }

    return T;
}

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
    return T->Visible[lin][col];
}
char valTabMines(TTMines *T, int lin, int col)
{
    return T->TMines[lin][col];
}

void modifTabVisible(TTMines *T, int lin, int col, int nouvVal)
{
    T->Visible[lin][col] = nouvVal;
}
void modifTabMines(TTMines *T, int lin, int col, char nouvVal)
{
    T->TMines[lin][col] = nouvVal;
}
