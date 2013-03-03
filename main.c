#include "strips.h"
char * problem_name;
Fluent * init_state;
Fluent * goal_state;
Function * add_effects; 
Function * del_effects;
Function * preconditions;

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
	fclose(filepointer);


	print_state("INIT",init_state);
	print_state("GOAL",goal_state);
}

int print_state (char * name, Fluent * state)
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


