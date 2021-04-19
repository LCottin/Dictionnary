#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

extern void affiche_anagramme(const struct dictionnaire dico, const char* mot);
extern int indice_alphabet(const char lettre);
extern int est_anagramme(const char* mot_dico, const char* mot);