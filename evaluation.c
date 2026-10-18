#include "evaluation.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ========================================================================= */
/* 1. DENSITÉ & DISPERSION                                                    */
/* ========================================================================= */

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

	/* Si le joueur n'a aucun pion, dispersion nulle */
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

	/*
	 * Plus la dispersion est petite, plus les troupes sont denses / unies.
	 * Maximiser pour Minimax :
	 * - minimiser la dispersion du joueur
	 * - maximiser la dispersion de l'adversaire
	 */
	diff = dispersion_adv - dispersion_joueur;

	return (int)round(diff * (double)poids);
}

/* ========================================================================= */
/* 2. DISTANCE DE MANHATTAN & AVANCEMENT                                      */
/* ========================================================================= */

int dist_manhattan(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

int dist_ligne_adverse(int ligne, int joueur)
{
	/*
	 * Joueur 1  : part du bas (lignes 7-9), son but est la ligne 0.
	 * Joueur -1 : part du haut (lignes 0-2), son but est la ligne 9.
	 */
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
				/* Avancement = nombre de lignes franchies vers le camp adverse */
				int avancement = (NB_LIGNES - 1) - dist_ligne_adverse(i, joueur);
				total_avancement += plateau[idx].valeur * avancement;
			}
		}
	}

	return total_avancement;
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

	/* 1. Avancement global pondéré */
	avancement_joueur = eval_avancement_joueur(plateau, joueur);
	avancement_adv = eval_avancement_joueur(plateau, adversaire);
	score += (avancement_joueur - avancement_adv) * poids_avancement;

	/* 2. Alerte d'urgence sur le pion le plus proche du but (sprinteur) */
	min_dist_joueur = eval_distance_min_but(plateau, joueur);
	min_dist_adv = eval_distance_min_but(plateau, adversaire);

	/* Bonus offensif selon la proximité de la ligne adverse */
	if (min_dist_joueur == 1)
		score += poids_danger * 3;
	else if (min_dist_joueur == 2)
		score += poids_danger;
	else if (min_dist_joueur == 3)
		score += poids_danger / 3;

	/* Pénalité défensive critique si l'adversaire est sur le point d'atteindre notre ligne */
	if (min_dist_adv == 1)
		score -= poids_danger * 3;
	else if (min_dist_adv == 2)
		score -= poids_danger;
	else if (min_dist_adv == 3)
		score -= poids_danger / 3;

	return score;
}
/* ========================================================================= */
/* 3.evaluation de la valeur matérielle                                    */
/* ========================================================================= */

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

/* ========================================================================= */
/*  TEST DE VICTOIRE SUR PLATEAU SIMULÉ                                    */
/* ========================================================================= */

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

/* ========================================================================= */
/*  PERCÉE / DANGER IMMÉDIAT (DISTANCE AU BUT)                               */
/* ========================================================================= */

int eval_percee(Pion *plateau, int joueur)
{
	int min_dist = eval_distance_min_but(plateau, joueur);

	if (min_dist == 1)
		return 3; 
	else if (min_dist == 2)
		return 1; 

	return 0;
}
