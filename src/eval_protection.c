#include "eval_protection.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int eval_protection_piece(Pion *plateau, int l, int c)
{
	int i, j;
	int couleur;
	int mini, maxi, minj, maxj;
	int protection = 0;

	if (plateau == NULL)
		return 0;

	couleur = plateau[l * NB_COLONNES + c].couleur;
	if (couleur == 0 || plateau[l * NB_COLONNES + c].valeur == 0)
		return 0;

	mini = (l - 1 < 0) ? 0 : l - 1;
	maxi = (l + 1 > NB_LIGNES - 1) ? NB_LIGNES - 1 : l + 1;
	minj = (c - 1 < 0) ? 0 : c - 1;
	maxj = (c + 1 > NB_COLONNES - 1) ? NB_COLONNES - 1 : c + 1;

	for (i = mini; i <= maxi; i++)
	{
		for (j = minj; j <= maxj; j++)
		{
			if (i == l && j == c)
				continue;

			if (plateau[i * NB_COLONNES + j].couleur == couleur)
			{
				protection += plateau[i * NB_COLONNES + j].valeur;
			}
		}
	}

	return protection;
}

double eval_protection_moyenne(Pion *plateau, int joueur)
{
	int total_protection = 0;
	int nb_pions = 0;
	int l, c;

	if (plateau == NULL)
		return 0.0;

	for (l = 0; l < NB_LIGNES; l++)
	{
		for (c = 0; c < NB_COLONNES; c++)
		{
			int idx = l * NB_COLONNES + c;
			if (plateau[idx].couleur == joueur && plateau[idx].valeur > 0)
			{
				total_protection += eval_protection_piece(plateau, l, c);
				nb_pions++;
			}
		}
	}

	if (nb_pions == 0)
		return 0.0;

	return (double)total_protection / (double)nb_pions;
}

int eval_protection_entiere(Pion *plateau, int joueur)
{
	return (int)round(eval_protection_moyenne(plateau, joueur));
}

