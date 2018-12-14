#pragma once 
#include "tadlst.h"

lst_t fscanLst( const char * );

void fprintLst(lst_t L, const char *filename);

void fwriteLst( lst_t, const char * );

lst_t freadLst( const char * );

