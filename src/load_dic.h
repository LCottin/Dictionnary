#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"

extern struct dictionnaire ouvrir_fichier(const char* nom_fichier);
extern void libere_memoire(struct dictionnaire dico);
extern void convert_word(char* word);
extern void convert_to_utf8(char* dst, const char* src);
extern char convert_char(unsigned char c);