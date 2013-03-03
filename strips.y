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
	Var_List *varval;
	Function *funcval;
	Action *actval;
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

%token <sval> IDENTIFIER_TK
%token <sval> VARIABLE_TK

%type <fluentval> fluent
%type <idval> id_star
%type <varval> var_star parameters
%type <funcval> function_plus preconditions effects delete_effects
%type <actval> action_list

%%


start:
	'(' START_TK IDENTIFIER_TK
	    initial goal actions ')'		{ problem_name = malloc (strlen ($3) + 1);
	    					  strcpy(problem_name, $3); };


initial:
	'(' INITIAL_TK fluent ')'		{ init_state = $3; };


goal:
	'(' GOAL_TK fluent ')'			{ goal_state = $3; };


/********** ACTIONS **********/

actions:
	'(' ACTIONS_TK action_list ')'		{  };

action_list:
	  '(' IDENTIFIER_TK parameters preconditions
	      effects delete_effects ')'
	      						{ $$ = new_Action();
	  						  strcpy($$->name, $2);
							  $$->param = $3;
							  $$->pre = $4;
							  $$->add = $5;
							  $$->del = $6;
							  $$->next = NULL; }

	| '(' IDENTIFIER_TK parameters preconditions
	      effects delete_effects ')' action_list	{ $$ = new_Action();
	      						  strcpy($$->name, $2);
							  $$->param = $3;
							  $$->pre = $4;
							  $$->add = $5;
							  $$->del = $6;
							  $$->next = $8; };

parameters:
	'(' PARAMETERS_TK var_star ')'			{ $$ = $3; };

preconditions:
	'(' PRECONDITIONS_TK function_plus ')'		{ $$ = $3; };

effects:
	  '(' EFFECTS_TK function_plus ')'		{ $$ = $3; };

delete_effects:
	  '(' DEL_EFFECTS_TK function_plus ')'		{ $$ = $3; };

fluent:
	  '(' IDENTIFIER_TK id_star ')'			{ $$ = new_Fluent();
							  strcpy($$->name, $2);
							  $$->obj = $3; 
							  $$->next = NULL; }

	| '(' IDENTIFIER_TK id_star ')'	fluent		{ $$ = new_Fluent();
							  strcpy($$->name, $2);
							  $$->obj = $3;
							  $$->next = $5; };

id_star:
	  /* nothing */					{ $$ = new_ID_List();
	  						  $$->id = NULL; }

	| IDENTIFIER_TK	id_star				{ $$ = new_ID_List();
							  strcpy($$->id, $1);
							  $$->next = $2;;}
							  
	;

function_plus:
	  '(' IDENTIFIER_TK var_star ')'		{ $$ = new_Function();
	  						  strcpy($$->name, $2);
							  $$->obj = $3;
							  $$->next = NULL; }

	| '(' IDENTIFIER_TK var_star ')' function_plus	{ $$ = new_Function();
							  strcpy($$->name, $2);
							  $$->obj = $3;
							  $$->next = $5; };

var_star:
	  /* nothing */					{ $$ = new_Var_List();
	  						  $$->var = NULL; }

	| var_star VARIABLE_TK				{ $$ = new_Var_List();
							  $$->var = $2;
							  $$->next = $1; }
	;



%%

void yyerror(const char *s)
{
	printf("\nError: %s\n",s);
	fprintf(stderr,"\nError: %s\n",s);
	exit(-1);
}
