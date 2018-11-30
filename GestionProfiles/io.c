#include "stdio.h"
#include "io.h"

#include "tadpro.h"

lst_t fscanLst( const char * filename ) {
  FILE * fd = fopen( filename, "rt" );

  assert( fd != NULL );

  lst_t L = consVide();

  for( int pos = 1; !feof( fd ); pos += 1 ) {
    profile_t * P = (profile_t *) calloc( 1, sizeof( profile_t ) ); //!! calloc intialise la mémoire à 0
    
    fscanf( fd, " %d", &(P->score) );
    if( P->score == 0 ) {
      free( P );
    } else {
      fscanf( fd, " %s", P->name );
      fscanf( fd, " %s", P->forename );

      ins( &L, P, pos );
    }
  }

  fclose( fd );

  return L;
}

void fwriteLst( lst_t L, const char * filename ) {
  FILE * fd = fopen( filename, "wb" );

  assert( fd != NULL );

  for( ; !estVide( L ); L = reste( L ) ) {
    fwrite( tete( L ), sizeof( profile_t ), 1, fd );
  }

  fclose( fd );
}

lst_t freadLst( const char * filename ) {
  FILE * fd = fopen( filename, "rb" );

  assert( fd != NULL );

  lst_t L = consVide();
  
  for( int pos = 1; !feof(fd); pos += 1 ) {
    profile_t * P = (profile_t *) calloc( 1, sizeof(profile_t) );
    
    fread( P, sizeof( profile_t ), 1, fd );
    if( P->score == 0 ) {
      free( P );
    } else {
      ins( &L, P, pos );
    }
  }

  return L;
}

