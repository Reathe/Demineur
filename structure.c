#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct
{
    //Le tableau 2d TMines allant de [0][0] à [n-1][n-1],
    //Le tableau de même taille Visible qui indique
    //si la case de Tmines du même indice est visible par l'utilisateur
    //n est la taille des tablaux
    //lin et col sont la position du "curseur"
    char **TMines;
    int **Visible;
    int n, lin, col;
} TTMines;

//Fonctions disponibles
TTMines *init_TTMines(TTMines *T, char *difficulte);
void free_TTMines(TTMines *T);
void aff_TTMines(TTMines *T);
int somme_autour(int **t, int lin, int col);
TTMines *deplace_curseur(TTMines *T, char dir);
//Fin

TTMines *init_TTMines(TTMines *T, char *difficulte)
{
    int nbombe;
    T = malloc(sizeof(TTMines));
    T->lin = T->col = 0;
    if (difficulte == "facile")
    {
        (*T).n = 10;
        nbombe = 10;
    }
    else if (difficulte == "moyen")
    {
        T->n = 10;
        nbombe = 10;
    }
    else if (difficulte == "difficile")
    {
        T->n = 10;
        nbombe = 10;
    }
    else
    {
        T->n = 10;
        nbombe = 10;
    }
    T->TMines = malloc((T->n) * sizeof(char *));
    T->Visible = malloc((T->n) * sizeof(int *));
    for (int i = 0; i < T->n; i++)
    {
        T->TMines[i] = malloc(T->n * sizeof(char));
        T->Visible[i] = malloc(T->n * sizeof(int));
        for (int j = 0; j < T->n; j++)
        {
            T->TMines[i][j] = '0';
            T->Visible[i][j] = 0;
        }
    }

    //Création des mines//
    int **mines = malloc((T->n + 2) * sizeof(int *));
    for (int i = 0; i < T->n + 2; i++)
    {
        mines[i] = malloc((T->n + 2) * sizeof(int));
    }
    for (int i = 0; i < T->n + 2; i++)
        for (int j = 0; j < T->n + 2; j++)
            mines[i][j] = 0;
    //memset(mines, 0, sizeof(int) *(T->n*T->n + 4*T->n + 4) );
    int lin, col;
    for (int i = 0; i < nbombe; i++)
    {
        do
        {
            lin = rand() % (T->n + 1) + 1;
            col = rand() % (T->n + 1) + 1;
        } while (mines[lin][col] == 1);
        mines[lin][col] = 1;
    }

    for (int i = 0; i < T->n; i++)
    {
        for (int j = 0; j < T->n; j++)
        {
            if (mines[i + 1][j + 1] == 1)
            {
                T->TMines[i][j] = 'M';
            }
            else
                T->TMines[i][j] = '0' + somme_autour(mines, i + 1, j + 1);
        }
    }
    //free(mines);
    return T;
}
void free_TTMines(TTMines *T)
{
    free(T->TMines);
    free(T);
}

void aff_TTMines(TTMines *T)
{
    for (int i = 0; i < (T->n); i++)
    {
        for (int j = 0; j < T->n; j++)
        {
            if (i == T->lin && j == T->col)
            {
                printf("■ ");
            }
            else if (T->Visible[i][j] == 0)
            {
                printf("□ ");
            }
            else if (T->Visible[i][j] == -1)
            {
                printf("⚑ ");
            }
            else
                printf("%c ", T->TMines[i][j]);
        }
        printf("\n");
    }
}

TTMines *deplace_curseur(TTMines *T, char dir)
{
    switch (dir)
    {
    case 'z':
        if (T->lin > 0)
            T->lin--;
        break;
    case 'q':
        if (T->col > 0)
            T->col--;
        break;
    case 's':
        if (T->lin < T->n - 1)
            T->lin++;
        break;
    case 'd':
        if (T->col < T->n - 1)
            T->col++;
        break;
    case 'A':
        if (T->lin > 0)
            T->lin--;
        break;
    case 'D':
        if (T->col > 0)
            T->col--;
        break;
    case 'B':
        if (T->lin < T->n - 1)
            T->lin++;
        break;
    case 'C':
        if (T->col < T->n - 1)
            T->col++;
        break;
    case 'c':
        T->Visible[T->lin][T->col] = 1;
        break;
    case 'f':
        T->Visible[T->lin][T->col] = -1;
        break;
    }
    return T;
}
int somme_autour(int **t, int lin, int col)
{
    //Retourne la somme des entiers autour de la case t[lin][col]
    //Ne fonctionne que si toutes les cases autour de t[lin][col] sont à l'intérieur du tableau.
    int somme = 0;
    for (int i = lin - 1; i <= lin + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (i != lin || j != col)
            {
                somme += t[i][j];
            }
        }
    }
    return somme;
}