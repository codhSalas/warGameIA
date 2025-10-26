#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define NB_LIGNES 10
#define NB_COLONNES 10
#define INFINI 10000000
#define PROFONDEUR 3
int node = 0;
int nbrCoups = 0;

// #define DEBUG

typedef struct pion_s
{
	int couleur;
	int valeur;
}Pion;
typedef struct suite_s
{
	int curX;
	int curY;
	int nextX;
	int nextY;
	int couleur;
	int valeur;
}Suite;
Pion *plateauDeJeu;

void f_affiche_plateau(Pion *plateau);
int f_convert_char2int(char c);
char f_convert_int2char(int i);
void f_copie_plateau(Pion *source, Pion *destination);
Pion *f_raz_plateau();
int f_eval(Pion *plateau, int joueur);
int f_min(Pion *plateau, int joueur, Suite *suite , int profondeur,int * alpha, int * beta);
int f_max(Pion *plateau, int joueur, Suite *suite , int profondeur,int * alpha, int * beta);


int f_convert_char2int(char c)
{
#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif
	if(c>='A' && c<='Z')
		return (int)(c-'A');
	if(c>='a' && c<='z')
		return (int)(c-'a');
	return -1;
}

char f_convert_int2char(int i)
{
#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	return (char)i+'A';
}

Pion *f_init_plateau()
{
	int i, j;
	Pion *plateau=NULL;


#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	plateau = (Pion *)malloc(NB_LIGNES*NB_COLONNES*sizeof(Pion));
	if(plateau == NULL)
	{
		printf("error: unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<NB_LIGNES; i++)
	{
		for(j=0; j<NB_COLONNES; j++)
		{
			plateau[i*NB_COLONNES+j].couleur = 0;
			plateau[i*NB_COLONNES+j].valeur = 0;
		}
	}

    /* les pieces de l'ordinateur */
	plateau[9*NB_COLONNES+5].couleur = 1;
	plateau[9*NB_COLONNES+5].valeur = 1;

	plateau[9*NB_COLONNES+6].couleur = 1;
	plateau[9*NB_COLONNES+6].valeur = 2;

	plateau[9*NB_COLONNES+7].couleur = 1;
	plateau[9*NB_COLONNES+7].valeur = 3;

	plateau[9*NB_COLONNES+8].couleur = 1;
	plateau[9*NB_COLONNES+8].valeur = 2;

	plateau[9*NB_COLONNES+9].couleur = 1;
	plateau[9*NB_COLONNES+9].valeur = 1;

	plateau[8*NB_COLONNES+0].couleur = 1;
	plateau[8*NB_COLONNES+0].valeur = 1;

	plateau[8*NB_COLONNES+1].couleur = 1;
	plateau[8*NB_COLONNES+1].valeur = 3;

	plateau[8*NB_COLONNES+2].couleur = 1;
	plateau[8*NB_COLONNES+2].valeur = 3;

	plateau[8*NB_COLONNES+3].couleur = 1;
	plateau[8*NB_COLONNES+3].valeur = 1;

	plateau[8*NB_COLONNES+6].couleur = 1;
	plateau[8*NB_COLONNES+6].valeur = 1;

	plateau[8*NB_COLONNES+7].couleur = 1;
	plateau[8*NB_COLONNES+7].valeur = 1;

	plateau[8*NB_COLONNES+8].couleur = 1;
	plateau[8*NB_COLONNES+8].valeur = 1;

	plateau[7*NB_COLONNES+1].couleur = 1;
	plateau[7*NB_COLONNES+1].valeur = 1;

	plateau[7*NB_COLONNES+2].couleur = 1;
	plateau[7*NB_COLONNES+2].valeur = 1;

    /*les pieces de l'ennemi */
	plateau[2*NB_COLONNES+7].couleur = -1;
	plateau[2*NB_COLONNES+7].valeur = 1;

	plateau[2*NB_COLONNES+8].couleur = -1;
	plateau[2*NB_COLONNES+8].valeur = 1;

	plateau[1*NB_COLONNES+1].couleur = -1;
	plateau[1*NB_COLONNES+1].valeur = 1;

	plateau[1*NB_COLONNES+2].couleur = -1;
	plateau[1*NB_COLONNES+2].valeur = 1;

	plateau[1*NB_COLONNES+3].couleur = -1;
	plateau[1*NB_COLONNES+3].valeur = 1;

	plateau[1*NB_COLONNES+6].couleur = -1;
	plateau[1*NB_COLONNES+6].valeur = 1;

	plateau[1*NB_COLONNES+7].couleur = -1;
	plateau[1*NB_COLONNES+7].valeur = 3;

	plateau[1*NB_COLONNES+8].couleur = -1;
	plateau[1*NB_COLONNES+8].valeur = 3;

	plateau[1*NB_COLONNES+9].couleur = -1;
	plateau[1*NB_COLONNES+9].valeur = 1;

	plateau[0*NB_COLONNES+0].couleur = -1;
	plateau[0*NB_COLONNES+0].valeur = 1;

	plateau[0*NB_COLONNES+1].couleur = -1;
	plateau[0*NB_COLONNES+1].valeur = 2;

	plateau[0*NB_COLONNES+2].couleur = -1;
	plateau[0*NB_COLONNES+2].valeur = 3;

	plateau[0*NB_COLONNES+3].couleur = -1;
	plateau[0*NB_COLONNES+3].valeur = 2;

	plateau[0*NB_COLONNES+4].couleur = -1;
	plateau[0*NB_COLONNES+4].valeur = 1;

#ifdef DEBUG
printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif

return plateau;
}

void f_affiche_plateau(Pion *plateau)
{
	int i,j,k;


#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	printf("\n    ");
	for(k=0; k<NB_COLONNES; k++)
		printf("%2c ",f_convert_int2char(k));
	printf("\n    ");
	for(k=0; k<NB_COLONNES; k++)
		printf("-- ");
	printf("\n");
	for(i=NB_LIGNES-1; i>=0; i--)
	{
		printf("%2d ", i);
		for(j=0; j<NB_COLONNES; j++)
		{
			printf("|");
			switch(plateau[i*NB_COLONNES+j].couleur)
			{
			case -1:
				printf("%do",plateau[i*NB_COLONNES+j].valeur);
				break;
			case 1:
				printf("%dx",plateau[i*NB_COLONNES+j].valeur);
				break;
			default:
				printf("  ");
			}
		}
		printf("|\n    ");
		for(k=0; k<NB_COLONNES; k++)
			printf("-- ");
		printf("\n");
	}
	printf("    ");

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
}


int f_gagnant()
{
	int i, j, somme1=0, somme2=0;


#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	/*Teste si quelqu'un est-il arrive sur la ligne de l'autre */
	for(i=0; i<NB_COLONNES; i++)
	{
		if(plateauDeJeu[i].couleur == 1)                               return  1;
		if(plateauDeJeu[(NB_LIGNES-1)*NB_COLONNES+i].couleur == -1)    return -1;
	}

	//taille des armees
	for(i=0; i<NB_LIGNES; i++)
	{
		for(j=0; j<NB_COLONNES; j++)
		{
			if(plateauDeJeu[i*NB_COLONNES+j].couleur == 1)  	somme1++;
			if(plateauDeJeu[i*NB_COLONNES+j].couleur == -1)  	somme2++;
		}
	}
	if(somme1==0)  return -1;
	if(somme2==0)  return  1;

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
	return 0;
}


/**
 * Prend comme argument la ligne et la colonne de la case
 * 	pour laquelle la bataille a lieu
 * Renvoie le couleur du gagnant
 * */
int f_bataille(int l, int c)
{
	int i, j, mini, maxi, minj, maxj;
	int somme=0;

#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif
	mini = l-1<0?0:l-1;
	maxi = l+1>NB_LIGNES-1?NB_LIGNES-1:l+1;
	minj = c-1<0?0:c-1;
	maxj = c+1>NB_COLONNES-1?NB_COLONNES-1:c+1;

	for(i=mini; i<=maxi; i++)
	{
		for(j=minj; j<=maxj; j++)
		{
			somme += plateauDeJeu[i*NB_COLONNES+j].couleur*plateauDeJeu[i*NB_COLONNES+j].valeur;
		}
	}
	// somme -= plateauDeJeu[l*NB_COLONNES+c].couleur*plateauDeJeu[l*NB_COLONNES+c].valeur;

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
	if(somme < 0)	return -1;
	if(somme > 0)	return 1;

	return plateauDeJeu[l*NB_COLONNES+c].couleur;
}


/**
 * Prend la ligne et colonne de la case d'origine
 * 	et la ligne et colonne de la case de destination
 * Renvoie 1 en cas d'erreur
 * Renvoie 0 sinon
 * */
int f_test_mouvement(Pion *plateau, int l1, int c1, int l2, int c2, int couleur)
{
#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
	printf("de (%d,%d) vers (%d,%d)\n", l1, c1, l2, c2);
#endif
	/* Erreur, hors du plateau */
	if(l1 < 0 || l1 >= NB_LIGNES || l2 < 0 || l2 >= NB_LIGNES || c1 < 0 || c1 >= NB_COLONNES || c2 < 0 || c2 >= NB_COLONNES)    return 1;
	/* Erreur, il n'y a pas de pion a deplacer ou le pion n'appartient pas au joueur*/
	if(plateau[l1*NB_COLONNES+c1].valeur == 0 || plateau[l1*NB_COLONNES+c1].couleur != couleur)                             	return 1;
	/* Erreur, tentative de tir fratricide */
	if(plateau[l2*NB_COLONNES+c2].couleur == plateau[l1*NB_COLONNES+c1].couleur)                                                return 1;

	if(l1-l2 >1 || l2-l1 >1 || c1-c2 >1 || c2-c1 >1 || (l1==l2 && c1==c2))                                                	return 1;
#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
	return 0;
}


/**
 * Prend la ligne et colonne de la case d'origine
 * 	et la ligne et colonne de la case de destination
 *  et effectue le trantement de l'operation demandée
 * Renvoie 1 en cas d'erreur
 * Renvoie 0 sinon
 * */
int f_bouge_piece(Pion *plateau, int l1, int c1, int l2, int c2, int couleur)
{
	int gagnant=0;


#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	if(f_test_mouvement(plateau, l1, c1, l2, c2, couleur) != 0)
		return 1;


	/* Cas ou il n'y a personne a l'arrivee */
	if(plateau[l2*NB_COLONNES+c2].valeur == 0)
	{
		plateau[l2*NB_COLONNES+c2].couleur = plateau[l1*NB_COLONNES+c1].couleur;
		plateau[l2*NB_COLONNES+c2].valeur = plateau[l1*NB_COLONNES+c1].valeur;
		plateau[l1*NB_COLONNES+c1].couleur = 0;
		plateau[l1*NB_COLONNES+c1].valeur = 0;
	}
	else
	{
		gagnant=f_bataille(l2, c2);
		/* victoire */
		if(gagnant == couleur)
		{
			plateau[l2*NB_COLONNES+c2].couleur = plateau[l1*NB_COLONNES+c1].couleur;
			plateau[l2*NB_COLONNES+c2].valeur = plateau[l1*NB_COLONNES+c1].valeur;
			plateau[l1*NB_COLONNES+c1].couleur = 0;
			plateau[l1*NB_COLONNES+c1].valeur = 0;
		}
		/* defaite */
		else if(gagnant != 0)
		{
			plateau[l1*NB_COLONNES+c1].couleur = 0;
			plateau[l1*NB_COLONNES+c1].valeur = 0;
		}
	}

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
	return 0;
}

//Calcul du nombre de pions sur le plateau du joueur
int f_nbPions(Pion* jeu, int joueur)
{
	int nbPion=0;
	int i, j;
	for (i = 0; i < NB_COLONNES; ++i)
	{
		for (j = 0; j < NB_LIGNES; ++j)
		{
			if (jeu[i * NB_COLONNES + j].couleur == joueur)
			{
				++nbPion;
			}
		}
	}
	return nbPion;
}

//Calcul de la valeur de tous les pions du joueur
int f_valeur(Pion* jeu, int joueur)
{
	int i, j;
	int valeur=0;
	for (i = 0; i < NB_COLONNES; ++i)
	{
		for (j = 0; j < NB_LIGNES; ++j)
		{
			if (jeu[i * NB_COLONNES + j].couleur == joueur)
			{
				valeur += jeu[i * NB_COLONNES + j].valeur;
			}
		}
	}
	return valeur;
}


int f_eval(Pion* jeu, int joueur){
    int score = 0;
    int adversaire = -joueur;
    int i, j;

    const int poids_materiel = 150;
    const int poids_avancement = 10; 
    const int poids_mobilite = 0;
    const int controle_centre = -5;
    // const int poids_defense_ligne = 50;      // Défense de la ligne de base
    const int poids_menace_adverse = 100;     // Pénalité pour pions adverses avancés
    const int poids_protection = 100;          // Bonus pour pions protégés
    const int poids_blocage = 50;            // Bonus pour bloquer l'adversaire
    
    // Vérification victoire/défaite
    if(f_gagnant(jeu, joueur) == joueur){
        return INFINI;
    }
    if(f_gagnant(jeu, joueur) == -joueur){
        return -INFINI;
    }

    for (i = 0; i < NB_LIGNES; i++){
        for (j = 0; j < NB_COLONNES; j++){
            Pion p = jeu[i * NB_COLONNES + j];
            
            if (p.couleur == joueur){
                // Valeur matérielle du pion
                score += p.valeur * poids_materiel;

                // Avancement offensif
                int avancement = (joueur == 1) ? (i) : (NB_LIGNES - 1 - i);
                if (avancement > 0){
                    score += poids_avancement * (1 + avancement); 
                    score += (avancement * poids_avancement);    
                }

                // DEFENSE : Bonus pour garder des pions sur la ligne de base
                // int distance_from_base = (joueur == 1) ? i : (NB_LIGNES - 1 - i);
                // if (distance_from_base <= 2) {  // 3 premières lignes
                //     score += poids_defense_ligne * (3 - distance_from_base);
                // }

                // PROTECTION : Bonus si le pion est entouré d'alliés
                int voisinage = 0;
                for (int di = -1; di <= 1; di++){
                    for (int dj = -1; dj <= 1; dj++){
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < NB_LIGNES && nj >= 0 && nj < NB_COLONNES){
                            if (jeu[ni * NB_COLONNES + nj].couleur == joueur){
                                voisinage++;
                            }
                        }
                    }
                }
				if (voisinage > 0){
                	score += voisinage * poids_protection;
				}else{
					score -=  poids_protection/2;
				}

                // Contrôle du centre
                if (i >= NB_LIGNES / 3 && i <= 2 * NB_LIGNES / 3 &&
                    j >= NB_COLONNES / 3 && j <= 2 * NB_COLONNES / 3){
                    score += controle_centre * controle_centre;
                }

                // Mobilité
                int mobilite = 0;
                for (int di = -1; di <= 1; di++){
                    for (int dj = -1; dj <= 1; dj++){
                        if (di == 0 && dj == 0) continue;
                        int si = i + di;
                        int sj = j + dj;
                        if (si >= 0 && si < NB_LIGNES && sj >= 0 && sj < NB_COLONNES){
                            if (f_test_mouvement(jeu, i, j, si, sj, joueur) == 0){
                                mobilite++;
                            }
                        }
                    }
                }
                score += mobilite * poids_mobilite;
            }
            else if (p.couleur == adversaire){
                score -= p.valeur * poids_materiel;

                int avancement = (adversaire == 1) ? (i) : (NB_LIGNES - 1 - i);
                
                // MENACE ADVERSE : Pénalité exponentielle pour pions adverses avancés
                if (avancement > 0){
                    score -= poids_avancement * (1 + avancement);
                    score -= (avancement * poids_avancement);
                    
                    // Pénalité CRITIQUE si l'adversaire est proche de notre ligne
                    if (avancement >= NB_LIGNES - 3) {  // 3 dernières lignes
                        int danger_level = avancement - (NB_LIGNES - 4);
                        score -= poids_menace_adverse * danger_level * danger_level * p.valeur;
                    }
                }

                // BLOCAGE : Vérifier si on peut bloquer ce pion adverse
                for (int di = -1; di <= 1; di++){
                    for (int dj = -1; dj <= 1; dj++){
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < NB_LIGNES && nj >= 0 && nj < NB_COLONNES){
                            // Si un de nos pions peut attaquer ce pion adverse
                            if (jeu[ni * NB_COLONNES + nj].couleur == joueur){
                                score += poids_blocage;
                            }
                        }
                    }
                }

                if (i >= NB_LIGNES / 3 && i <= 2 * NB_LIGNES / 3 &&
                    j >= NB_COLONNES / 3 && j <= 2 * NB_COLONNES / 3){
                    score -= controle_centre * controle_centre;
                }

                int mobilite = 0;
                for (int di = -1; di <= 1; di++){
                    for (int dj = -1; dj <= 1; dj++){
                        if (di == 0 && dj == 0) continue;
                        int si = i + di;
                        int sj = j + dj;
                        if (si >= 0 && si < NB_LIGNES && sj >= 0 && sj < NB_COLONNES){
                            if (f_test_mouvement(jeu, i, j, si, sj, adversaire) == 0){
                                mobilite++;
                            }
                        }
                    }
                }
                score -= mobilite * poids_mobilite;
            }
        }
    }

    return score;
}

void f_copie_plateau(Pion* source, Pion* destination)
{
	int i, j;
	for (i = 0; i < NB_LIGNES; i++)
	{
		for (j = 0; j < NB_COLONNES; j++)
		{
			destination[i * NB_COLONNES + j].couleur = source[i * NB_COLONNES + j].couleur;
			destination[i * NB_COLONNES + j].valeur = source[i * NB_COLONNES + j].valeur;
		}
	}
}

//mise a zero du plateau
Pion* f_raz_plateau()
{
	Pion* jeu = NULL;
	int i, j;
	jeu = (Pion *) malloc(NB_LIGNES * NB_COLONNES * sizeof (Pion));
	for (i = 0; i < NB_LIGNES; i++)
	{
		for (j = 0; j < NB_COLONNES; j++)
		{
			jeu[i * NB_COLONNES + j].couleur = 0;
			jeu[i * NB_COLONNES + j].valeur = 0;
		}
	}
	return jeu;	
}

int f_min(Pion* plateau, int joueur, Suite *suite, int profondeur, int *alpha, int *beta){
    node++;

    if(profondeur == PROFONDEUR){
        return f_eval(plateau, joueur);
    }
    int val = INFINI;
    
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (plateau[i * NB_COLONNES + j].couleur == joueur) {
                for (int si = -1; si <= 1; si++) {
                    for (int sj = -1; sj <= 1; sj++) {
							if(!(si == 0 && sj == 0)){
								if (f_test_mouvement(plateau, i, j, i + si, j + sj, joueur) == 0) {
								Pion sous_plateau[NB_LIGNES * NB_COLONNES];
								f_copie_plateau(plateau, sous_plateau);
								f_bouge_piece(sous_plateau, i, j, i + si, j + sj, joueur);
								int score = f_max(sous_plateau, -joueur, suite, profondeur + 1, alpha, beta);

								if (score < val) {
									val = score;
									if (profondeur == 0) {
										suite->curX = i;
										suite->curY = j;
										suite->nextX = i + si;
										suite->nextY = j + sj;
										suite->couleur = joueur;
										suite->valeur = plateau[i * NB_COLONNES + j].valeur;
									}
								}
								if(val <= *alpha){
									return val;
								}
								*beta = (val < *beta) ? val : *beta;
							}
						}
                    }
                }
            }
        }
    }
    return val;
}

int f_max(Pion* plateau, int joueur, Suite *suite, int profondeur, int *alpha, int *beta){  
    node++;

    if(profondeur == PROFONDEUR){
        return f_eval(plateau, joueur);
    }
    int val = -INFINI;

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (plateau[i * NB_COLONNES + j].couleur == joueur) {
                for (int si = -1; si <= 1; si++) {
                    for (int sj = -1; sj <= 1; sj++) {
						if(!(si == 0 && sj == 0)){
							if (f_test_mouvement(plateau, i, j, i + si, j + sj, joueur) == 0) {
								Pion sous_plateau[NB_LIGNES * NB_COLONNES];
								f_copie_plateau(plateau, sous_plateau);
								f_bouge_piece(sous_plateau, i, j, i + si, j + sj, joueur);
								int score = f_min(sous_plateau, -joueur, suite, profondeur + 1, alpha, beta);

								if (score > val) {
									val = score;
									if (profondeur == 0) {
										suite->curX = i;
										suite->curY = j;
										suite->nextX = i + si;
										suite->nextY = j + sj;
										suite->couleur = joueur;
										suite->valeur = plateau[i * NB_COLONNES + j].valeur;
									}
								}
								if(val >= *beta){
									return val;
								}
								*alpha = (val > *alpha) ? val : *alpha;
							}
	                    }
                	}
            	}
        	}
    	}
	}
	return val;
}
/**
 * Calcule et joue le meilleur cout
 * */
void f_IA(int joueur)
{
#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif
    int alpha = -INFINI;
    int beta = INFINI;

	Suite * suite = malloc(sizeof(Suite));
	if(suite==NULL){
		printf("Erreur allocation memoire\n");
		exit (1);
	}
	
	f_max(plateauDeJeu,joueur,suite,0,&alpha,&beta);
	f_bouge_piece(plateauDeJeu,suite->curX,suite->curY,suite->nextX,suite->nextY,joueur);
	printf(" joueur %d a joue (%d,%d) vers (%d,%d)\n", joueur, suite->curX, suite->curY, suite->nextX, suite->nextY);
	free(suite);

    #ifdef DEBUG
        printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
    #endif
}


/**
 * Demande le choix du joueur humain et calcule le coup demande
 * */
void f_humain(int joueur){
	char c1, c2;
	char buffer[32];
	int l1, l2;


    #ifdef DEBUG
        printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
    #endif

	printf("joueur ");
	switch(joueur)
	{
	case -1:
		printf("o ");
		break;
	case 1:
		printf("x ");
		break;
	default:
		printf("inconnu ");
	}
	printf("joue:\n");
	while(1)
	{
		fgets(buffer, 32, stdin);
		if(sscanf(buffer, "%c%i%c%i\n", &c1, &l1, &c2, &l2) == 4)
		{
			if(f_bouge_piece(plateauDeJeu, l1, f_convert_char2int(c1), l2, f_convert_char2int(c2), joueur) == 0)
				break;
		}
		fflush(stdin);
		printf("mauvais choix\n");
	}

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
}

int main(){
	srand(time(NULL));

	int fin = 0,mode=0 , ret, joueur = 1;
	printf("1 humain vs IA\n2 humain vs humain\n3 IA vs IA\n");
	scanf("%d",&mode);

	plateauDeJeu = f_init_plateau();
	clock_t start, end;
	start = clock();
	while (!fin)
	{
		printf("coups %d\n", nbrCoups);
		f_affiche_plateau(plateauDeJeu);
		if(mode==1)
		{
			if(joueur>0)
				f_humain(joueur);
			else
				f_IA(joueur);
		}
		else if(mode==2)
		{
			f_humain(joueur);
		}
		else
		{
			f_IA(joueur);
		}

		if ((ret = f_gagnant()) != 0)
		{
			switch (ret)
			{
			case 1:
				f_affiche_plateau(plateauDeJeu);
				printf("joueur x gagne!\n");
				fin = 1;
				break;
			case -1:
				f_affiche_plateau(plateauDeJeu);
				printf("joueur o gagne!\n");
				fin = 1;
				break;
			}
		}
		joueur = -joueur;
		nbrCoups++;
	}
	end = clock();
	printf("Temps de jeu: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("Nombre de noeuds: %d\n", node);
	printf("nombre de coup: %d\n", nbrCoups);
    #ifdef DEBUG
        printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
    #endif

	return 0;
}

