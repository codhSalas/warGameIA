#include "eval_materiel.h"
#include <stdio.h>

int eval_valeur(Pion *plateau, int joueur)
{
	int valeur = 0;
	int i;

	if (plateau == NULL)
		return 0;

	for (i = 0; i < NB_LIGNES * NB_COLONNES; i++)
	{
		if (plateau[i].couleur == joueur)
		{
			valeur += plateau[i].valeur;
		}
	}
	return valeur;
}

int eval_nb_pions(Pion *plateau, int joueur)
{
	int nb = 0;
	int i;

	if (plateau == NULL)
		return 0;

	for (i = 0; i < NB_LIGNES * NB_COLONNES; i++)
	{
		if (plateau[i].couleur == joueur)
		{
			nb++;
		}
	}
	return nb;
}

