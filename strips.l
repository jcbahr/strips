%{
#include "strips.h"
#include "strips.tab.h"

int linenum = 0;

%}

%%

	/*	SYMBOLS		*/

\;.*					/* comment */;
[ \t\n]+				/* whitespace */;
\(					{ return '('; }
\)					{ return ')'; }
(?i:start)				{ return START_TK; }
(?i:initial)				{ return INITIAL_TK; }
(?i:goal)				{ return GOAL_TK; }
(?i:actions)				{ return ACTIONS_TK; }
(?i:parameters)				{ return PARAMETERS_TK; }
(?i:preconditions)			{ return PRECONDITIONS_TK; }
(?i:effects)				{ return EFFECTS_TK; }
(?i:delete-effects)			{ return DEL_EFFECTS_TK; }

	/*	VALUES		*/

[a-zA-Z]+				{ yylval.sval = strdup(yytext);
					  return IDENTIFIER_TK; }
\?[a-zA-Z]+				{ yylval.sval = strdup(yytext);
					  return VARIABLE_TK; }
<<EOF>>					{ return EOF_TK; }
.					; /* catch all */

%%
