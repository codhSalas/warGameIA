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

/* --- Fonctions de densité & dispersion --- */

double eval_barycentre(Pion *plateau, int joueur, double *bar_x, double *bar_y);
double eval_dispersion(Pion *plateau, int joueur);
int eval_score_densite(Pion *plateau, int joueur, int poids);

/* --- Fonctions de distance de Manhattan & avancement --- */

int dist_manhattan(int x1, int y1, int x2, int y2);
int dist_ligne_adverse(int ligne, int joueur);
int eval_distance_min_but(Pion *plateau, int joueur);
int eval_avancement_joueur(Pion *plateau, int joueur);
int eval_score_manhattan(Pion *plateau, int joueur, int poids_avancement, int poids_danger);

/* --- Fonctions de valeur matérielle & cohésion --- */
int eval_valeur(Pion *plateau, int joueur);
int eval_nb_pions(Pion *plateau, int joueur);


/* --- Test de victoire sur plateau simulé --- */
int eval_test_victoire(Pion *plateau);

/* --- Fonction de percée / danger immédiat --- */
int eval_percee(Pion *plateau, int joueur);

/* --- Fonctions de protection des pièces --- */
int eval_protection_piece(Pion *plateau, int l, int c);
double eval_protection_moyenne(Pion *plateau, int joueur);
int eval_protection_entiere(Pion *plateau, int joueur);

/* --- Fonctions de cohésion (regroupement des troupes) --- */
double eval_cohesion(Pion *plateau, int joueur);
int eval_cohesion_entiere(Pion *plateau, int joueur);

#endif /* EVAL_H */