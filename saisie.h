#pragma once

#include "GestionProfiles/tadlst.h"

void clearBuffer();
//vide le buffer de l'entree standard

bool checkBuffer();
//retourne Faux si le buffer n'est pas vide et Vrai sinon

void ChoixTaille(int *largeur, int *longueur, int *nbMines);
//saisie la taille de la grille et le nombre de mines

bool Rejouer();
//DEmande à l'utilisateur s'il veut rejouer, retourne sa reponse

char *getFilename(int largeur, int longueur, int nbMines);
//restitue le nom du fichier pour une taille de grille et un nombre de mine donne

void ScanNomPrenom(char *nom, char *prenom);
//saisie le nom et prenom d'un joueur

int Classement(int score, lst_t L);
//retourne le classement d'un joueur

bool FichierExiste(char *FileName);
//retourne vrai si le fichier existe et faux sinon

void EnregistrerScore(int largeur, int longueur, int nbMines, int score);
//Demande à l'utilisateur s'il veut enregistrer son score, si oui, le fait.

void AfficherClassement(int largeur, int longueur, int nbMines);
//affiche le classement pour une largeur, longueur et un nb de mine donne

int ChoixMenu();
//affiche le menu et saisie la reponse de l'utilisateur

void Bienvenue();
void Regles();