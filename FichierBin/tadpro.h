#ifndef _TADPRO_
#define _TADPRO_

#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"

//#define _DEBUG_
/**
   @brief le TAD d'un profil.
   name : le nom de la personne,
   forename : le prénom de la personne,
   num : le numéro d'inscription de la personne.
*/
#define sz 20
typedef struct {
  char name[sz];
  char forename[sz];
  int num;
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
   readNum : lecture du champ num,
   writeNum : ecriture dans le champ num,
*/
profile_t * consEmptyProfile();

profile_t * consProfile( char *, char *, int );

void freeProfile( profile_t * );

char * readName( const profile_t * );

void writeName( const char *, profile_t * );

char * readForename( const profile_t * );

void writeForename( const char *, profile_t * );

int readNum( const profile_t * );

void writeNum( const int, profile_t * );

void printPro( const profile_t * );
#endif
