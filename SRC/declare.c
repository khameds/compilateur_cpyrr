#include <stdio.h>
#include <stdlib.h>
#include "declare.h"
#include "hash.h"
#include "err.h"


/*********************************************
 * decVar declareTruc(lexeme name, ...){     *
 *     1) On teste qu'il n'y ait pas déja    *
 * une declaration de même nom ET nature     *
 *     2) On stocke la déclaration en fin de *
 * liste des déclaration du lexeme lex	     *
 *     3) On gère les arguments...	     *
 *********************************************/


declare newDec(int nature, lexeme name, int reg, void * descr, int exec){
    declare new = NULL;

    if (decSeek(name->dec, nature)){
	printf("! %s a déja été déclaré pour un élément de même nature\n", name->string);
	return(NULL);
    }
    
    if ((new = (declare) malloc (sizeof(struct declare_struct))) == NULL){
	err(ALLOC);
    }

    new->nature = nature;
    new->next = name->dec;
    new->region = reg;

    /* Remplissage du champ description */
    new->descr = descr;
    new->exec = exec;

    name->dec = new;

    return(new);
}


int decSeek(declare list, int nat){
    declare cur;
    for (cur=list; cur != NULL; cur = cur->next){
	/* Si on trouve un élément de même nom ET de même nature ! */
	if (cur->nature == nat){
	    return(1);
	}
    }
    return(0);
}
