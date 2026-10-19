#ifndef EVAL_COHESION_H
#define EVAL_COHESION_H

#include "evaluation.h"

/* Barycentre et dispersion */
double eval_barycentre(Pion *plateau, int joueur, double *bar_x, double *bar_y);
double eval_dispersion(Pion *plateau, int joueur);

/* Cohésion des troupes */
double eval_cohesion(Pion *plateau, int joueur);
int eval_cohesion_entiere(Pion *plateau, int joueur);
int eval_score_densite(Pion *plateau, int joueur, int poids);

#endif /* EVAL_COHESION_H */
