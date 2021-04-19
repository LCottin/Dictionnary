#include "stat_mots.h"

//PARTIE 1.2 afffichage relatif aux mots

//donne le nombre de lettre du mot le plus court
int nb_lettre_min(const struct dictionnaire dico)
{ 
	int minimum = 1;
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		if (dico.mots[i].nb_lettre < minimum)
			minimum = dico.mots[i].nb_lettre;
	}
	return minimum;
}

//donne le nombre de lettre du mot le plus long
int nb_lettre_max(const struct dictionnaire dico) 
{ 
	int maximum = 1;
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		if (dico.mots[i].nb_lettre > maximum)
			maximum = dico.mots[i].nb_lettre;
	}
	return maximum;
}

//donne la moyenne du nombre de lettre
double moyenne_lettre(const struct dictionnaire dico)
{
	double moyenne = 0;
	for (int i = 0; i < dico.nombre_mot; ++i)
		moyenne += dico.mots[i].nb_lettre;

	moyenne /= dico.nombre_mot;
	return moyenne;
}

//donne le nombre de mot ayant la meme longueur
int calcul_nombre_mot(const struct dictionnaire dico, const int longueur)
{
	int nombre = 0;
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		if (dico.mots[i].nb_lettre == longueur)
			nombre++;
	}
	return nombre;
}

//renvoie la proportion des mots d'une taille donnée
double proportion_mot(const struct dictionnaire dico, const double nombre_mot)
{
	return (double)(100 * nombre_mot / dico.nombre_mot);
}

//affiche toutes les statistiques liées aux mots
void affiche_statistique_mot(const struct dictionnaire dico)
{
	int nb_mot;
	double proportion;

	const int longueur_mini = nb_lettre_min(dico);
	const int longueur_maxi = nb_lettre_max(dico);
	const double longueur_moyenne = moyenne_lettre(dico);

	printf("\nLancement de la recherche statistique (STATS WORDS).\n");
	printf("Nombre de mots chargés     : %d\n", dico.nombre_mot);
	printf("Longueur minimale des mots : %d\n", longueur_mini);
	printf("Longueur maximale des mots : %d\n", longueur_maxi);	
	printf("Longueur moyenne des mots  : %lf\n", longueur_moyenne);

	for (int i = 1; i < longueur_maxi+1; ++i)
	{
		nb_mot = calcul_nombre_mot(dico, i);
		proportion = proportion_mot(dico, nb_mot);

		printf("Longueur %2d : %5d mots (%7.4lf %%) ", i, nb_mot, proportion);

		for (int i = 0; i < 3*floor(proportion) + 1; ++i)
		{
			printf("#");
		}
		printf("\n");
	}
}