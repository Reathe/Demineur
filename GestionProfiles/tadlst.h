#pragma once
#include "stdbool.h"
#include "tadpro.h"

/**
   @brief le TAD d'une liste de profils.
   elt_t : le type d'un élément de la liste,
   lst_t : le type d'une liste, càd. un pointeur sur son premier élément.
*/
typedef struct eltList
{
	profile_t *P;
	struct eltList *suc;
} elt_t, *lst_t;

/**
   @brief les fonctions membres du TAD lst_t
   consVide : construit une liste vide,
   estVide : vérifie si la liste est vide;
   tete : renvoie la valeur du premier élément de la liste,
          (la liste ne peut pas être vide)
   reste : renvoie la liste privée de son premier élément
          (la liste ne peut pas être vide)
   length : renvoie la longueur de la liste
   ins : insère la valeur v à la position pos dans la liste
*/
lst_t consVide();

void freeLst(lst_t *);

bool estVide(const lst_t);

profile_t *tete(lst_t);

lst_t reste(lst_t);

int length(lst_t);

void ins(lst_t *, profile_t *, int);

void printLst(lst_t);
