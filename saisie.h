#pragma once

#include "GestionProfiles/tadlst.h"

void clearBuffer();
//vide le buffer de l'entrée standard

bool checkBuffer();
//retourne Faux si le buffer n'est pas vide et Vrai sinon

void ChoixTaille(int *largeur, int *longueur, int *nbMines);
//saisie la taille de la grille et le nombre de mines

bool Rejouer();
//DEmande à l'utilisateur s'il veut rejouer, retourne sa réponse

char *getFilename(int largeur, int longueur, int nbMines);
//restitue le nom du fichier pour une taille de grille et un nombre de mine donné

int Classement(int score, lst_t L);
//retourne le classement d'un joueur

void EnregistrerScore(int largeur, int longueur, int nbMines, int score);
//Demande à l'utilisateur s'il veut enregistrer son score, si oui, le fait.

void Bienvenue();
void Regles();