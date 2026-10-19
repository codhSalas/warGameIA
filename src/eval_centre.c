#include "eval_centre.h"
#include <stdio.h>

int eval_controle_centre(Pion *plateau, int joueur)
{
	int score_centre = 0;
	int l, c;

	if (plateau == NULL)
		return 0;

	for (l = 0; l < NB_LIGNES; l++)
	{
		for (c = 0; c < NB_COLONNES; c++)
		{
			int idx = l * NB_COLONNES + c;
			if (plateau[idx].couleur == joueur && plateau[idx].valeur > 0)
			{
				if (l >= 4 && l <= 5 && c >= 4 && c <= 5)
				{
					score_centre += plateau[idx].valeur * 4; /* Cœur central */
				}
				else if (l >= 3 && l <= 6 && c >= 3 && c <= 6)
				{
					score_centre += plateau[idx].valeur * 2; /* Zone centrale élargie */
				}
			}
		}
	}
	return score_centre;
}

