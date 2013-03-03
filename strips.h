#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**** PARSING ****/
extern int yylex();
extern int yyparse();
extern FILE *yyin;


/**** STRUCTS ****/
typedef struct ID_List_
{
	char * id;
	struct ID_List_ *next;

} ID_List;

typedef struct Fluent_
{
	char * var;
	struct ID_List_ * obj;
	struct Fluent_ *next;
} Fluent;


/**** GLOBAL VARS ****/
extern char * problem_name;
extern Fluent * init_state;
extern Fluent * goal_state;


/**** FUNCTIONS ****/
Fluent * new_Fluent();
