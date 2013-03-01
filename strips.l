%{
#include <stdio.h>
#include "strips.tab.h"

int linenum = 0;

%}

%%

	/*	SYMBOLS		*/

[ \t\n]+				/* whitespace */;
\(					{ return '('; }
\)					{ return ')'; }
(?i:start)				{ puts("start"); return START_TK; }
(?i:initial)				{ puts("init"); return INITIAL_TK; }
(?i:goal)				{ return GOAL_TK; }
(?i:actions)				{ return ACTIONS_TK; }
(?i:parameters)				{ return PARAMETERS_TK; }
(?i:preconditions)			{ return PRECONDITIONS_TK; }
(?i:effects)				{ return EFFECTS_TK; }
(?i:delete-effects)			{ return DEL_EFFECTS_TK; }


	/*	VALUES	\;+.*					 comment ;*/

[a-zA-Z]+				{ yylval.sval = strdup(yytext);
					  printf("identifier: %s\n",yylval.sval);
					  return IDENTIFIER_TK; }
\?[a-zA-Z]+				{ yylval.sval = strdup(yytext);
					  return VARIABLE_TK; }
<<EOF>>					{ return EOF_TK; }
.					; /* catch all */

%%
