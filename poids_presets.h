/*
 * poids_presets.c
 *
 * Tableau des presets de pondération.
 *
 * Types :
 *   Equilibré   — poids symétriques, base de référence
 *   Attaque     — priorité matériel et avancée offensive
 *   Percée      — score de percée dominant, vitesse avant tout
 *   Défense     — cohésion et protection élevées
 *   Anti-percée — neutralise spécifiquement les percées adverses
 */

/*                                            ------ allié ------        ------ adverse -----          */
#ifndef POIDS_PRESETS_H
#define POIDS_PRESETS_H
#include "evaluation.h"
/*                                            mat   av  perc prot coh ctr  mat   av  perc prot coh ctr  */
static const PoidsEval TABLEAU_PRESETS[] = {
    /* [0]  Equilibré   — référence symétrique, tous critères pondérés */
    { 100,  60, 150,  20,  10,  5,   100,  60, 150,  20,  10,  5 },

    /* [1]  Attaque     — chasseur de matériel, contre les percées ennemies */
    { 433,  99, 361,   0, 201,  8,   116,  23, 492,  28, 129,  0 },

    /* [2]  Attaque     — poussée constante, pénalise le centre adverse */
    { 319, 256, 233,  14, 150,  4,   252, 237, 437, 127,  26, 336 },

    /* [3]  Défense     — phalange dense, armée résistante et cohésive */
    { 461,  94, 282,   0, 258,  1,   227,   0, 484, 250, 258,   0 },

    /* [4]  Défense     — forteresse protégée, protection et avancée élevées */
    { 455, 256, 238, 374, 343, 13,    78, 429, 311, 302, 149, 401 },

    /* [5]  Percée      — sprinteur éclair, priorité maximale à la pénétration */
    { 282,  54, 497,   0, 129,  1,   140, 203, 401, 105,  66,  16 },

    /* [6]  Attaque     — mastodonte, phalange offensive très lourde */
    { 500, 406, 125,   0, 369,  5,   391,  84, 500,   0, 157,   7 },

    /* [7]  Percée      — percée rapide, taillé pour tournoi 40 joueurs */
    { 419, 260, 489,   0,   0, 23,   220,  66, 376, 167, 119,   0 },

    /* [8]  Anti-percée — sentinelle rapide, bloque les percées adverses */
    { 204,  87, 271,   0, 156, 10,   298,  18, 470,   4, 217,   0 },

    /* [9]  Attaque     — blitz lourd, avancée massive anti-percée */
    { 492, 398, 230,   0, 269,  4,   159, 104, 500, 260,  61,   0 },

    /* [10] Attaque     — attrition pure, conservation maximale du matériel */
    { 500,  24,  95,   0,  24,  6,   101, 302, 441,  79, 237,  27 },

    /* [11] Equilibré   — profil polyvalent, protection élevée, tournoi 40 joueurs */
    { 221, 283, 453, 430,  61, 17,   278,  55,  95, 219, 183, 240 },

    /* [12] Défense     — forteresse compacte, cohésion au maximum */
    { 108, 247, 165,   0, 460,  5,   127, 238, 254, 155, 280,   0 },

    /* [13] Anti-percée — sniper équilibré, neutralise l'avancée adverse */
    { 436, 254, 441, 120, 344, 22,   206, 448, 283, 327, 111, 399 },

    /* [14] Percée      — sprinteur percée maximale, tournoi 40 joueurs gen 20 */
    { 250, 278, 500,   0, 152, 12,   240, 130, 280, 152,  92,  11 },

    /* [15] Défense     — phalange cohésive, cohésion alliée au maximum (500) */
    {  88, 197, 235, 104, 500,  4,   285, 358, 369, 294,  42, 403 },

    /* [16] Attaque     — avancée rapide, unités protégées (score record 4155) */
    { 111, 437,  47, 379, 196, 54,   278, 296, 163,  43, 440,   1 },

    /* [17] Equilibré   — cohésion renforcée par rapport à la baseline */
    { 230, 180, 275,  20, 380,  0,   310, 230, 370,  15, 280,   0 },

    /* [18] Attaque     — toutes armes, percée et matériel en priorité */
    { 429, 319, 489, 224,  85,  5,   213,  32, 359, 331,  59,  23 },

    /* [19] Défense     — phalange blindée, protection et cohésion très élevées */
    { 218, 187, 274, 458, 435,  0,   324, 481, 230, 191, 378,   0 },

    /* [20] Attaque     — chasseur de matériel pur, dépouille l'adversaire */
    { 460, 110, 245,   2, 189,  0,   492,  40, 314,  46, 293, 336 },

    /* [21] Anti-percée — spécialiste anti-percée, cohésion pour tenir les lignes */
    { 164, 265, 446,  21, 465,  0,   337, 147, 471,  29,  10, 410 },

    /* [22] Attaque     — attaque lourde et soutenue, gen 5 */
    { 111, 463, 403, 307, 196, 75,   420, 375, 226,  16, 423,   1 },

    /* [23] Percée      — percée coordonnée en convergence, gen 20 */
    { 108, 307, 422, 295, 161, 75,   285, 416, 244,  16, 423,   0 },
};

/* Alias de compatibilite avec les noms symboliques */
#define POIDS_BASELINE_TD              (TABLEAU_PRESETS[0])
#define POIDS_CHAMPION_RUN1_GEN100     (TABLEAU_PRESETS[1])
#define POIDS_CHAMPION_RUN2_GEN100     (TABLEAU_PRESETS[2])
#define POIDS_CHAMPION_RUN3_GEN100     (TABLEAU_PRESETS[3])
#define POIDS_CHAMPION_RUN4_GEN100     (TABLEAU_PRESETS[4])
#define POIDS_CHAMPION_RUN5_GEN100     (TABLEAU_PRESETS[5])
#define POIDS_CHAMPION_RUN6_GEN100     (TABLEAU_PRESETS[6])
#define POIDS_CHAMPION_RUN7_40POP_G100 (TABLEAU_PRESETS[7])
#define POIDS_CHAMPION_RAPIDE_10KS     (TABLEAU_PRESETS[8])
#define POIDS_CHAMPION_BLITZ_AVANCE    (TABLEAU_PRESETS[9])
#define POIDS_CHAMPION_MATERIEL_MAX    (TABLEAU_PRESETS[10])
#define POIDS_RECORD_FITNESS_40POP     (TABLEAU_PRESETS[11])
#define POIDS_FORTERESSE_COHESION_MAX  (TABLEAU_PRESETS[12])
#define POIDS_SNIPER_ANTI_AVANCE       (TABLEAU_PRESETS[13])
#define POIDS_SPRINTEUR_40POP_GEN20    (TABLEAU_PRESETS[14])
#define POIDS_PHALANGE_COHESION_500    (TABLEAU_PRESETS[15])
#define POIDS_CHAMPION_INVAINCU_4155   (TABLEAU_PRESETS[16])
#define POIDS_CHAMPION_EQUILIBRE       (TABLEAU_PRESETS[17])
#define POIDS_ULTRA_AGRESSIF           (TABLEAU_PRESETS[18])
#define POIDS_PHALANGE_BLINDEE         (TABLEAU_PRESETS[19])
#define POIDS_CHASSEUR_MATERIEL        (TABLEAU_PRESETS[20])
#define POIDS_ANTI_PERCEE              (TABLEAU_PRESETS[21])
#define POIDS_ATTAQUE_LOURDE_GEN5      (TABLEAU_PRESETS[22])
#define POIDS_CONVERGENCE_GEN20        (TABLEAU_PRESETS[23])

static const PoidsEval score1 = TABLEAU_PRESETS[0];
static const PoidsEval score2 = TABLEAU_PRESETS[1];
#endif /* POIDS_PRESETS_H */
