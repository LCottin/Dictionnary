#include "scrabble.h"
#include "anagrammes.h"

/* PARTIE 7
	Dans cette partie, l'utilisateur fournit 7 lettres (type scrabble).
	Il faut alors trouver tous les mots que l'on peut former avec cette
	combinaison de lettres tel que l'on ferait au scrabble.
*/

//indique si le mot du dictionnaire peut etre forme avec la combinaison de lettres
int est_scrabble(const char* mot_dico, const char* combinaison)
{
	const int longueur_mot = strlen(mot_dico);

	//si le mot proposé est plus long que la longueur d'un scrabble
	if (longueur_mot > 7) 
		return 0;

	//on s'assure que la combinaison fasse bien 7 lettres
	if (strlen(combinaison) != 7)
	{
		printf("Le nombre de lettre de la combinaison doit etre égal à 7 !!\n");
		exit(0);
	}

	//si la combinaison et le mot sont anagrammes, on peut former le mot
	if (est_anagramme(mot_dico, combinaison)) 
		return 1;

	//retient la frequence de chaque lettre
	int freq_lettre_mot[26] = {0};
	int freq_combinaison[26] = {0};

	for (int i = 0; i < strlen(mot_dico); ++i)
		freq_lettre_mot[indice_alphabet(mot_dico[i])]++;

	for (int i = 0; i < 7; ++i)
		freq_combinaison[indice_alphabet(combinaison[i])]++;

	//si l'une des frequences de la combinaison est plus petite, on ne peut pas faire le mot
	for (int i = 0; i < 26; ++i)
	{
		if (freq_combinaison[i] < freq_lettre_mot[i])
			return 0;
	}
	return 1;
}

//affiche tous les mots que l'on peut former avec la combinaison
void affiche_scrabble(const struct dictionnaire dico, const char* combinaison)
{
	int nb_srabble = 0;
	printf("\nLancement de la recherche de mot (SCRABBLE)\n");
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		if (est_scrabble(dico.mots[i].contenu, combinaison))
		{
			printf("Le mot numéro %d (%s) répond au critère du scrabble.\n", i+1, dico.mots[i].accent);
			nb_srabble++;
		}
	}
	printf("Il y a un total de %d mots qui répondent au critère.\n", nb_srabble);
}