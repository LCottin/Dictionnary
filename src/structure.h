#ifndef _structure_
#define _structure_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mot_dico 
{
	char* contenu;
	char* accent;
	unsigned nb_lettre;
};

struct dictionnaire 
{
	struct mot_dico* mots;
	unsigned nombre_mot;
};

#endif