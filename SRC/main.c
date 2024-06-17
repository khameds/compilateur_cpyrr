#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "declare.h"
#include "err.h"


int main(){
    char input[256];
    char ** wordTab;
    int cont = 1;
    int place = 0;
    int i;
    hashTab index;
    for (i=0; i<HASHTAB_SIZE ; i++)
	index[i] = NULL;

    /* Nettoyage de la console : varie selon l'OS */
    
    #ifdef __unix__
    system("clear");
    #endif

    #ifdef _WIN32
    system("cls");
    #endif


    printf("\t-=Test console for hashing tool=-\n\t\t[By DJ Pick-Up]\n\nUsage :\n- Enter a string for it to be stored in the hash table; the console will return this string's adress\nIf it has already been stored, it won't store it but still return its adress.\n- \"stop\" to stop\n\n");
    while (cont){
	printf("> ");
	for (i=0; i<255; input[i]=' ', i++);
	input[i] = '\0';
	fflush(stdin);
	gets(input);
	if (strlen(input) > 0){
	    wordTab = parseString(input);

	    if (!strcmp(wordTab[0], "stop")){
		freeHashTab(index);
		printf("Convinced ?\nGoodbye !\n");
		cont = 0;
	    }
	    else if (!strcmp(wordTab[0], "help")){
		help();
	    }
	    else if (!strcmp(wordTab[0], "declare") && tabLength(wordTab) > 2){
		lexeme l = storeString(wordTab[2], index);
		char nat;
		declare d;
		if (!strcmp(wordTab[1], "struct"))
		    nat = 1;
		else if (!strcmp(wordTab[1], "tab"))
		    nat = 2;
		else if (!strcmp(wordTab[1], "var"))
		    nat = 3;
		else if (!strcmp(wordTab[1], "proc"))
		    nat = 4;
		else if (!strcmp(wordTab[1], "fun"))
		    nat = 5;
		else
		    err(UNKNOWN);

		d = newDec(nat, l, 0, NULL, 0);
		printf("@%p \t: %s %s (%p)\n", d, wordTab[1], wordTab[2], l);

	    }
	    else{
		printf("! Commande \"%s\" non reconnue\n", input);
	    }
	}
    }
    return(0);
}


void help(){
    // Commandes générales
    printf("? Help Section ?\n----------------\n\n-> stop : exits\n-> help : displays this help\n");
    // Déclarations
    printf("-> declare :\n\t-> var <name> <type>\n\t-> fun <name> <returned_type> [<arg_name> <arg_type>]*\n\t-> proc <name> [<arg_name> <arg_type>]*\n\t-> tab <name> <type> [ ( <dim_min> , <dim_max> ) ]+\n\t-> struct name [<field_name> <field_type>]\n");
}
