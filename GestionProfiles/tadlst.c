#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "tadlst.h"

lst_t consVide()
{
	return NULL;
}

void freeLst(lst_t *ptrL)
{
	lst_t L = *ptrL;
	while (!estVide(L))
	{
		lst_t T = L;
		L = reste(L);
		freeProfile(T->P);
		free(T);
	}
	*ptrL = consVide();
}

bool estVide(const lst_t L)
{
	return L == consVide();
}

profile_t *tete(lst_t L)
{
	assert(!estVide(L));

	return L->P;
}

lst_t reste(lst_t L)
{
	assert(!estVide(L));

	return L->suc;
}

int length(lst_t L)
{
	static int nb = 0; // static pour ne pas supprimer la variable d'un appel à l'autre

	for (; !estVide(L); nb += 1, L = reste(L))
		;
	return nb;
}

void ins(lst_t *ptrL, profile_t *P, int pos)
{
	int lg = length(*ptrL);

	assert(0 < pos && pos < lg + 2); // on s'autorise l'insertion en queue en position (lg+1)

	elt_t *E = (elt_t *)malloc(1 * sizeof(elt_t));

	E->P = P;

	if (pos == 1)
	{
		E->suc = *ptrL;
		*ptrL = E;
	}
	else
	{
		lst_t T = *ptrL;

		for (int p = 1; p < pos - 1; p += 1, T = reste(T))
			;
		E->suc = T->suc;
		T->suc = E;
	}
}

void printLst(lst_t L)
{
	int i;
	printf("Classement :\n");
	for (i = 1; !estVide(L); L = reste(L), i++)
	{
		printf("%d. ", i);
		printPro(tete(L));
		printf("\n");
	}
}
