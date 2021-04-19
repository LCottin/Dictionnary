#include "livre.h"
#include "load_dic.h"

//PARTIE 10 : ouverture d'un fichier type texte / livre

//ouvre un livre 
// POUR LE MOMENT : COMPTE LE NOMBRE DE MOT UNIQUEMENT
struct dictionnaire ouvrir_livre(const char* nom_fichier)
{
	FILE* fichier = fopen(nom_fichier, "r");
	if (fichier == NULL)
	{
		printf("Erreur d'uverture du fichier. Arret programme\n");
		exit(0);
	}

	unsigned nb_mots = 0;
	int lecture;
	int continuer = 1;

	while (continuer)
	{
		//selon la valeur lue, les cas diffèrent
		lecture = fgetc(fichier);
		switch (lecture)
		{
			case ',' :
			case '.' :
			case '!' :
			case '?' :
			case '\n':
			{
				//on lit un caractere en plus -> les séparateurs sont suivis d'un espace
				nb_mots++;
				lecture = fgetc(fichier);
				break;
			}

			case ' ' :
			{
				nb_mots++;
				break;
			}

			case EOF :
			{
				continuer = 0;
				break;
			}
		}
	}

	fclose(fichier);

	
	//FILE* fichier2 = fopen(nom_fichier, "r");

	struct dictionnaire dico;
	dico.mots = malloc(sizeof(struct mot_dico) * nb_mots);
	dico.nombre_mot = nb_mots;
	continuer = 1;
	/*
	int taille_mot = 0;
	int numero_mot = 0;
	int indice = 0;

	while((lecture = fgetc(fichier2)) != EOF)
	{
		char buffer[64] = {0};	
		//si ce n'est pas la fin d'un mot
		if (lecture != ' ' || lecture != '.' || lecture != ',' )//|| !isdigit(lecture))
		{
			buffer[indice++] = lecture;
		}

		else 
		{
			taille_mot = strlen(buffer);
			dico.mots[numero_mot].contenu = malloc((taille_mot + 1) * sizeof(char));
			//copie le mot en latin1
			strcpy(dico.mots[numero_mot].contenu, buffer);
	        //desaccentue le mot
			convert_word(dico.mots[numero_mot].contenu);

			char mot_accent[128];
			convert_to_utf8(mot_accent, buffer);

			dico.mots[numero_mot].accent = malloc( (strlen(mot_accent) + 1) * sizeof(char) );
			strcpy(dico.mots[numero_mot].accent, mot_accent);

			indice = 0;
			taille_mot = 0;
			numero_mot++;

		}
	}
	fclose(fichier2);
	*/
	
	printf("Nombre de mots chargés : %d\n", nb_mots);
	return dico;
}

