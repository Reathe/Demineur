#include <stdio.h>
#include <stdlib.h>
#include "fonctions.c"
#include "structure.c"
//Fonctions disponibles
TTMines* init_TTMines (TTMines* T ,char* difficulte);
void free_TTMines(TTMines* T);
void aff_TTMines (TTMines* T);


int main () {
    char instr;
    int lin=1,col=1;
    TTMines* T;

    T=init_TTMines(T,"");
    
    aff_TTMines(T);
    free_TTMines(T);
    //aff_TTMines(T);
    exit(0);
 }