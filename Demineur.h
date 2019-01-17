#pragma once

#include "structure.h"

int Partie(int largeur, int longueur, int nbMines);
//Lance une partie et retourne le score

int somme_autour(int *t, int lin, int col, int wid, int len);
//Retourne la somme des entiers autour de la case t[lin][col]

void instruction(TTMines *T, TCurseur *C, char dir, bool *defaite);
//Realise les operations sur la grille et le curseur
//en fonction de l'instruction qu'on lui donne

void visible_0(TTMines *T, int lin, int col);
//Rend visible toutes les cases

void drapeau_case(TTMines *T, TCurseur *C);
//Si la case est dejà un drapeau, l'enlève
//Si c'est une case non Visible, met un drapeau

void Verif_drapeau(TTMines *T, TCurseur *C, bool *defaite);
//Si le nombre de drapeaux autour de la case est egal à sa valeur
//On Rend visible toutes les cases autour de celle-ci

void decouvrir_case(TTMines *T, int lin, int col, bool *defaite);
//Rend la case visible à (lin,col) visible, et si c'est un 0,
//elle rend visible toutes les cases autour jusqu'à avoir des chiffres

void remplirCaseEtVoisines(int *t, TCurseur *C, int val, int wid, int len);
//Remplit une case et ses 8 voisines de la valeur val