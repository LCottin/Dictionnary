#include "etoile.h"

/*PARTIE 6
	Cette partie est similaire à la précédente sauf que l'on remplace le ? par *.
	Dans ce cas, l'étoile peut remplacer plusieurs lettres !
*/

//indique si le mot du dico correspond (1) ou non (0)
int repond_critere2 (const char* mot, const char* recherche)
{
	const int taille_recherche = strlen(recherche);
	const int taille_mot = strlen(mot);

	//parcourt jusqu'à l'étoile
	int i = 0;
	while (recherche[i] != '*')
	{
		if (mot[i] != recherche[i])
			return 0;
		i++;
	}

	//parcourt depuis la fin des mots jusqu'à l'étoile
	int fin_mot = taille_mot - 1;
	int fin_recheche = taille_recherche - 1;

	while (recherche[fin_recheche] != '*')
	{
		if (mot[fin_mot] != recherche[fin_recheche])
			return 0;
		
		fin_recheche--;
		fin_mot--;
	}
	return 1;	
}

//affiche tous les mots qui correspondent avec le mot recherche
void affiche_pattern2(const struct dictionnaire dico, const char* recherche)
{
	int nb_pattern = 0;
	printf("\nLancement de la recherche de mot (*).\n");
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		if (repond_critere2(dico.mots[i].contenu, recherche))
		{
			printf("Le mot numéro %d (%s) répond au critère.\n", i+1, dico.mots[i].accent);
			nb_pattern++;
		}
	}
	printf("Il y un un total de %d mots qui répondent au critère.\n", nb_pattern);
}
