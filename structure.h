
typedef struct
{
    //Le tableau 2d TMines allant de [0][0] à [n-1][n-1],
    //Le tableau de même taille Visible qui indique
    //si la case de Tmines du même indice est visible par l'utilisateur
    //n est la taille des tablaux
    //lin et col sont la position du "curseur"
    char **TMines;
    int **Visible;
    int largeur, longueur;
} TTMines;

typedef struct
{
    int ligne, colonne;
} TCurseur;

//Fonctions disponibles

TTMines *init_TTMines(char *difficulte);
void free_TTMines(TTMines *T);
int Larg(TTMines *T);
int Long(TTMines *T);
int valTabVisible(TTMines *T, int lin, int col);
char valTabMines(TTMines *T, int lin, int col);
void modifTabVisible(TTMines *T, int lin, int col, int nouvVal);
void modifTabMines(TTMines *T, int lin, int col, char nouvVal);

TCurseur * consCurseur();
void modifCurseur( TCurseur *C, int lin, int col);
void free_TCurseur(TCurseur *C);
int Lin(TCurseur *C);
int Col(TCurseur *C);

void aff_TTMines(TTMines *T, TCurseur *C);
int somme_autour(int **t, int lin, int col, int wid, int len);
TTMines *instruction(TTMines *T, TCurseur *C, char dir);
TTMines *visible_0(TTMines *T, int lin, int col);
TTMines *drapeau_case(TTMines *T, TCurseur *C);
TTMines *decouvrir_case(TTMines *T, int lin, int col);
TTMines *Verif_drapeau(TTMines *T, TCurseur *C);
//Fin