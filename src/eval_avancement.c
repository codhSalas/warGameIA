#include "eval_avancement.h"
#include <stdio.h>
#include <stdlib.h>

int dist_manhattan(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

int dist_ligne_adverse(int ligne, int joueur)
{
	if (joueur == 1)
		return ligne;
	else
		return (NB_LIGNES - 1) - ligne;
}

int eval_distance_min_but(Pion *plateau, int joueur)
{
	int min_dist = NB_LIGNES;
	int i, j;

	if (plateau == NULL)
		return NB_LIGNES;

	for (i = 0; i < NB_LIGNES; i++)
	{
		for (j = 0; j < NB_COLONNES; j++)
		{
			int idx = i * NB_COLONNES + j;
			if (plateau[idx].couleur == joueur && plateau[idx].valeur > 0)
			{
				int d = dist_ligne_adverse(i, joueur);
				if (d < min_dist)
					min_dist = d;
			}
		}
	}

	return min_dist;
}

int eval_avancement_joueur(Pion *plateau, int joueur)
{
	int total_avancement = 0;
	int i, j;

	if (plateau == NULL)
		return 0;

	for (i = 0; i < NB_LIGNES; i++)
	{
		for (j = 0; j < NB_COLONNES; j++)
		{
			int idx = i * NB_COLONNES + j;
			if (plateau[idx].couleur == joueur && plateau[idx].valeur > 0)
			{
				int avancement = (NB_LIGNES - 1) - dist_ligne_adverse(i, joueur);
				total_avancement += plateau[idx].valeur * avancement;
			}
		}
	}

	return total_avancement;
}

int eval_percee(Pion *plateau, int joueur)
{
	int min_dist = eval_distance_min_but(plateau, joueur);

	if (min_dist == 1)
		return 3;
	else if (min_dist == 2)
		return 1;

	return 0;
}

int eval_score_manhattan(Pion *plateau, int joueur, int poids_avancement, int poids_danger)
{
	int adversaire = -joueur;
	int avancement_joueur;
	int avancement_adv;
	int min_dist_joueur;
	int min_dist_adv;
	int score = 0;

	if (plateau == NULL)
		return 0;

	avancement_joueur = eval_avancement_joueur(plateau, joueur);
	avancement_adv = eval_avancement_joueur(plateau, adversaire);
	score += (avancement_joueur - avancement_adv) * poids_avancement;

	min_dist_joueur = eval_distance_min_but(plateau, joueur);
	min_dist_adv = eval_distance_min_but(plateau, adversaire);

	if (min_dist_joueur == 1)
		score += poids_danger * 3;
	else if (min_dist_joueur == 2)
		score += poids_danger;
	else if (min_dist_joueur == 3)
		score += poids_danger / 3;

	if (min_dist_adv == 1)
		score -= poids_danger * 3;
	else if (min_dist_adv == 2)
		score -= poids_danger;
	else if (min_dist_adv == 3)
		score -= poids_danger / 3;

	return score;
}

