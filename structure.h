
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
TTMines *init_TTMines(char *difficulte);

void free_TTMines(TTMines *T);
void aff_TTMines(TTMines *T);
int somme_autour(int **t, int lin, int col, int n);
TTMines *instruction(TTMines *T, char dir);
TTMines *visible_0(TTMines *T, int lin, int col);
TTMines *drapeau_case(TTMines *T);
TTMines *decouvrir_case(TTMines *T, int lin, int col);
TTMines *Verif_drapeau(TTMines *T);
//Fin