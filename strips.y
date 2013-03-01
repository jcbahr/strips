%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(const char *s);
%}

%error-verbose
%define "parse.lac" "full"

%start start

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
%token EFFECTS_TK
%token DEL_EFFECTS_TK
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


start:
	'(' START_TK IDENTIFIER_TK
	    initial goal actions ')'	{  };


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
	    preconditions effects delete_effects ')'		{ };


parameters:
	'(' PARAMETERS_TK var_star ')';

preconditions:
	'(' PRECONDITIONS_TK var_list ')'		{ printf("precondition_list\n"); };

effects:
	  '(' EFFECTS_TK var_list ')'			{ printf("effects\n"); };

delete_effects:
	  '(' DEL_EFFECTS_TK var_list ')'		{ printf("delete_effects\n"); };

fluent_list:
	  '(' IDENTIFIER_TK id_star ')'
	| '(' IDENTIFIER_TK id_star ')' fluent_list	{ printf("fluent_list\n"); };

id_star:
	  /* nothing */
	| IDENTIFIER_TK id_star
	;

var_list:
	  '(' IDENTIFIER_TK var_star ')';

var_star:
	  /* nothing */
	| VARIABLE_TK var_star			{  }
	;



%%

void yyerror(const char *s)
{
	printf("\nError: %s\n",s);
	fprintf(stderr,"\nError: %s\n",s);
	exit(-1);
}