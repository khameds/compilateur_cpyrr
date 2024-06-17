#ifndef DEF_STRUCTS
#define DEF_STRUCTS

/* CASE DE LA TABLE DE DECLARATIONS */
typedef struct declare_struct{
    char nature;
    struct declare_struct * next;
    int region;			    // Indique la région où se trouve la déclaration
    void * descr;		    // Pointeur sur le tableau des types
    int exec;			    // C'est quoi, déja ?
} * declare;

#endif
