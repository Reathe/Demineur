#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Demineur.h"
#include "structure.h"
#include "saisie.h"

int main()
{
    srand(time(NULL));
    system("clear");
    Bienvenue();
    Regles();
    int choix;
    do
    {
        choix = ChoixMenu();
        if (choix == 1)
        {
            bool rejouer;
            int largeur, longueur, nbMines, score;
            ChoixTaille(&largeur, &longueur, &nbMines);
            do
            {
                score = Partie(largeur, longueur, nbMines);
                if (score > 0)
                    EnregistrerScore(largeur, longueur, nbMines, score);
                rejouer = Rejouer();
                system("clear");
            } while (rejouer);
        }
        else if (choix == 2)
        {
            int largeur, longueur, nbMines;
            ChoixTaille(&largeur, &longueur, &nbMines);
            AfficherClassement(largeur, longueur, nbMines);
        }
        else if (choix == 3)
        {
            system("clear");
            Regles();
        }
    } while (choix != 4);
    exit(0);
}