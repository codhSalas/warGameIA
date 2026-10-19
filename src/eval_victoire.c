#include "eval_victoire.h"
#include <stdio.h>

int eval_test_victoire(Pion *plateau)
{
	int i;
	int somme1 = 0, somme2 = 0;

	if (plateau == NULL)
		return 0;

	/* Teste si un pion a franchi la ligne de fond adverse */
	for (i = 0; i < NB_COLONNES; i++)
	{
		if (plateau[0 * NB_COLONNES + i].couleur == 1)
			return 1;
		if (plateau[(NB_LIGNES - 1) * NB_COLONNES + i].couleur == -1)
			return -1;
	}

	/* Teste si une armée est totalement anéantie */
	for (i = 0; i < NB_LIGNES * NB_COLONNES; i++)
	{
		if (plateau[i].couleur == 1)
			somme1++;
		if (plateau[i].couleur == -1)
			somme2++;
	}

	if (somme1 == 0)
		return -1;
	if (somme2 == 0)
		return 1;

	return 0;
}

