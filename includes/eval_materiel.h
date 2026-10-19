#ifndef EVAL_MATERIEL_H
#define EVAL_MATERIEL_H

#include "evaluation.h"

/* Somme de la valeur des pièces d'un joueur */
int eval_valeur(Pion *plateau, int joueur);

/* Nombre de pièces vivantes d'un joueur */
int eval_nb_pions(Pion *plateau, int joueur);

#endif /* EVAL_MATERIEL_H */
