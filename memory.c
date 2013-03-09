


/*
 *	Copyright 2013 (C) Jackson Bahr
 *
 *	This file is part of a STRIPS-algorithm planner
 *	
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or (at
 *	your option) any later version.  This program is distributed in the hope
 *	that it	will be useful, but WITHOUT ANY WARRANTY; without even the
 *	implied	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU General Public License for more details.  You should have
 *	received a copy of the GNU General Public License along with this program.
 *	If not, see <http://www.gnu.org/licenses/>.
 */



#include "strips.h"


Fluent * new_Fluent ()
{
	Fluent * node = (Fluent *) calloc (1, sizeof(Fluent) + 1);
	node->name = (char *) malloc (sizeof(char) + 1);
	// I don't need to malloc obj because id list already has memory
	node->next = NULL;
	return node;
}

ID_List * new_ID_List ()
{
	ID_List * node = (ID_List *) calloc (1, sizeof(ID_List) + 1);
	node->id = (char *) malloc (sizeof(char) + 1);
	node->next = NULL;
	return node;
}

Function * new_Function ()
{
	Function * node = (Function *) calloc (1, sizeof(Function) + 1);
	node->name = (char *) malloc (sizeof(char) + 1);
	node->next = NULL;
	return node;
}

Var_List * new_Var_List ()
{
	Var_List * node = (Var_List *) calloc (1, sizeof(Var_List) + 1);
	node->var = (char *) malloc (sizeof(char) + 1);
	node->next = NULL;
	return node;
}

Action * new_Action ()
{
	Action * act = (Action *) calloc (1, sizeof(Action) + 1);
	act->name = (char *) malloc (sizeof(char) + 1);
	act->next = NULL;
	return act;
}

Stack * new_Stack ()
{
    Stack * stack = (Stack *) calloc (1, sizeof(Stack) + 1);
    stack->type = (char *) malloc (sizeof(char) + 1);
	return stack;
}

Stack_Element * new_Stack_Element ()
{
	Stack_Element * element = (Stack_Element *) calloc (1, sizeof(Stack_Element) + 1);
}

Plan * new_Plan ()
{
	Plan * plan = (Plan *) calloc (1, sizeof(Plan) + 1);
	plan->action = (char *) malloc (sizeof(char) + 1);
	return plan;
}
