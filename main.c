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


	print_fluent("INIT",init_state);
	print_fluent("GOAL",goal_state);

	print_actions();
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


int print_actions (Action * actions)
{
	while(actions->next)
	{
		printf("\n%s:\n",actions->name);
/*
		if(actions->param)
		{
			printf(" with parameters '%s'",actions->param->var);
		}
		actions->param = actions->param->next;
		while(actions->param->var)
		{
			printf(", '%s'",actions->param->var);
			actions->param = actions->param->next;
		}
		printf("\n");
*/
//		print_function("Preconditions",actions->pre);
//		print_function("Add effects",actions->add);
//		print_function("Delete effects",actions->del);

		actions = actions->next;
	}
}
