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

%token <sval> IDENTIFIER_TK
%token <sval> VARIABLE_TK

%type <fluentval> fluent fluent_list
%type <idval> id_star

%%


start:
	'(' START_TK IDENTIFIER_TK
	    initial goal actions ')'		{ problem_name = malloc (strlen ($3) + 1);
	    					  strcpy(problem_name, $3); };


initial:
	'(' INITIAL_TK fluent_list ')'		{ };


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
	'(' IDENTIFIER_TK id_star ')'			{ $$ = new_Fluent();
							  strcpy($$->var, $2);
							  $$->obj = $3; 
							  $$->next = NULL; //redundant

							//testing
							  Fluent * fl = $$;
							  printf("%s (",fl->var);
							  printf("%s",fl->obj->id);
							  fl->obj = fl->obj->next;
							  while(fl->obj->next)
							  {
							  	printf(", %s",fl->obj->id);
								fl->obj = fl->obj->next;
							  }
							  printf(")\n");
							  printf("next fluent is %s\n",fl->next->var);};

fluent_list:
	  fluent					{ $$ = $1;
	  						  $1->next = NULL; }
	| fluent fluent_list				{ $$ = $1;
							  $1->next = $2; }
	;

id_star:
	  /* nothing */					{ $$ = malloc (sizeof(ID_List)+1);
	  						  $$->id = NULL;
							  $$->next = NULL; }

	| IDENTIFIER_TK	id_star				{ $$ = malloc (sizeof(ID_List));;
							  $$->id = malloc(strlen ($1) + 1);
							  strcpy($$->id, $1);
							  $$->next = $2;;}
							  
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
