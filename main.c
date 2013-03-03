#include "strips.h"
char * problem_name;
Fluent * init_state;
Fluent * goal_state;

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
	while (!feof(yyin)) //not the file's EOF
	{
		yyparse();
	}
	printf("\nProblem '%s' found.\n",problem_name);

	print_state("INIT",init_state);
	print_state("GOAL",goal_state);
}

int print_state (char * name, Fluent * state)
{
	printf("\n%s:\n",name);
	while(state)
	{
		printf("Function '%s'",state->name);
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
	// I don't need to malloc obj because var list already has memory
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
