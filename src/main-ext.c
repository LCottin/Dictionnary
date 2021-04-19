#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>

#include "load_dic.h"
#include "scrabble.h"
#include "anagrammes.h"
#include "correction.h"
#include "etoile.h"
#include "structure.h"
#include "palindrome.h"
#include "question.h"
#include "stat_lettres.h"
#include "stat_mots.h"
#include "livre.h"


int main( int argc, char* argv[] )
{
    int  en_stats_words   = 0;
    int  en_stats_letters = 0;
    int  en_anagrammes    = 0;
    int  en_palindromes   = 0;
    int  en_question      = 0;
    int  en_star          = 0;
    int  en_scrabble      = 0;
    int  en_corretion     = 0;
    int  en_book          = 0;

    char pal_motif[128];
    char que_motif[128];
    char sta_motif[128];
    char scr_motif[128];
    char cor_motif[128];
    
    int choix = 0;

    char* filename = "dic/french-avec-accents-latin1.txt";

    while (1)
    {
        static struct option long_options[] =
        {
            /* These options set a flag. */
            {"stats-words",   no_argument,       0,   'W'},
            {"stats-letters", no_argument,       0,   'L'},
            {"palindromes",   no_argument,       0,   'p'},
            {"anagrammes",    required_argument, 0,   'a'},
            {"question",      required_argument, 0,   'q'},
            {"star",          required_argument, 0,   's'},
            {"scrabble",      required_argument, 0,   'S'},
            {"correction",    required_argument, 0,   'c'},
            {"file",          required_argument, 0,   'f'},
            {"book",          required_argument, 0,   'b'},
            {"help",          no_argument,       0,   '?'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        choix = getopt_long (argc, argv, "WLpa:q:s:S:c:f:?", long_options, &option_index);

        /* Detect the end of the options. */
        if (choix == -1) break;

        switch (choix)
        {

          case 'W':
            en_stats_words = 1;
            break;

          case 'L':
            en_stats_letters = 1;
            break;

          case 'a':
            en_anagrammes = 1;
            strcpy(pal_motif, optarg);
            break;

          case 'p':
            en_palindromes = 1;
            break;

          case 'q':
            en_question = 1;
            strcpy(que_motif, optarg);
            break;

          case 's':
            en_star = 1;
            strcpy(sta_motif, optarg);
            break;

          case 'S':
            en_scrabble = 1;
            strcpy(scr_motif, optarg);
            break;

          case 'c':
            en_corretion = 1;
            strcpy(cor_motif, optarg);
            break;
                
          case 'f':
            filename = optarg;
            break;

          case 'b':
            en_book  = 1;
            filename = optarg;
            break;

          case '?':
            printf("--file              : permet de specifier le dictionnaire à charger (defaut = dic/french.txt.\n");
            printf("--book              : permet de specifier le livre à charger.\n");
            printf("--stats-words       : fourni des statistiques sur les mots présents dans le dictionnaire.\n");
            printf("--stats-letters     : fourni des statistiques sur l'utilisation des lettres dans le dictionnaire.\n");
            printf("--palindromes       : recherche les palindromes présents dans le dictionnaire.\n");
            printf("--anagrammes    ARG : recherche dans le dictionnaire les anagrammes du mot fourni en argument.\n");
            printf("--question      ARG : recherche dans le dictionnaire les corresponces avec le mot fourni en argument (?).\n");
            printf("--star          ARG : recherche dans le dictionnaire les corresponces avec le mot fourni en argument (*).\n");
            printf("--scrabble      ARG : recherche dans le dictionnaire les corresponces avec les lettres fournies en argument.\n");
            printf("--correction    ARG : recherche dans le dictionnaire les mots ressemblants du mot fourni en argument.\n");
            printf("--help              : ces informations :-)\n");
            exit(0);
            break;

          default:
            abort ();
        }
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
        exit(0);
    }

    //declaration du dictionnaire, on ne l'affecte pas : cela depend du fichier à ouvrir
    struct dictionnaire dico;

    //si on ouvre un livre
    if (en_book)
        //ne fonctionne pas entierement -> ne compte que le nombre de mot
        dico = ouvrir_livre(filename);

    //ou le dictionnaire classique
    else 
        dico = ouvrir_fichier(filename);

    if (en_stats_words)
        affiche_statistique_mot(dico);
    
    if (en_stats_letters)
        affiche_statistique_lettre(dico);
    
    if (en_anagrammes)
        affiche_anagramme(dico, pal_motif);

    if (en_palindromes)
        affiche_palindrome(dico);

    if (en_question)
        affiche_pattern1(dico, que_motif);

    if (en_star)
        affiche_pattern2(dico, sta_motif);

    if (en_scrabble)
        affiche_scrabble(dico, scr_motif);

    if (en_corretion)
        affiche_correction(dico, cor_motif);

    libere_memoire(dico);
    
    return 0;
}
