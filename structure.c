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
    T->lin = T->col = 0;
    if (strcmp(difficulte, "facile"))
    {
        (*T).n = 9;
        nbombe = 10;
    }
    else if (strcmp(difficulte, "moyen"))
    {
        T->n = 25;
        nbombe = 78;
    }
    else if (strcmp(difficulte, "difficile"))
    {
        T->n = 50;
        nbombe = 250;
    }
    else
    {
        T->n = 100;
        nbombe = 1000;
    }
    T->TMines = malloc((T->n) * sizeof(T->TMines));
    T->Visible = malloc((T->n) * sizeof(int *));
    for (i = 0; i < T->n; i++)
    {
        T->TMines[i] = malloc(T->n * sizeof(char));
        T->Visible[i] = malloc(T->n * sizeof(int));
        for (j = 0; j < T->n; j++)
        {
            T->TMines[i][j] = '0';
            T->Visible[i][j] = 0;
        }
    }

    //Création des mines//
    int **mines = malloc(sizeof(*mines) * (T->n));
    for (i = 0; i < T->n; i++)
    {
        mines[i] = malloc((T->n) * sizeof(int));
    }
    for (i = 0; i < T->n; i++)
        for (j = 0; j < T->n; j++)
            mines[i][j] = 0;
    //memset(mines, 0, sizeof(int) *(T->n*T->n + 4*T->n + 4) );
    int lin, col;
    for (i = 0; i < nbombe; i++)
    {
        do
        {
            lin = rand() % (T->n - 1) + 1;
            col = rand() % (T->n - 1) + 1;
        } while (mines[lin][col] == 1);
        mines[lin][col] = 1;
    }

    for (i = 0; i < T->n; i++)
    {
        for (j = 0; j < T->n; j++)
        {
            if (mines[i][j] == 1)
            {
                T->TMines[i][j] = 'M';
            }
            else
                T->TMines[i][j] = '0' + somme_autour(mines, i, j, T->n);
        }
    }
    free(mines);
    return T;
}
TTMines *decouvrir_case(TTMines *T, int lin, int col)
{ //Rend la case visible à (lin,col) visible, si c'est un 0,
    //elle remd visible toutes les cases autour jusqu'à avoir des chiffres
    T->Visible[lin][col] = 1;
    if (T->TMines[lin][col] == '0')
        T = visible_0(T, lin, col);
    //else if (T->TMines[lin][col] == 'M')
    //perdu;
    return T;
}
TTMines *drapeau_case(TTMines *T)
{
    if (T->Visible[T->lin][T->col] == -1)
        T->Visible[T->lin][T->col] = 0;
    else if (T->Visible[T->lin][T->col] == 0)
        T->Visible[T->lin][T->col] = -1;
    return T;
}

void free_TTMines(TTMines *T)
{
    free(T->TMines);
    free(T);
}

void aff_TTMines(TTMines *T)
{
    int i, j;
    for (i = 0; i < (T->n); i++)
    {
        for (j = 0; j < T->n; j++)
        {
            if (T->Visible[i][j] == 0)
            {
                printf("◼");
            }
            else if (T->Visible[i][j] == -1)
            {
                printf("⚑");
            }
            else if (T->TMines[i][j] == '0')
                printf("□");
            else
                printf("%c", T->TMines[i][j]);
            if (i == T->lin && j == T->col)
            {
                printf("|");
            }
            else
                printf(" ");
        }
        printf("\n");
    }
}

TTMines *instruction(TTMines *T, char dir)
{
    int lin = T->lin,
        col = T->col,
        n = T->n;
    switch (dir)
    {
    case 'z':
        if (lin > 0)
            T->lin--;
        break;
    case 'q':
        if (col > 0)
            T->col--;
        break;
    case 's':
        if (lin < n - 1)
            T->lin++;
        break;
    case 'd':
        if (col < n - 1)
            T->col++;
        break;
    case 'A':
        if (lin > 0)
            T->lin--;
        break;
    case 'D':
        if (col > 0)
            T->col--;
        break;
    case 'B':
        if (lin < n - 1)
            T->lin++;
        break;
    case 'C':
        if (col < n - 1)
            T->col++;
        break;
    case 'c':
        if (T->Visible[lin][col] == 1 && T->TMines[lin][col] != '0')
        {
            T = Verif_drapeau(T);
        }
        else if (T->Visible[lin][col] != -1)
        {
            T = decouvrir_case(T, lin, col);
        }
        break;
    case 'f':
        T = drapeau_case(T);
        break;
    }
    return T;
}
int somme_autour(int **t, int lin, int col, int n)
{
    //Retourne la somme des entiers autour de la case t[lin][col]
    int somme = 0, i, j;
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i >= 0 && i < n && j >= 0 && j < n))
            { //Si pas au milieu et à l'intérieur du tableau
                somme += t[i][j];
            }
    return somme;
}
TTMines *visible_0(TTMines *T, int lin, int col)
{
    int i, j;
    if (T->TMines[lin][col] == '0')
    {
        T->Visible[lin][col] = 1;
        for (i = lin - 1; i <= lin + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                if ((i != lin || j != col) && (i >= 0 && i < T->n && j >= 0 && j < T->n) && (T->Visible[i][j] == 0))
                { //Si pas au milieu et à l'intérieur du tableau
                    T = visible_0(T, i, j);
                }
    }
    T->Visible[lin][col] = 1;
    return T;
}
TTMines *Verif_drapeau(TTMines *T)
{
    int lin = T->lin, col = T->col, i, j;
    //Retourne la somme des entiers autour de la case t[lin][col]
    int somme = 0;
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i >= 0 && i < T->n && j >= 0 && j < T->n) && (T->Visible[i][j] == -1))
            { //Si pas au milieu et à l'intérieur du tableau
                somme++;
            }
    if (somme == T->TMines[T->lin][T->col] - '0')
    {
        printf("oui!");
        for (i = lin - 1; i <= lin + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                if ((i >= 0 && i < T->n && j >= 0 && j < T->n) && T->Visible[i][j] == 0)
                    T = decouvrir_case(T, i, j);
    }

    return T;
}