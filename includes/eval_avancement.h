#ifndef EVAL_AVANCEMENT_H
#define EVAL_AVANCEMENT_H

#include "evaluation.h"

/* Distances géométriques */
int dist_manhattan(int x1, int y1, int x2, int y2);
int dist_ligne_adverse(int ligne, int joueur);
int eval_distance_min_but(Pion *plateau, int joueur);

/* Avancement et percée */
int eval_avancement_joueur(Pion *plateau, int joueur);
int eval_percee(Pion *plateau, int joueur);
int eval_score_manhattan(Pion *plateau, int joueur, int poids_avancement, int poids_danger);

#endif /* EVAL_AVANCEMENT_H */
