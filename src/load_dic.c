#include "load_dic.h"


//PARTIE 1 :charge un dictionnnaire en mémoire

//supprime le retour à la ligne et copie le texte
void change(char* chaine)
{
	const int taille = strlen(chaine);
	for (int i = 0; i < taille; ++i)
	{
		if (chaine[i] == '\n')
			chaine[i] = 0;

        if (chaine[i] == '\r')
            chaine[i] = 0;
	}
}

char convert_char(unsigned char c){

    if( c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    
    //
    // Conversion du format Latin 1 vers de l'ascii sans accent
    //

    if( c == 0xE0 /* 'à' */ ) return 'a';
    if( c == 0xE2 /* 'â' */ ) return 'a';
    if( c == 0xE4 /* 'ä' */ ) return 'a';

    if( c == 0xE7 /* 'ç' */ ) return 'c';
    if( c == 0xE8 /* 'è' */ ) return 'e';
    if( c == 0xE9 /* 'é' */ ) return 'e';
    if( c == 0xEA /* 'ê' */ ) return 'e';
    if( c == 0xEB /* 'ë' */ ) return 'e';
    
    if( c == 0xEE /* 'î' */ ) return 'i';
    if( c == 0xEF /* 'ï' */ ) return 'i';
    
    if( c == 0xF4 /* 'ô' */ ) return 'o';
    if( c == 0xF6 /* 'ö' */ ) return 'o';

    if( c == 0xF9 /* 'ù' */ ) return 'o';
    
    if( c == 0xFB /* 'û' */ ) return 'u';
    if( c == 0xFC /* 'ü' */ ) return 'u';

    return c;
}

//
// Convert latin-1 ASCII => UTF-8
// ATTENTION DST DOIT ETRE PLUS GRAND QUE SRC !!!!
//
void convert_to_utf8(char* dst, const char* src){
    int taille = strlen( src );
    
    int ptr = 0;
    
    for(int i = 0; i < taille; i += 1)
    {
        unsigned char c = (unsigned char)src[i];
        
        if( c >= 'A' && c <= 'Z')
            c = (c - 'A' + 'a');
        
        if( c == 0xE0 /* 'à' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xA0;
        }else if( c == 0xE2 /* 'â' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xA2;
        }else if( c == 0xE4 /* 'ä' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xA4;
        }else if( c == 0xE7 /* 'ç' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xA7;
        }else if( c == 0xE8 /* 'è' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xA8;
        }else if( c == 0xE9 /* 'é' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xA9;
        }else if( c == 0xEA /* 'ê' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xAA;
        }else if( c == 0xEB /* 'ë' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xAB;
        }else if( c == 0xEE /* 'î' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xAE;
        }else if( c == 0xEF /* 'ï' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xAF;
        }else if( c == 0xF4 /* 'ô' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xB4;
        }else if( c == 0xF6 /* 'ö' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xB6;
        }else if( c == 0xF9 /* 'ù' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xB9;
        }else if( c == 0xFB /* 'û' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xBB;
        }else if( c == 0xFC /* 'ü' */ ){
            dst[ptr++] = 0xC3;
            dst[ptr++] = 0xBC;
        }else{
            dst[ptr++] = c;
        }
    }
    
    dst[ptr++] = 0;
}


void convert_word(char* word)
{
    int length = strlen( word );
    for (int i = 0; i < length; i += 1) {
        word[i] = convert_char( word[i] );
    }
}

//ouvre le dictionnaire et copie son contenu
struct dictionnaire ouvrir_fichier(const char* nom_fichier) 
{
	//ouvertue du fichier
	FILE* fichier = fopen(nom_fichier, "r");
	if (fichier == NULL) 
	{
		printf("Erreur d'ouverture du fichier, arret programme.\n");
		exit(0);
	}

	//acquisition du nombre de mot
	unsigned nb_mot = 0;
	char lecture[50];
	while(fgets(lecture, 50, fichier) != NULL) 
		nb_mot++;

	fclose(fichier);

	//re-ouverture du fichier
	FILE* fichier2 = fopen(nom_fichier, "r");
	
	//lecture des mots
	struct dictionnaire dico;

	dico.mots = malloc(sizeof(struct mot_dico) * nb_mot);
	dico.nombre_mot = nb_mot;
	int taille_mot;

	for (int i = 0; i < nb_mot; ++i) 
	{
		fgets(lecture, 50, fichier2);        //lecture du mot
        change(lecture);                     //supprime le retour à la ligne
		taille_mot = strlen(lecture);        //recuperation de sa taille
        dico.mots[i].nb_lettre = taille_mot; //copie du nombre de lettre du mot
        
        //copie le mot en latin1
		dico.mots[i].contenu = malloc( (taille_mot+1) * sizeof(char) );		
		strcpy(dico.mots[i].contenu, lecture);
        //desaccentue le mot
		convert_word(dico.mots[i].contenu);

		//copie le mot avec accent (en utf8)
		char buffer[128];
		convert_to_utf8(buffer, lecture);
		dico.mots[i].accent = malloc( (strlen(buffer) + 1) * sizeof(char) );
		strcpy(dico.mots[i].accent, buffer);		

	}
	fclose(fichier2);
	return dico;
}

//libère la mémoire de tous les malloc effectués
void libere_memoire(struct dictionnaire dico)
{
	for (int i = 0; i < dico.nombre_mot; ++i)
	{	
		free(dico.mots[i].contenu);
		free(dico.mots[i].accent);
	}
	free(dico.mots);
}

