%token PROG DEBUT FIN PROCEDURE FONCTION VARIABLE TYPE STRUCT STRUCT_END TAB RETURN APPEL
%token IF THEN ELSE ELIF WHILE DO FOR
%token LIRE ECRIRE
%token PO PF CO CF POINT_VIRGULE POINT POINT_POINT DEUX_POINTS VIRGULE
%token OPAFF PLAFF MINAFF MULTAFF DIVAFF MODAFF CATAFF
%token INT CHAR BOOL FLOAT STRING
%token CSTE_INT CSTE_FLOAT CSTE_CHAR CSTE_STRING TRUE FALSE
%token EGAL DIFF SUP INF SUPEGAL INFEGAL
%token IDF
%token PLUS MOINS MULT DIV MOD
%token INC DEC
%token NOT AND OR
%{
    #include "y.tab.h"
%}
%%
prog			: PROG corps
			;

corps			: liste_declarations instructions
			| instructions
		    	;

liste_declarations	: declaration_fun
			| liste_declarations declaration_fun
			;

instructions		: DEBUT liste_instructions FIN
			;

liste_instructions	: instruction_cond
			| liste_instructions instruction_cond
			;

declaration_fun		: declaration POINT_VIRGULE
			| declaration_procedure
			| declaration_fonction
			;

instruction_cond	: instruction POINT_VIRGULE
			| condition
			| while
			| for
			;

declaration		: declaration_type
			| declaration_var
			;

declaration_type	: TYPE IDF DEUX_POINTS liste_declar_type
			;

liste_declar_type	: STRUCT liste_champs STRUCT_END
			| TAB CO liste_dimensions CF DEUX_POINTS nom_type
		    	;

liste_dimensions	: dimension
			| liste_dimensions VIRGULE dimension
			;

dimension		: expression_num POINT_POINT expression_num
/*		           ^^^^^^^^^^^^^^	           ^^^^^^^^^^^^^^ *
 *			          indice_min		             indice_max   */
			;

liste_champs		: champ
		        | liste_champs VIRGULE champ
			;

champ			: IDF DEUX_POINTS nom_type
			;

nom_type		: type_simple
			| IDF
			;

type_simple		: FLOAT
			| INT
			| CHAR
			| BOOL
			| STRING CO CSTE_INT CF
/* A quel type		  ^^^^^^                *
 * ça correspond ??	  Tableau de CHAR ?	*/
			;

declaration_var		: VARIABLE IDF DEUX_POINTS nom_type
			;

declaration_procedure	: PROCEDURE IDF parametres corps
			;

declaration_fonction	: FONCTION IDF DEUX_POINTS nom_type parametres corps
			;

parametres		: PO PF
			| PO liste_params PF
			;

liste_params		: param
			| liste_params VIRGULE param
			;

param			: IDF DEUX_POINTS type_simple
			;

instruction		: 
			| affectation
			| appel
			| RETURN result
			| entree_sortie
			;

result			: PO PF /* cas d'une procédure */
			| expression
			| expression_string
			;

entree_sortie		: read
			| write
			;

read			: LIRE PO liste_variables PF
			;

liste_variables		: variable
			| liste_variables VIRGULE variable
			;

write			: ECRIRE PO format suite_ecriture PF
			;

format			: CSTE_STRING
			;

suite_ecriture		: 
			| VIRGULE variable suite_ecriture
			;

appel			: APPEL IDF arguments
			;

arguments		: PO PF /* Cas d'une procédure */
			| PO liste_args PF
			;

liste_args		: arg
			| liste_args VIRGULE arg
			;

arg			: expression
			;

affectation		: variable operateur_affect expression
			| variable operateur_affect expression_string
			| variable inc_ou_dec
			| inc_ou_dec variable
			;

operateur_affect	: OPAFF
			| PLAFF
			| MINAFF
			| MULTAFF
			| DIVAFF
			| MODAFF
			| CATAFF
			;

variable		: var_simple
			| tabl
			| variable POINT tabl
			| variable POINT var_simple
			;

tabl			: IDF CO tab_params CF
			| tabl CO tab_params CF
			;

var_simple		: IDF			    /* variable */
			;

tab_params		: expression
			| tab_params VIRGULE expression
			;

condition		: IF tests THEN instructions else
			;

else			:  
			| ELIF tests THEN instructions else
			| ELSE instructions
			;

tests			: PO test PF
			;

test			: expression
			;

comparaison		: expression_num comp expression_num
			;

comp			: SUP /* > */
			| SUPEGAL /* >= */
			| EGAL /* == */
			| INFEGAL /* <= */
			| INF /* < */
			| DIFF /* != */
			;


while			: WHILE tests DO instructions
			;

for			: FOR PO affectation POINT_VIRGULE test POINT_VIRGULE affectation PF instructions
			;

expression		: exp_bool1
			;

exp_bool1		: exp_bool1 OR exp_bool2
			| exp_bool2
			;

exp_bool2		: exp_bool2 AND exp_bool3
			| exp_bool3
			;

exp_bool3		: NOT exp_bool4
			| exp_bool4
			;

exp_bool4		: cste_bool
			| comparaison
			| expression_num
			;
	   
cste_bool		: TRUE
			| FALSE
			;

expression_num		: exp1
			;

exp1			: exp1 PLUS exp2
			| exp1 MOINS exp2
			| exp2
			;

exp2			: exp2 MULT exp3
			| exp2 DIV exp3
			| exp2 MOD exp3
			| exp3
			;

exp3			: MOINS exp4
			| exp4
			;

exp4			: CSTE_INT
			| CSTE_FLOAT
			| CSTE_CHAR	/* Prend la valeur ASCII du caractère */
			| exp5
			| PO expression PF
			| appel
			;

exp5			: variable
			| variable inc_ou_dec
			| inc_ou_dec variable
			;

inc_ou_dec		: INC
			| DEC
			;

expression_string	: expression_string POINT CSTE_STRING
			| CSTE_STRING
			;
%%
