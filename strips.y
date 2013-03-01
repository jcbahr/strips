%{
#include "strips.h"

void yyerror(const char *s);

%}

%error-verbose
%define "parse.lac" "full"

%start start

%union
{
	char *sval;
	Fluent *fluentval;
	ID_List *idval;
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

%type <fluentval> fluent fluent_list
%type <idval> id_star

%%


start:
	'(' START_TK IDENTIFIER_TK
	    initial goal actions ')'		{ problem_name = malloc (strlen ($3) + 1);
	    					  strcpy(problem_name, $3); };


/********** INITIAL **********/

initial:
	'(' INITIAL_TK fluent_list ')'		{ };


/********** GOAL **********/

goal:
	'(' GOAL_TK fluent_list ')'		{  };


/********** ACTIONS **********/

actions:
	'(' ACTIONS_TK action_plus ')'		{  };

action_plus:
	  action				{  }
	| action_plus action			{  }
	;

action:
	'(' IDENTIFIER_TK parameters
	    preconditions effects delete_effects ')'		{  };


parameters:
	'(' PARAMETERS_TK var_star ')';

preconditions:
	'(' PRECONDITIONS_TK var_list ')'		{  };

effects:
	  '(' EFFECTS_TK var_list ')'			{  };

delete_effects:
	  '(' DEL_EFFECTS_TK var_list ')'		{  };

fluent:
	'(' IDENTIFIER_TK id_star ')'			{ Fluent * fluent;
							  fluent->var = malloc (strlen ($2) +1);
							  strcpy(fluent->var, $2);
							  fluent->obj = $3; 
							  fluent->next = NULL; };

fluent_list:
	  fluent					{  }
	| fluent fluent_list				{  }
	;

id_star:
	  /* nothing */					{ $$ = malloc (sizeof(ID_List));
	  						  $$->id = NULL;
							  $$->next = NULL; }

	| IDENTIFIER_TK	id_star				{ $$ = malloc (sizeof(ID_List));;
							  strcpy($$->id, $1);
							  $$->next = $2; }
							  
	;

var_list:
	  '(' IDENTIFIER_TK var_star ')';

var_star:
	  /* nothing */
	| var_star VARIABLE_TK
	;



%%

void yyerror(const char *s)
{
	printf("\nError: %s\n",s);
	fprintf(stderr,"\nError: %s\n",s);
	exit(-1);
}
