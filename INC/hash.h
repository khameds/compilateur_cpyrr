#ifndef DEF_HASH
#define DEF_HASH

#include "structs.h"
#define HASHTAB_SIZE 36

typedef struct lexeme_struct{
    char * string;
    struct lexeme_struct * next;
    declare dec;			    // déclarations portant ce nom
} * lexeme;

typedef lexeme hashTab[HASHTAB_SIZE];


lexeme storeString(char * string, hashTab index);
int hashCode(char * string);
lexeme stringHash(char * string, lexeme list);
lexeme newLex(char * string);
void freeHashTab(hashTab t);

#endif
