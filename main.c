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

	// Print init state
	printf("\nInit:\n");
	while(init_state)
	{
		printf("Function '%s'",init_state->var);
		if(init_state->obj)
		{
			printf(" with objects '%s'",init_state->obj->id);
		}
		init_state->obj = init_state->obj->next;
		while(init_state->obj->id)
		{
			printf(", '%s'",init_state->obj->id);
			init_state->obj = init_state->obj->next;
		}
		printf("\n");
		init_state = init_state->next;
	}

	printf("\nGoal:\n");
	while(goal_state)
	{
		printf("Function '%s'",goal_state->var);
		if(goal_state->obj)
		{
			printf(" with objects '%s'",goal_state->obj->id);
		}
		goal_state->obj = goal_state->obj->next;
		while(goal_state->obj->id)
		{
			printf(", '%s'",goal_state->obj->id);
			goal_state->obj = goal_state->obj->next;
		}
		printf("\n");
		goal_state = goal_state->next;
	}
	
}

Fluent * new_Fluent ()
{
	Fluent * node = (Fluent *) calloc (1, sizeof(Fluent) + 1);
	node->var = (char *) malloc (sizeof(char) + 1);
	//I don't need to malloc this because id list already has memory
	//node->obj = (ID_List *) malloc (sizeof(ID_List) + 1);
	node->next = NULL;

	return node;
}
