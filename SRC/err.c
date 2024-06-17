#include <stdio.h>
#include <stdlib.h>
#include "err.h"


void err(int errnum){
    switch (errnum){
	// ERREURS NON-CRITIQUES
	// ERREURS CRITIQUES
	case ALLOC :
	    fprintf(stderr, "! Erreur d'allocation de mémoire !\n");
	    exit(EXIT_FAILURE);
	default :
	    fprintf(stderr, "! Une erreur inconnue est survenue : arret du programme\n");
	    exit(EXIT_FAILURE);
    }
}
