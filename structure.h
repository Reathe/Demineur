#pragma once
#include <stdbool.h>
//Visible Valeurs Possible
#define Vrai 1
#define Faux 0
#define Drapeau -1
//Charactères TCase
#define charMine "M" //"M" ou  "💣"
#define charDrapeau "⚑"
#define charCase "◼"
#define charCaseOuverte "□"
typedef enum
{
    Debut,
    Milieu,
    Fin
} TMomentPartie;

typedef struct TCase
{
    //La case sera affiché ssi Visible == 1
    //La case est cachée si Visible == 0
    //La case est un drapeau sinon (Visible == -1)
    //Le charactère Case qui est le charactère qui doit être affiché à l'utilisateur
    int Visible;
    char Case;
} TCase;

typedef struct TTMines
{
    //Un tableau de cases (utilisé comme un tableau à deux dimensions)
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

    //Création/destrucion
TTMines *init_TTMines(int largeur, int longueur, int nbombe, TCurseur *C);
void free_TTMines(TTMines *T);

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
int somme_autour(int *t, int lin, int col, int wid, int len);
void instruction(TTMines *T, TCurseur *C, char dir, bool *defaite);
void visible_0(TTMines *T, int lin, int col);
void drapeau_case(TTMines *T, TCurseur *C);
void Verif_drapeau(TTMines *T, TCurseur *C, bool *defaite);
void decouvrir_case(TTMines *T, int lin, int col, bool *defaite);
void remplirCaseEtVoisines(int *t, TCurseur *C, int val, int wid, int len);
//Fin
