#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBJ_PER_ACTION 10

extern int yylex();
extern int yyparse();
extern FILE *yyin;

extern char * problem_name;

typedef struct _Fluent
{
	char * var;
	char * obj[MAX_OBJ_PER_ACTION];
	struct _Fluent *next;
	struct _Fluent *prev;
} Fluent;

