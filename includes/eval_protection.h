#ifndef EVAL_PROTECTION_H
#define EVAL_PROTECTION_H

#include "evaluation.h"

/* Protection locale et moyenne des pièces */
int eval_protection_piece(Pion *plateau, int l, int c);
double eval_protection_moyenne(Pion *plateau, int joueur);
int eval_protection_entiere(Pion *plateau, int joueur);

#endif /* EVAL_PROTECTION_H */
