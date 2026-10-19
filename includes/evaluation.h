#ifndef EVAL_H
#define EVAL_H

#ifndef NB_LIGNES
#define NB_LIGNES 10
#endif

#ifndef NB_COLONNES
#define NB_COLONNES 10
#endif

#ifndef PION_DEFINED
#define PION_DEFINED
typedef struct pion_s
{
	int couleur;
	int valeur;
} Pion;
#endif

/* Modules d'évaluation */
#include "eval_victoire.h"
#include "eval_materiel.h"
#include "eval_avancement.h"
#include "eval_cohesion.h"
#include "eval_protection.h"
#include "eval_centre.h"

/* Structure des 12 poids d'évaluation */
typedef struct poidsEval {
	/* Camp allié */
	int mat_allie;
	int av_allie;
	int perc_allie;
	int prot_allie;
	int coh_allie;
	int ctr_allie;

	/* Camp adverse */
	int mat_adv;
	int av_adv;
	int perc_adv;
	int prot_adv;
	int coh_adv;
	int ctr_adv;
} PoidsEval;

int eval_avec_poids(Pion *plateau, int joueur, const PoidsEval *p);

#if defined(__has_include)
#if __has_include("poids_presets.h")
#include "poids_presets.h"
#endif
#endif

#endif /* EVAL_H */