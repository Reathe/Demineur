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
int somme_autour(int **t, int lin, int col,int n);
TTMines *instruction(TTMines *T, char dir);
TTMines *visible_0 (TTMines *T,int lin,int col);
//Fin

TTMines *init_TTMines(TTMines *T, char *difficulte)
{
    int nbombe, i, j;
    T = malloc(sizeof(TTMines));
    T->lin = T->col = 0;
    if (difficulte == "facile")
    {
        (*T).n = 9;
        nbombe = 10;
    }
    else if (difficulte == "moyen")
    {
        T->n = 25;
        nbombe = 50;
    }
    else if (difficulte == "difficile")
    {
        T->n = 50;
        nbombe = 50;
    }
    else
    {
        T->n = 100;
        nbombe = 100;
    }
    T->TMines = malloc((T->n) * sizeof(char *));
    T->Visible = malloc((T->n) * sizeof(int *));
    for ( i = 0; i < T->n; i++)
    {
        T->TMines[i] = malloc(T->n * sizeof(char));
        T->Visible[i] = malloc(T->n * sizeof(int));
        for ( j = 0; j < T->n; j++)
        {
            T->TMines[i][j] = '0';
            T->Visible[i][j] = 0;
        }
    }

    //Création des mines//
    int **mines = malloc((T->n) * sizeof(int *));
    for ( i = 0; i < T->n; i++)
    {
        mines[i] = malloc((T->n) * sizeof(int));
    }
    for ( i = 0; i < T->n; i++)
        for ( j = 0; j < T->n; j++)
            mines[i][j] = 0;
    //memset(mines, 0, sizeof(int) *(T->n*T->n + 4*T->n + 4) );
    int lin, col;
    for ( i = 0; i < nbombe; i++)
    {
        do
        {
            lin = rand() % (T->n -1) + 1;
            col = rand() % (T->n -1) + 1;
        } while (mines[lin][col] == 1);
        mines[lin][col] = 1;
    }

    for ( i = 0; i < T->n; i++)
    {
        for ( j = 0; j < T->n; j++)
        {
            if (mines[i][j] == 1)
            {
                T->TMines[i][j] = 'M';
            }
            else
                T->TMines[i][j] = '0' + somme_autour(mines, i, j,T->n);
        }
    }
    free(mines);
    return T;
}
void free_TTMines(TTMines *T)
{
    free(T->TMines);
    free(T);
}

void aff_TTMines(TTMines *T)
{
    int i,j;
    for ( i = 0; i < (T->n); i++)
    {
        for ( j = 0; j < T->n; j++)
        {
            if (T->Visible[i][j] == 0)
            {
                printf("◼");
            }
            else if (T->Visible[i][j] == -1)
            {
                printf("⚑");
            }
            else if (T->TMines[i][j]=='0')
                printf("□");
            else 
                printf("%c", T->TMines[i][j]);
            if (i == T->lin && j == T->col)
            {
                printf("|");
            }else 
                printf (" ");
        }
        printf("\n");
    }
}

TTMines *instruction(TTMines *T, char dir)
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
        if (T->Visible[T->lin][T->col] != -1){
            T->Visible[T->lin][T->col] = 1;
            if (T->TMines[T->lin][T->col]=='0')
                T=visible_0(T,T->lin,T->col);
        }
        break;
    case 'f':
        if (T->Visible[T->lin][T->col] == -1)
            T->Visible[T->lin][T->col] = 0;
        else if(T->Visible[T->lin][T->col] == 0)
            T->Visible[T->lin][T->col] = -1;
        break;
    }
    return T;
}
int somme_autour(int **t, int lin, int col,int n)
{
    //Retourne la somme des entiers autour de la case t[lin][col]
    int somme = 0, i,j;
    for ( i = lin - 1; i <= lin + 1; i++)
        for ( j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i>=0 && i <n && j>=0 && j <n))
            { //Si pas au milieu et à l'intérieur du tableau
                somme+=t[i][j];
            }
    return somme;
}
TTMines *visible_0 (TTMines *T,int lin,int col){
    int i,j;
    if (T->TMines[lin][col]=='0'){
        T->Visible[lin][col]=1;
        for ( i = lin - 1; i <= lin + 1; i++)
            for ( j = col - 1; j <= col + 1; j++)
                if ((i != lin || j != col) && (i>=0 && i <T->n && j>=0 && j <T->n) && (T->Visible[i][j]==0))
                { //Si pas au milieu et à l'intérieur du tableau
                        T=visible_0(T,i,j);
                }
    }
    T->Visible[lin][col]=1;
    return T;
}
int Verif_drapeau(TTMines *T)
{
    int lin=T->lin,col=T->col,i,j;
    //Retourne la somme des entiers autour de la case t[lin][col]
    int somme = 0;
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i>=0 && i <T->n && j>=0 && j <T->n) && T->TMines[i][j])
            { //Si pas au milieu et à l'intérieur du tableau
                somme+=T->TMines[i][j];
            }
    return somme;
}