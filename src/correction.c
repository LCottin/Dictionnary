#include "correction.h"


/* PARTIE 9 
	Dans cette partie, l'utilisateur rentre un mot mal orthographié 
	et on cherche le mot correctement écrit
*/


/*Renvoie la distance des deux mots à la façon d'un correcteur orthographique
    NE PREND PAS EN COMPTE LES ACCENTS ! */
int distance(const char* mot, const char* mal_ecrit){
	const int longueur_mot = strlen(mot);
	const int longueur_mal_ecrit = strlen(mal_ecrit);
	int dist = 0;              //distance entre les deux mots
	int indice_mot = 0;        //indice de parcourt du mot du dictionnaire
	int indice_mal_ecrit = 0;  //indice de parcourt du mot mal écrit

    //si les longueurs sont identiques, on recherche uniquement les différences
	if(longueur_mal_ecrit == longueur_mot)
	{
		for(int i = 0; i < longueur_mot; ++i)
		{
			if(mal_ecrit[i] != mot[i])
				dist++;
		}
        return dist;
	}

    //si le mot du dictionnaire est plus long
	if(longueur_mot > longueur_mal_ecrit)
	{
        //la distance est la différence des tailles - 1 (on tolere une erreur)
		dist = longueur_mot - longueur_mal_ecrit - 1;
        //on parcourt les deux mots avec 2 indices differents
		while(indice_mot < longueur_mot && indice_mal_ecrit < longueur_mal_ecrit)
		{
			if(mal_ecrit[indice_mal_ecrit] != mot[indice_mot])
			{
                //'il y'a une difference, on augmente la distance et diminue l'indice
				dist++;
				indice_mal_ecrit--;
			}
            //on augmente les indices (si il y a une difference, l'indice de mal écrit est inchangé)
			indice_mot++;
			indice_mal_ecrit++;
		}
        return dist;
	}

    //idem si le mot du dictionnaire est plus court
	if(longueur_mal_ecrit > longueur_mot)
	{
		dist = longueur_mal_ecrit - longueur_mot - 1;
		while(indice_mot < longueur_mot && indice_mal_ecrit < longueur_mal_ecrit)
		{
			if(mal_ecrit[indice_mal_ecrit] != mot[indice_mot])
			{
				dist++;
				indice_mot--;
			}
			indice_mot++;
			indice_mal_ecrit++;
		}
    }
    return dist;
}

//affiche tous les mots corrigés
void affiche_correction(const struct dictionnaire dico, const char* mal_ecrit)
{
	int nb_correction = 0;
	printf("\nLancement de la correction orthographique (CORRECTION).\n");
	for (int i = 0; i < dico.nombre_mot; ++i)
	{
		if (distance(dico.mots[i].contenu, mal_ecrit) <= 1)
		{
			nb_correction++;
			printf("Le mot numéro %d (%s) répond au critère.\n", i+1, dico.mots[i].accent);
		}
	}
	printf("Il y a %d mots qui correspondent.\n", nb_correction);
}	