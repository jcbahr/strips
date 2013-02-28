%{
#include <stdio.h>
#include "strips.tab.h"

int linenum = 0;

%}

%%

	/*	SYMBOLS		*/

[ \t]+					/* whitespace */;
\;+.*					/* comment */;
'\n'					{ linenum++; }
(?i:start)				{ printf("hi"); return START_TK; }
(?i:initial)				{ return INITIAL_TK; }
(?i:goal)				{ return GOAL_TK; }
(?i:actions)				{ return ACTIONS_TK; }
(?i:parameters)				{ return PARAMETERS_TK; }
(?i:preconditions)			{ return PRECONDITIONS_TK; }
(?i:result)				{ return RESULT_TK; }
	/*	OPERATORS	*/

\+					{ return PLUS; }
-					{ return MINUS; }
\*					{ return TIMES; }
\/					{ return DIVIDE; }

	/*	BOOL OPs	*/

(?i:and)				{ return AND_TK; }
(?i:or)					{ return OR_TK; }
(?i:not)				{ return NOT_TK; }

	/*	VALUES		*/

[a-zA-Z]+				{ yylval.sval = strdup(yytext);
					  return IDENTIFIER_TK; }
\?[a-zA-Z]+				{ yylval.sval = strdup(yytext);
					  return VARIABLE_TK; }
<<EOF>>					{ return EOF_TK; }
.					; /* catch all */

%%
