#pragma once
#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"

//#define _DEBUG_
/**
   @brief le TAD d'un profil.
   name : le nom de la personne,
   forename : le prénom de la personne,
   score : le score de la personne.
*/
#define sz 20
typedef struct
{
  char name[sz];
  char forename[sz];
  int score;
} profile_t;

/**
   @brief les fonctions membres du TAD lst_t
   consEmptyProfile : construit un profile vide,
   consProfile : construit un profile vide,
   freeProfile : libère la mémoire occupée par un profil,
   readName : lecture du champ name,
   writeName : ecriture dans le champ name,
   readForename : lecture du champ forename,
   writeForename : ecriture dans le champ forename,
   readScore : lecture du champ score,
   writeScore : ecriture dans le champ score,
*/
profile_t *consEmptyProfile();

profile_t *consProfile(char *, char *, int);

void freeProfile(profile_t *);

char *readName(const profile_t *);

void writeName(const char *, profile_t *);

char *readForename(const profile_t *);

void writeForename(const char *, profile_t *);

int readScore(const profile_t *);

void writeScore(const int, profile_t *);

void printPro(const profile_t *);
