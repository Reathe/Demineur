#define Vrai 1
#define Faux 0
#define Drapeau -1
typedef struct TCase
{
    //La case sera affiché ssi Visible == 1
    //La case est un drapeau si Visible == 0
    //La case est cachée sinon (Visible == -1)
    //Le charactère Case qui est le charactère qui doit être affiché à l'utilisateur
    int Visible;
    char Case;
} TCase;

typedef struct TTMines
{
    //Un tableau de cases (utilisé comme un tableau à deux dimensions)
    // avec largeur lignes et longueur collonnes
    TCase *TMine;
    int largeur, longueur;
} TTMines;
typedef struct TCurseur
{
    int ligne, colonne;
} TCurseur;

//Fonctions disponibles

TTMines *init_TTMines(int longueur, int largeur,int nbombe);
void free_TTMines(TTMines *T);
int Larg(TTMines *T);
int Long(TTMines *T);
int valTabVisible(TTMines *T, int lin, int col);
char valTabCase(TTMines *T, int lin, int col);
void modifTabVisible(TTMines *T, int lin, int col, int nouvVal);
void modifTabCase(TTMines *T, int lin, int col, char nouvVal);

TCurseur *consCurseur();
void modifCurseur(TCurseur *C, int lin, int col);
void free_TCurseur(TCurseur *C);
int Lin(TCurseur *C);
int Col(TCurseur *C);

void aff_TTMines(TTMines *T, TCurseur *C);
int somme_autour(int *t, int lin, int col, int wid, int len);
TTMines *instruction(TTMines *T, TCurseur *C, char dir);
TTMines *visible_0(TTMines *T, int lin, int col);
TTMines *drapeau_case(TTMines *T, TCurseur *C);
TTMines *decouvrir_case(TTMines *T, int lin, int col);
TTMines *Verif_drapeau(TTMines *T, TCurseur *C);
//Fin