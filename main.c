


/*
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



#include "strips.h"
char * problem_name;
Fluent * init_state;
Fluent * goal_state;
Function * add_effects; 
Function * del_effects;
Function * preconditions;
Action * actions;

int main (int argc, char *argv[])
{
        extern FILE *yyin;
        char *filename;
        if (argc != 2)
        {
                printf ("Usage: strips [FILE]\n");
                exit (EXIT_FAILURE);
        }

	filename = malloc (strlen (argv[1]) + 1);
        strcpy (filename, argv[1]);
	FILE *filepointer = fopen (filename, "r");

	if (!filepointer)
	{
                printf ("Error: '%s' not found!\n",argv[1]);
                exit (EXIT_FAILURE);
        }

	yyin = filepointer;
	while (!feof(yyin))
	{
		yyparse();
	}
	fclose(filepointer);


//	print_fluent("INIT",init_state);
//	print_fluent("GOAL",goal_state);
//	print_actions(actions);
}

int print_fluent (char * name, Fluent * state)
{
	printf("\n%s:\n",name);
	while(state)
	{
		printf("Fluent '%s'",state->name);
		if(state->obj)
		{
			printf(" with objects '%s'",state->obj->id);
		}
		state->obj = state->obj->next;
		while(state->obj->id)
		{
			printf(", '%s'",state->obj->id);
			state->obj = state->obj->next;
		}
		printf("\n");
		state = state->next;
	}
	
}


int print_function (char * name, Function * func)
{
	printf("\n%s:\n",name);
	while(func)
	{
		printf("Function '%s'",func->name);
		if(func->obj)
		{
			printf(" with objects '%s'",func->obj->var);
		}
		func->obj = func->obj->next;
		while(func->obj->var)
		{
			printf(", '%s'",func->obj->var);
			func->obj = func->obj->next;
		}
		printf("\n");
		func = func->next;
	}
}

int print_var_list (char * name, Var_List * param)
{
	if(param)
	{
		printf("%s: '%s'",name,param->var);
	}
	param = param->next;
	while (param->var)
	{
		printf(", '%s'",param->var);
		param = param->next;
	}
	printf("\n");
}

int print_actions (Action * actions)
{
	printf("\n\nACTION %s:\n",actions->name);
	print_var_list("Parameters",actions->param);
	print_function("Preconditions",actions->pre);
	print_function("Add effects",actions->add);
	print_function("Delete effects",actions->del);
	while (actions->next)
	{
		actions = actions->next;
		print_function("Preconditions",actions->pre);
		print_function("Add effects",actions->add);
		print_function("Delete effects",actions->del);
	}
}
