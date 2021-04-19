#include "stat_lettres.h"

//PARTIE 2 afffichage relatif aux lettres

//donne le nombre total de lettre dans le dictionnaire
int calcul_nombre_lettre_total(const struct dictionnaire dico)
{
	int nombre = 0;
	for (int i = 0; i < dico.nombre_mot; ++i)
		nombre += dico.mots[i].nb_lettre;		

	return nombre;
}

//donne le nombre d'une certaine lettre dans le dico
int calcul_nombre_lettre(const struct dictionnaire dico, const char lettre)
{
	int nombre = 0;
	char* mot;
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		for (int j = 0; j < dico.mots[i].nb_lettre; ++j)
		{
			mot = dico.mots[i].contenu;
			if (mot[j] == lettre)
				nombre++;
		}
	}
	return nombre;
}

//renvoie la proportion d'une lettre dans le dico
double proportion_lettre(const int nb_lettre_max, const double nb_lettre)
{
	return (double)(100* nb_lettre / nb_lettre_max);
}

//affiche toutes les statistiqus liées aux lettres
void affiche_statistique_lettre(const struct dictionnaire dico)
{
	int nb_lettre;
	const int nb_lettre_max = calcul_nombre_lettre_total(dico);

	printf("\nLancement de la recherche statistique (STATS LETTERS).\n");
	printf("Nombre de lettres chargées : %d\n", nb_lettre_max);
	for (int i = 97; i < 97 + 26; ++i)
	{
		nb_lettre = calcul_nombre_lettre(dico, i);
		printf("Nombre de %1c : %6d(%7.4lf %%) ", i, nb_lettre, proportion_lettre(nb_lettre_max, (double)nb_lettre));
		for (int j = 0; j < 3*floor(proportion_lettre(nb_lettre_max, (double)nb_lettre)) + 1; ++j)
		{
			printf("#");
		}
		printf("\n");
	}
}