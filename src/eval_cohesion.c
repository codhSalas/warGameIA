#include "eval_cohesion.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double eval_barycentre(Pion *plateau, int joueur, double *bar_x, double *bar_y)
{
	double somme_poids = 0.0;
	double somme_wx = 0.0;
	double somme_wy = 0.0;
	int i, j;

	if (plateau == NULL)
	{
		if (bar_x) *bar_x = 0.0;
		if (bar_y) *bar_y = 0.0;
		return 0.0;
	}

	for (i = 0; i < NB_LIGNES; i++)
	{
		for (j = 0; j < NB_COLONNES; j++)
		{
			int idx = i * NB_COLONNES + j;
			if (plateau[idx].couleur == joueur && plateau[idx].valeur > 0)
			{
				double w = (double)plateau[idx].valeur;
				somme_poids += w;
				somme_wx += w * (double)i;
				somme_wy += w * (double)j;
			}
		}
	}

	if (somme_poids <= 0.0)
	{
		if (bar_x) *bar_x = 0.0;
		if (bar_y) *bar_y = 0.0;
		return 0.0;
	}

	if (bar_x) *bar_x = somme_wx / somme_poids;
	if (bar_y) *bar_y = somme_wy / somme_poids;

	return somme_poids;
}

double eval_dispersion(Pion *plateau, int joueur)
{
	double bar_x = 0.0;
	double bar_y = 0.0;
	double somme_poids;
	double somme_distances_ponderees = 0.0;
	int i, j;

	if (plateau == NULL)
		return 0.0;

	somme_poids = eval_barycentre(plateau, joueur, &bar_x, &bar_y);

	if (somme_poids <= 0.0)
		return 0.0;

	for (i = 0; i < NB_LIGNES; i++)
	{
		for (j = 0; j < NB_COLONNES; j++)
		{
			int idx = i * NB_COLONNES + j;
			if (plateau[idx].couleur == joueur && plateau[idx].valeur > 0)
			{
				double w = (double)plateau[idx].valeur;
				double dx = (double)i - bar_x;
				double dy = (double)j - bar_y;
				double distance = sqrt(dx * dx + dy * dy);

				somme_distances_ponderees += w * distance;
			}
		}
	}

	return somme_distances_ponderees / somme_poids;
}

double eval_cohesion(Pion *plateau, int joueur)
{
	double dispersion = eval_dispersion(plateau, joueur);

	if (dispersion > 0.0 && dispersion < 8.0)
		return (8.0 - dispersion);

	return 0.0;
}

int eval_cohesion_entiere(Pion *plateau, int joueur)
{
	return (int)round(eval_cohesion(plateau, joueur));
}

int eval_score_densite(Pion *plateau, int joueur, int poids)
{
	int adversaire = -joueur;
	double dispersion_joueur;
	double dispersion_adv;
	double diff;

	if (plateau == NULL)
		return 0;

	dispersion_joueur = eval_dispersion(plateau, joueur);
	dispersion_adv = eval_dispersion(plateau, adversaire);

	diff = dispersion_adv - dispersion_joueur;

	return (int)round(diff * (double)poids);
}

