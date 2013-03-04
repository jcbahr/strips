


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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**** PARSING ****/
extern int yylex();
extern int yyparse();
extern FILE *yyin;


/**** STRUCTS ****/
typedef struct ID_List_
{
	char * id;
	struct ID_List_ *next;

} ID_List;

typedef struct Fluent_
{
	char * name;
	struct ID_List_ * obj;
	struct Fluent_ *next;
} Fluent;


typedef struct Var_List_
{
	char * var;
	struct Var_List_ *next;

} Var_List;

typedef struct Function_
{
	char * name;
	struct Var_List_ * obj;
	struct Function_ *next;
} Function;

typedef struct Action_
{
	char * name;
	struct Function_ *add;
	struct Function_ *del;
	struct Function_ *pre;
	struct Var_List_ *param;
	struct Action_ *next;
} Action;


/**** GLOBAL VARS ****/
extern char * problem_name;
extern Fluent * init_state;
extern Fluent * goal_state;
extern Action * actions;

/**** FUNCTIONS ****/
Fluent * new_Fluent();
ID_List * new_ID_List();
Var_List * new_Var_List();
Function * new_Function();
Action * new_Action();
