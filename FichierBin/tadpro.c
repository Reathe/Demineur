#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"
#include "string.h"
#include "tadpro.h"

profile_t * consEmptyProfile() {
  profile_t * P = (profile_t *) calloc( 1, sizeof( profile_t ) );

  assert( P != NULL );

  return P;
}

profile_t * consProfile( char * name, char * forename, int num ) {
  profile_t * P = (profile_t *) calloc( 1, sizeof( profile_t ) );

  assert( P != NULL );

  strcpy( P->name, name );
  strcpy( P->forename, forename );
  P->num = num;

  return P;
}

void freeProfile( profile_t * P ) {
  assert( P != NULL );

  free( P );
}

char * readName( const profile_t * P ) {
  assert( P != NULL );

  return (char *) P->name;
}

void writeName( const char * name, profile_t * P ) {
  assert( P != NULL );

  strcpy( P->name, name );
}
  

char * readForename( const profile_t * P ) {
  assert( P != NULL );

  return (char *) P->forename;
}

void writeForename( const char * forename, profile_t * P ) {
  assert( P != NULL );

  strcpy( P->name, forename );
}

int readNum( const profile_t * P ) {
  assert( P != NULL );

  return P->num;
}

void writeNum( const int num, profile_t * P ) {
  assert( P != NULL );

  P->num = num;
}

void printPro( const profile_t * P ) {
  printf( "(%s %s %d)", P->forename, P->name, P->num );
}
