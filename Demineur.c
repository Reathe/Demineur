#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "structure.h"
#include "saisie.h"
#include "GestionProfiles/io.h"
#include "GestionProfiles/tadlst.h"
#include "GestionProfiles/tadpro.h"

int Partie(int largeur, int longueur, int nbMines)
{
    system("/bin/stty -icanon"); //Permet d'éviter d'appuyer sur Enter
    char dir;
    TTMines *T;
    TCurseur *C;
    bool defaite = Faux;
    int tempsDebut = clock(), score = 0;
    C = consCurseur();
    T = consTTMines(largeur, longueur, nbMines);
    //Debut de partie (avant que les bombes soient générées)
    while (dir != Quitter && (dir != DecouvrirCase || valTabVisible(T, Lin(C), Col(C)) == Drapeau))
    {
        system("clear");
        printf("Nombre de mines restantes : %d\n", nombMines(T) - nombDrapeau(T));
        aff_TTMines(T, C, Debut);
        printf("Lin=%d, col=%d\n", Lin(C) + 1, Col(C) + 1);
        dir = getc(stdin);
        if (dir!=DecouvrirCase)
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
    system("/bin/stty cooked"); //Remet les paramètres par défaut de la console
    system("clear");
    aff_TTMines(T, C, Fin);
    if (defaite)
        printf("Vous avez perdu.\n");
    else if (nombCasesRest(T) == nombMines(T))
    {
        printf("Vous avez gagné !\n");
        score = clock() - tempsDebut;
    }
    else if (dir == Quitter)
        printf("Vous avez quitté la partie en cours.\n");
    free_TTMines(T);
    free_TCurseur(C);
    return score;
}

int main()
{
    srand(time(NULL));
    system("clear");
    Bienvenue();
    Regles();
    int rejouer;
    do {
        int largeur, longueur, nbMines, score;
        ChoixTaille(&largeur, &longueur, &nbMines);
        score = Partie(largeur, longueur, nbMines);
        if (score>0)
            EnregistrerScore(largeur, longueur, nbMines, score);
        rejouer = Rejouer();
    } while (rejouer);
    exit(0);
}

