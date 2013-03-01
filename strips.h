#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;

extern char * problem_name;

typedef struct Fluent_
{
	char * var;
	struct ID_List_ * obj;
	struct Fluent_ *next;
} Fluent;

typedef struct ID_List_
{
	char * id;
	struct ID_List_ *next;

} ID_List;

