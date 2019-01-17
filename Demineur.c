#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "structure.h"
#include "saisie.h"
#include "Demineur.h"
#include "GestionProfiles/io.h"
#include "GestionProfiles/tadlst.h"
#include "GestionProfiles/tadpro.h"

int Partie(int largeur, int longueur, int nbMines)
//Lance une partie et retourne le score
{
    system("/bin/stty -icanon"); //Permet d'eviter d'appuyer sur Enter
    char dir;
    TTMines *T;
    TCurseur *C;
    bool defaite = false;
    int tempsDebut = time(NULL), score = 0;
    C = consCurseur();
    T = consTTMines(largeur, longueur, nbMines);
    //Debut de partie (avant que les bombes soient generees)
    while (dir != Quitter && (dir != DecouvrirCase || valTabVisible(T, Lin(C), Col(C)) == Drapeau))
    {
        system("clear");
        printf("Nombre de mines restantes : %d\n", nombMines(T) - nombDrapeau(T));
        aff_TTMines(T, C, Debut);
        printf("Lin=%d, col=%d\n", Lin(C) + 1, Col(C) + 1);
        dir = getc(stdin);
        if (dir != DecouvrirCase)
            instruction(T, C, dir, &defaite);
    }

    init_TTMines(T, C);
    instruction(T, C, dir, &defaite);

    while (dir != Quitter && !defaite && nombCasesRest(T) != nombMines(T))
    {
        system("clear");
        printf("Nombre de mines restantes : %d\n", nombMines(T) - nombDrapeau(T));
        aff_TTMines(T, C, Milieu);
        printf("Lin=%d, col=%d\n", Lin(C) + 1, Col(C) + 1);
        dir = getc(stdin);
        instruction(T, C, dir, &defaite);
    }
    system("/bin/stty cooked"); //Remet les paramètres par defaut de la console
    system("clear");
    aff_TTMines(T, C, Fin);
    if (defaite)
        printf("Vous avez perdu.\n");
    else if (nombCasesRest(T) == nombMines(T))
    {
        printf("Vous avez gagne !\n");
        score = time(NULL) - tempsDebut;
    }
    else if (dir == Quitter)
        printf("Vous avez quitte la partie en cours.\n");
    free_TTMines(T);
    free_TCurseur(C);
    return score;
}

void remplirCaseEtVoisines(int *t, TCurseur *C, int val, int wid, int len)
//Remplit une case et ses 8 voisines de la valeur val
{
    int i, j;
    for (i = Lin(C) - 1; i <= Lin(C) + 1; i++)
        for (j = Col(C) - 1; j <= Col(C) + 1; j++)
            if (i >= 0 && i < wid && j >= 0 && j < len)
                //Si à l'interieur du tableau
                t[j + i * len] = val;
}

void decouvrir_case(TTMines *T, int lin, int col, bool *defaite)
//Rend la case visible à (lin,col) visible, et si c'est un 0,
//elle rend visible toutes les cases autour jusqu'à avoir des chiffres
{
    if (valTabCase(T, lin, col) == '0')
        visible_0(T, lin, col);
    else
    {
        modifTabVisible(T, lin, col, Vrai);
        decrementNombCasesRest(T);
        if (valTabCase(T, lin, col) == 'M')
            *defaite = true;
    }
}
void drapeau_case(TTMines *T, TCurseur *C)
//Si la case est dejà un drapeau, l'enlève
//Si c'est une case non Visible, met un drapeau
{
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

void instruction(TTMines *T, TCurseur *C, char dir, bool *defaite)
//Realise les operations sur la grille et le curseur
//en fonction de l'instruction qu'on lui donne
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
    case DecouvrirCase:
        if (valTabVisible(T, lin, col) == Vrai && valTabCase(T, lin, col) != '0')
            //Si la case est dejà visible et
            //qu'elle est differente de '0'
            Verif_drapeau(T, C, defaite);
        else if (valTabVisible(T, lin, col) != Drapeau)
            decouvrir_case(T, lin, col, defaite);
        break;
    case PoserDrapeau:
        drapeau_case(T, C);
        break;
    }
}
int somme_autour(int *t, int lin, int col, int wid, int len)
//Retourne la somme des entiers autour de la case t[lin][col]
{
    int somme = 0, i, j;
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i >= 0 && i < wid && j >= 0 && j < len))
                //Si pas au milieu et à l'interieur du tableau
                somme += t[j + i * len];
    return somme;
}
void visible_0(TTMines *T, int lin, int col)
//Rend visible toutes les cases
{
    int i, j;
    modifTabVisible(T, lin, col, Vrai);
    decrementNombCasesRest(T);
    if (valTabCase(T, lin, col) == '0')
    {
        for (i = lin - 1; i <= lin + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                if ((i != lin || j != col) && (i >= 0 && i < Larg(T) && j >= 0 && j < Long(T)) && (valTabVisible(T, i, j) == Faux))
                    //Si pas au milieu et si à l'interieur du tableau et si la case est invisible
                    visible_0(T, i, j);
    }
}

void Verif_drapeau(TTMines *T, TCurseur *C, bool *defaite)
//Si le nombre de drapeaux autour de la case est egal à sa valeur
//On Rend visible toutes les cases autour de celle-ci
{
    int lin = Lin(C), col = Col(C), i, j;
    int nbDrapeau = 0;
    //Calcul du nombre de drapeaux autour de la case lin,col
    for (i = lin - 1; i <= lin + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            if ((i != lin || j != col) && (i >= 0 && i < Larg(T) && j >= 0 && j < Long(T)) && (valTabVisible(T, i, j) == Drapeau))
                //Si pas au milieu et à l'interieur du tableau et si la case i,j est un drapeau
                nbDrapeau++;

    //Si le nombre de drapeaux est egal au nombre de drapeaux qu'indique la case
    //On rend visible toutes les cases autour
    if (nbDrapeau == valTabCase(T, Lin(C), Col(C)) - '0')
    {
        for (i = lin - 1; i <= lin + 1; i++)
            for (j = col - 1; j <= col + 1; j++)
                if ((i >= 0 && i < Larg(T) && j >= 0 && j < Long(T)) && valTabVisible(T, i, j) == Faux)
                    decouvrir_case(T, i, j, defaite);
    }
}