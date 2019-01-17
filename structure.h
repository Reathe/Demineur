#pragma once
#include <stdbool.h>
//Visible Valeurs Possible
#define Vrai 1
#define Faux 0
#define Drapeau -1
//Charactères TCase
#define charMine "☢" //"M" ou  "☢"
#define charDrapeau "⚑"
#define charCase "◼"
#define charCaseOuverte "□"
//Charactères utilisateurs
#define DecouvrirCase 'g'
#define PoserDrapeau 'f'
#define Quitter 'p'
typedef enum
{
    Debut,
    Milieu,
    Fin
} TMomentPartie;

typedef struct TCase
{
    //La case sera affiche ssi Visible == 1
    //La case est cachee si Visible == 0
    //La case est un drapeau sinon (Visible == -1)
    //Le charactère Case qui est le charactère qui doit être affiche à l'utilisateur
    int Visible;
    char Case;
} TCase;

typedef struct TTMines
{
    //Un tableau de cases (utilise comme un tableau à deux dimensions)
    // avec largeur lignes et longueur colonnes
    TCase *TMine;
    int largeur, longueur;
    int nbMines, nbDrapeau, nbCasesRestantes;
} TTMines;

typedef struct TCurseur
{
    int ligne, colonne;
} TCurseur;

//Fonctions disponibles

//Creation/destrucion
void init_TTMines(TTMines *T, TCurseur *C);
void free_TTMines(TTMines *T);
TTMines *consTTMines(int largeur, int longueur, int nbombe);
//Consultation TTMines
int Larg(TTMines *T);
int Long(TTMines *T);
int valTabVisible(TTMines *T, int lin, int col);
char valTabCase(TTMines *T, int lin, int col);
int nombMines(TTMines *T);
int nombDrapeau(TTMines *T);
int nombCasesRest(TTMines *T);

//Modification TTMines
void modifTabVisible(TTMines *T, int lin, int col, int nouvVal);
void modifTabCase(TTMines *T, int lin, int col, char nouvVal);
void modifNombDrapeau(TTMines *T, int nouvVal);
void decrementNombCasesRest(TTMines *T);

//Primitives Curseur
TCurseur *consCurseur();
void modifCurseur(TCurseur *C, int lin, int col);
void free_TCurseur(TCurseur *C);
int Lin(TCurseur *C);
int Col(TCurseur *C);

//Autres
void aff_TTMines(TTMines *T, TCurseur *C, TMomentPartie moment);
//Fin
