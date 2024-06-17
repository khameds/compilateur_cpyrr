#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "err.h"


lexeme storeString(char * string, hashTab index){
    int code = hashCode(string);
    /* Si la liste est vide à cet index... */
    if (index[code] == NULL){
	index[code] = newLex(string);
	return(index[code]);
    }
    return(stringHash(string, index[code]));
}


int hashCode(char * string){
    /* Retourne le hashcode associé a "string" */
    int code = 0;
    int length = strlen(string);
    int i;
    for (i=0; i<length; i++){
	code += string[i];
    }
    code %= HASHTAB_SIZE;
    return(code);
}


lexeme stringHash(char * string, lexeme list){
    lexeme cur = NULL;
    char stop = 0; // Variable terminant la boucle si "string" est déja présent parmi les lexèmes (stop = 1) ou si la liste a été totalement parcourue (stop = 2)
    for (cur=list; !stop;){
	if (!strcmp(cur->string, string))
	    stop = 1;
	else if (cur->next == NULL)
	    stop = 2;
	else
	    cur = cur->next;
    }
    /* Si "string" a été trouvé */
    if (stop == 1)
	return(cur);
    /* Si on a atteint la fin de la liste sans succès */
    else{
	cur->next = newLex(string);
	return(cur->next);
    }	
}


lexeme newLex(char * string){
    /* Crée un nouveau "lexeme", qui sera ajouté en fin de liste */
    int i;
    int length = strlen(string) + 1; // Compte le '\0' dans les caractères de la chaîne
    lexeme new = NULL;
    if ((new = (lexeme)malloc(sizeof(struct lexeme_struct))) == (lexeme) NULL){
	err(ALLOC);
    }
    new->next = NULL;  
    if ((new->string = (char *)malloc(sizeof(char) * length)) == (char *) NULL){
	err(ALLOC);
    }
    new->dec = NULL;
    for(i=0; i<length; i++)
	new->string[i] = string[i];
    return(new);
}

void freeHashTab(hashTab t){
    /* Libère chaque élément de chaque liste du tableau de hashage, de manière propre */
    int i = 0;
    lexeme l = NULL, l_next = NULL;
    declare d = NULL, d_next = NULL;
/* TEST */  fprintf(stdout, "\n\n¤ Libération de la mémoire :\n");
    for (i=0; i<HASHTAB_SIZE; i++){
	l = t[i];
	while (l != NULL){
/* TEST */  fprintf(stdout, "\t-> Lexeme %s (@%p)\n", l->string, l);
	    l_next = l->next;
	    free(l->string);
	    /* Libération des tables de déclarations associées */
	    for (d=l->dec; d != NULL;){
/* TEST */  fprintf(stdout, "\t\t-> Nature : %d (@%p)\n", d->nature, d);
		d_next = d->next;
		free(d);
		d = d_next;
	    }
	    free(l);
	    l = l_next;
	}
    }
/* TEST */  fprintf(stdout, "¤ Mémoire libérée\n");
}

