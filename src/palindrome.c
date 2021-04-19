#include "palindrome.h"


//PARTIE 3 : relative aux palindromes 

//renvoie 1 si le mot est un palindrome, 0 sinon
int est_palindrome(const char* mot)
{
	const int taille = strlen(mot);
	
	for (int i = 0; i < taille/2; ++i)
	{
		if (mot[i] != mot[taille - i -1])
			return 0;
	}
	return 1;
}

//affiche tous les palindromes du dictionnaire
void affiche_palindrome(const struct dictionnaire dico)
{
	int nb_palindrome = 0;
	printf("\nLancement de la recherche de mot (PALINDROME).\n");
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		if (est_palindrome(dico.mots[i].contenu))
			printf("Le mot numéro %d (%s) est le %dème palindrome.\n", i+1, dico.mots[i].accent, ++nb_palindrome);
	}
	printf("Il y un un total de %d palindromes dans le dictionnaire.\n", nb_palindrome);
}


