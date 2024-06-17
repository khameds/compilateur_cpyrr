/* LEX du projet */

%{
	#include "y.tab.h"
%}

%%
\+				{return(PLUS);}
\-				{return(MOINS);}
\*				{return(MULT);}
\/				{return(DIV);}
\%				{return(MOD);}
\;				{return(POINT_VIRGULE);}
\(				{return(PO);}
\)				{return(PF);}
\{				{return(DEBUT);}
\}				{return(FIN);}
[[]			    	{return(CO);}
[]]				{return(CF);}
\:				{return(DEUX_POINTS);}
\,				{return(VIRGULE);}
prog				{return(PROG);}
(bigbang|begin)			{return(DEBUT);}
(apocalypse|end)		{return(FIN);}
if			    	{return(IF);}
then			    	{return(THEN);}
elif				{return(ELIF);}
else				{return(ELSE);}
while				{return(WHILE);}
do				{return(DO);}
for				{return(FOR);}
read				{return(LIRE);}
write				{return(ECRIRE);}
call				{return(APPEL);}
return				{return(RETURN);}
function			{return(FONCTION);}
procedure			{return(PROCEDURE);}
struct				{return(STRUCT);}
struct_end			{return(STRUCT_END);}
type				{return(TYPE);}
var				{return(VARIABLE);}
int				{return(INT);}
char				{return(CHAR);}
string				{return(STRING);}
bool				{return(BOOL);}
float				{return(FLOAT);}
tab				{return(TAB);}
\/\*([^*]|\*+[^*/])*\*+\/	{;}	/* Commentaire multilignes */
\/\/.*				{;}	/* Commentaire sur une seule ligne */
\+\+				{return(INC);}
\-\-				{return(DEC);}
\.\.				{return(POINT_POINT);}
:=				{return(OPAFF);}
\+=				{return(PLAFF);}
\-=				{return(MINAFF);}
\*=				{return(MULTAFF);}
\/=				{return(DIVAFF);}
\%=				{return(MODAFF);}
\.=				{return(CATAFF);}
==				{return(EGAL);}
\<				{return(INF);}
>				{return(SUP);}
\<=				{return(INFEGAL);}
>=				{return(SUPEGAL);}
!=				{return(DIFF);}
\!				{return(NOT);}
\.				{return(POINT);}
true				{return(TRUE);}
false				{return(FALSE);}
[a-zA-Z][a-zA-Z0-9_]*		{return(IDF);}
(0|[1-9][0-9]*)   		{return(CSTE_INT);} 
(0|[1-9][0-9]*)\.[0-9]+		{return(CSTE_FLOAT);}
\'[a-zA-Z]\'			{return(CSTE_CHAR);}
\"[^\"\n]+\"			{return(CSTE_STRING);}
\&\&				{return(AND);}
\|\|				{return(OR);}
(.|\n)				{;}

%%
