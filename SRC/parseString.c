#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseString.h"


char ** parseString(char * input){
    char state = 0;
    char ** ret;
    int letter = 0, word = -1, i;
    for (i=0; state != 3; i++){
	if (input[i] == '\0'){
	    state = 3;
	    word ++;
	    ret = (char **) realloc (ret, (word + 1) * sizeof(char *));
	    ret[word] = NULL;
	}
	else if (state == 0){
	    switch (input[i]){
		case '"' :
		    state = 2;
		    letter = 0;
		    word ++;
	    	    ret = (char **) realloc (ret, (word + 1) * sizeof(char *));
		    ret[word] = (char *) malloc (sizeof(char));
		    break;
		case ' ' :
		    break;
		default :
		    state = 1;
		    letter = 0;
		    word ++;
	    	    ret = (char **) realloc(ret, (word + 1) * sizeof(char *));
		    ret[word] = (char *) malloc (sizeof(char));
		    i--;
	    }
	}
	else if (state == 1){
	    ret[word] = (char *)realloc(ret[word], (letter + 1) * sizeof(char));
	    switch (input[i]){
		case ' ':
		    ret[word][letter] = '\0';
		    state = 0;
		    break;
		case '\\' :
		    i++;
		    ret[word][letter] = input[i];
		    letter ++;
		    break;
		default :
		    ret[word][letter] = input[i];
		    letter ++;
	    }
	}
	else if (state == 2){
	    ret[word] = (char *)realloc(ret[word], (letter + 1) * sizeof(char));
	    switch (input[i]){
		case '"':
		    ret[word][letter] = '\0';
		    state = 0;
		    break;
		case '\\' :
		    i++;
		    ret[word][letter] = input[i];
		    letter ++;
		    break;
		default :
		    ret[word][letter] = input[i];
		    letter ++;
	    }
	}
    }
    return(ret);
}


int tabLength(char ** tab){
    int length;
    for (length=0; tab[length] != NULL; length++);
    return(length);
}
