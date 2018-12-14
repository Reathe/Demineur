#pragma once

void clearBuffer();
//vide le buffer de l'entrée standard

bool checkBuffer();
//retourne Faux si le buffer n'est pas vide et Vrai sinon

void ChoixTaille(int *largeur, int *longueur, int *nbMines);
//saisie la taille de la grille et le nombre de mines

char* getFilename(int largeur, int longueur, int nbMines);
//restitue le nom du fichier pour une taille de grille et un nombre de mine donné

void Bienvenue();
void Regles();