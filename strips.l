


/*
 *	Copyright 2013 (C) Jackson Bahr
 *
 *	This file is part of SAWLI (STRIPS Algorithm With Lisp-like Input)
 *	
 *	SAWLI is free software: you can redistribute it and/or modify it under
 *	the terms of the GNU General Public License as published by the Free
 *	Software Foundation, either version 3 of the License, or (at your
 *	option) any later version.  SAWLI is distributed in the hope that it
 *	will be useful, but WITHOUT ANY WARRANTY; without even the implied
 *	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *	the GNU General Public License for more details.  You should have
 *	received a copy of the GNU General Public License along with SAWLI.  If
 *	not, see <http://www.gnu.org/licenses/>.
 */



%{
#include "strips.h"
#include "strips.tab.h"
%}

%%

	/*   SYMBOLS	*/

\;.*			/* comment */;
[ \t\n]+		/* whitespace */;
\(			{ return '('; }
\)			{ return ')'; }
(?i:start)		{ return START_TK; }
(?i:initial)		{ return INITIAL_TK; }
(?i:goal)		{ return GOAL_TK; }
(?i:actions)		{ return ACTIONS_TK; }
(?i:parameters)		{ return PARAMETERS_TK; }
(?i:preconditions)	{ return PRECONDITIONS_TK; }
(?i:effects)		{ return EFFECTS_TK; }
(?i:delete-effects)	{ return DEL_EFFECTS_TK; }

	/*   VALUES	*/

[a-zA-Z]+		{ yylval.sval = strdup(yytext);
			  return IDENTIFIER_TK; }
\?[a-zA-Z]+		{ yylval.sval = strdup(yytext);
			  return VARIABLE_TK; }
<<EOF>>			{ return EOF_TK; }
.			; /* catch all */

%%
