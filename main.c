#include "strips.h"
char * problem_name;

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
	printf("The problem name is %s",problem_name);
}
