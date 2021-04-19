#include "anagrammes.h"


//PARTIE 4 relative aux anagrames 

//renvoie l'indice d'une lettre dans l'alphabet : a = 0, b = 1 ...
int indice_alphabet(const char lettre)
{
	return lettre-97;
}

//renvoie 1 si le mot est un anagramme du mot dans le dictionnaire, 0 sinon
int est_anagramme(const char* mot_dico, const char* mot)
{
	const int taille_mot_dico = strlen(mot_dico);
	const int taille_mot = strlen(mot);

	//si les tailles sont différentes, c'est forcément faux
	if (taille_mot != taille_mot_dico)
		return 0;

	int freq_lettre_mot_dico[128] = {0};
	int freq_lettre_mot[128] = {0};

	//retient la frequence d'apparition de chaque lettre dans le mot ...
	for (int i = 0; i < taille_mot; ++i)
	{
		freq_lettre_mot[(int)mot[i]]++;
		freq_lettre_mot_dico[(int)mot_dico[i]]++;
	}

	//... puis les compare. S'il y en a une qui differe c'est faux
	for (int i = 0; i < 128; ++i)
	{
		if (freq_lettre_mot_dico[i] != freq_lettre_mot[i])
			return 0;
	}
	return 1;
}

//affiche tous les anagrames du mot donné en argument
void affiche_anagramme(const struct dictionnaire dico, const char* mot)
{
	int nb_anagrame = 0;
	printf("\nLancement de la recherche de mot (ANAGRAMMES).\n");
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		if (est_anagramme(dico.mots[i].contenu, mot))
		{
			printf("Le mot numéro %d (%s) est un anagramme. \n", i+1, dico.mots[i].accent);
			nb_anagrame++;
		}
	}
	printf("Il y a un total de %d anagrammes du mot %s.\n", nb_anagrame, mot);
}