%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(const char *s);
%}

%union
{
	char *sval;
}

%token START_TK
%token INITIAL_TK
%token GOAL_TK
%token ACTIONS_TK
%token PARAMETERS_TK
%token PRECONDITIONS_TK
%token RESULT_TK
%token EOF_TK 0 "end of file"

%token PLUS
%token MINUS
%token TIMES
%token DIVIDE

%token AND_TK
%token OR_TK
%token NOT_TK 

%token <sval> IDENTIFIER_TK
%token <sval> VARIABLE_TK

%%


input:
	  start_expr EOF_TK 
;

start_expr:
	'(' START_TK initial goal actions ')'	{ printf("HELLO"); };


/********** INITIAL **********/

initial:
	'(' INITIAL_TK fluent_list ')'		{ printf("initial"); };


/********** GOAL **********/

goal:
	'(' GOAL_TK fluent_list ')'		{ puts("goal"); };


/********** ACTIONS **********/

actions:
	'(' ACTIONS_TK action_plus ')'		{ puts("actions"); };

action_plus:
	  action				{  }
	| action action_plus			{  }
	;

action:
	'(' IDENTIFIER_TK parameters
	    preconditions results ')'		{  };


parameters:
	'(' PARAMETERS_TK var_star ')';


var_star:
	  /* nothing */
	| VARIABLE_TK var_star			{  }
	;

preconditions:
	'(' PRECONDITIONS_TK var_star ')'		{ printf("precondition_list\n"); };


results:
	  '(' RESULT_TK fluent_list ')'			{ printf("result_list\n"); };


fluent_list:
	  '(' VARIABLE_TK id_star ')'			{ printf("int fluent_expr\n"); };

id_star:
	  /* nothing */
	| IDENTIFIER_TK id_star
	;



%%

/*main()
{
	extern linenum;
	char *filename = "input";
	FILE *filepointer = fopen(filename,"r");
	//check if valid file
	if(!filepointer)
	{
		printf("Woah dude. There ain't no %s file there.\n",filename);
		return -1;
	}
	//set flex to read from this file, not from stdin
	yyin = filepointer;
	while (!feof(yyin)) //not the file's EOF
	{
		yyparse();
	}

}
*/

void yyerror(const char *s)
{
	printf("\nError: %s\n",s);
	exit(-1);
}
