#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"
#include "string.h"
#include "tadpro.h"

profile_t *consEmptyProfile()
{
	profile_t *P = (profile_t *)calloc(1, sizeof(profile_t));

	assert(P != NULL);

	return P;
}

profile_t *consProfile(char *name, int score)
{
	profile_t *P = (profile_t *)calloc(1, sizeof(profile_t));

	assert(P != NULL);

	strcpy(P->name, name);
	P->score = score;

	return P;
}

void freeProfile(profile_t *P)
{
	assert(P != NULL);

	free(P);
}

char *readName(const profile_t *P)
{
	assert(P != NULL);

	return (char *)P->name;
}

void writeName(const char *name, profile_t *P)
{
	assert(P != NULL);

	strcpy(P->name, name);
}

int readScore(const profile_t *P)
{
	assert(P != NULL);

	return P->score;
}

void writeScore(const int Score, profile_t *P)
{
	assert(P != NULL);

	P->score = Score;
}

void printPro(const profile_t *P)
{
	printf("%s : %d", P->name, P->score);
}
