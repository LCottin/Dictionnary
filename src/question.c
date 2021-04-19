#include "question.h"

/* PARTIE 5
	Dans cette partie, on donne un mot dont l'une des lettres est remplacée par
	un ? --> il faut trouver tous les mots qui collent si on enleve le ?
	ex : man??er --> manquer, manager ...
*/

//retourne 1 si le mot recherché matche avec le mot du dico
int repond_critere1(const char* mot, const char* recherche)
{
	const int taille_mot = strlen(mot);
	const int taille_recherche = strlen(recherche);

	//si les tailles sont différentes, le mot ne peut pas correspondre
	if(taille_mot != taille_recherche)
		return 0;

	for (int i = 0; i < taille_mot; ++i)
	{
		if (recherche[i] != '?')
		{
			if (mot[i] != recherche[i])
				return 0;
		}
	}
	return 1;
}

//affiche tous les mots qui correspondent avec le mot recherché
void affiche_pattern1(const struct dictionnaire dico, const char* recherche)
{
	int nb_pattern = 0;
	printf("\nLancement de la recherche de mot (?).\n");
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		if (repond_critere1(dico.mots[i].contenu, recherche))
		{
			printf("Le mot numéro %d (%s) répond au critère.\n", i+1, dico.mots[i].accent);
			nb_pattern++;
		}
	}
	printf("Il y un un total de %d mots qui répondent au critère.\n", nb_pattern);
}