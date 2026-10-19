#include "evaluation.h"
#include <stdio.h>

/* Évaluation complète selon la structure de poids */
int eval_avec_poids(Pion *plateau, int joueur, const PoidsEval *p)
{
	int score = 0;

	if (plateau == NULL || p == NULL)
		return 0;

	/* Camp allié */
	score += eval_valeur(plateau, joueur)             * p->mat_allie;
	score += eval_avancement_joueur(plateau, joueur)  * p->av_allie;
	score += eval_percee(plateau, joueur)             * p->perc_allie;
	score += eval_protection_entiere(plateau, joueur) * p->prot_allie;
	score += eval_cohesion_entiere(plateau, joueur)   * p->coh_allie;
	score += eval_controle_centre(plateau, joueur)    * p->ctr_allie;

	/* Camp adverse */
	score -= eval_valeur(plateau, -joueur)             * p->mat_adv;
	score -= eval_avancement_joueur(plateau, -joueur)  * p->av_adv;
	score -= eval_percee(plateau, -joueur)             * p->perc_adv;
	score -= eval_protection_entiere(plateau, -joueur) * p->prot_adv;
	score -= eval_cohesion_entiere(plateau, -joueur)   * p->coh_adv;
	score -= eval_controle_centre(plateau, -joueur)    * p->ctr_adv;

	return score;
}
