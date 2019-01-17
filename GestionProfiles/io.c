#include "stdio.h"
#include "io.h"

#include "tadpro.h"

lst_t fscanLst(const char *filename)
{
	FILE *fd = fopen(filename, "r");

	assert(fd != NULL);

	lst_t L = consVide();

	for (int pos = 1; !feof(fd); pos += 1)
	{
		profile_t *P = (profile_t *)calloc(1, sizeof(profile_t));

		fscanf(fd, " %d", &(P->score));
		if (P->score == 0)
		{
			free(P);
		}
		else
		{
			fscanf(fd, " %s\n", P->name);

			ins(&L, P, pos);
		}
	}

	fclose(fd);

	return L;
}

void fprintLst(lst_t L, const char *filename)
{
	FILE *fd = fopen(filename, "w");

	assert(fd != NULL);

	for (; !estVide(L); L = reste(L))
	{
		fprintf(fd, " %d %s\n", tete(L)->score, tete(L)->name);
	}
	fclose(fd);
}