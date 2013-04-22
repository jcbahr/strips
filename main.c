


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
char * problem_name;
Fluent * init_state;
Fluent * goal_state;
Function * add_effects;
Function * del_effects;
Function * preconditions;
Action * actions;

Fluent * state;
Plan * plan;
Stack * stack;

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
        printf ("Error: '%s' not found!\n", argv[1]);
        exit (EXIT_FAILURE);
    }
    yyin = filepointer;
    while (!feof(yyin))
    {
        yyparse();
    }
    fclose(filepointer);


	print_fluent(init_state);
	print_fluent(goal_state);
//	print_actions(actions);
 
	/*
	state = init_state;
    plan = new_Plan();
    stack = new_Stack();
	*stack->type = 2;
    Plan * plan_out = strips_loop(state, plan, stack);
	*/
//	print plan

/*	if ( equal_ID_Lists( init_state->obj, goal_state->obj ))
	{
		printf("Yea!\n");
	}
	else
		printf("Nay!\n");
*/
	printf("\n\n%d",Fluent_in_List(init_state, goal_state));

	testing(init_state);

}

void testing (Fluent * a)
{
	print_fluent(a);
}

Plan * strips_loop (Fluent * state, Plan * plan, Stack * stack)
{
    Stack_Element * top = new_Stack_Element();

	// testing

	top->operator = malloc ( 5 * sizeof(char) + 1);
	strcpy(top->operator, "push!");
	*stack->type = 1;

	for ( ; stack->next; stack = stack->next )
    {
        top = stack->element;
		Plan * new_op = new_Plan();
		switch(*stack->type)
		{
			case 1:			// operator
				//state += add list
				//state -= del list
				
				new_op->action_name = malloc (strlen (top->operator) + 1);
				strcpy(new_op->action_name, top->operator);
				// what else gets added to new_op?
				// copy objects (don't just send pointer)
				plan = append_to_Plan( plan, new_op );
				break;
			case 2:			// conjunctive goal
				//select ordering for subgoals
				//push back on to stack
				break;
			case 3:			// simple goal
				//in current state
				//or unsatisfied
				break;
		}
    }
    return plan;
}

Stack * pop (Stack * stack)
{
    stack = stack->next;
    stack->prev = NULL;
    return stack;
}

Stack * push (Stack_Element * element, char * type, Stack * stack)
{
    Stack * top = new_Stack();
    *type = *top->type;
    top->next = stack;
    top->prev = NULL;
}

Plan * append_to_Plan ( Plan * plan, Plan * addition )
{
	Plan * out = plan;
	while (plan->next)
	{
		plan = plan->next;
	}
	plan->next = addition;

	return out;
}

bool equal_ID_Lists( ID_List * a, ID_List * b )
{
	if (strcmp(a->id, b->id))
	{
		return false;
	}
	
	while(a->next && b->next)
	{
		if (strcmp(a->id, b->id))
		{
			return false;
		}
		a = a->next;
		b = b->next;
	}

	return true;
}

bool equal_Fluents( Fluent * a, Fluent * b )
{
	if (strcmp(a->name, b->name))
	{
		return false;
	}
	else if (! equal_ID_Lists(a->obj, b->obj))
	{
		return false;
	}
	
	return true;
}

int Fluent_in_List( Fluent * a, Fluent * list )
{
print_fluent(a);
/*
	*
	 *	returns false if fluent is not in the list of fluents
	 *	or
	 *	returns the position of the equal fluent + 1
	 *	so the first is "1"
	 *
	int i=0;

	while ( list )
	{
		printf("\n\n\ni=%d\n",i);
		i++;
		print_fluent(a);
		print_fluent(list);
		if (equal_Fluents(a, list))
		{
			printf("returning i (= %d)\n",i+1);
			return i;
		}
		if (list->next)
			list = list->next;
		else
			return 0;
	}

///*
	for ( i = 0; list->next; i++, list = list->next )
	{
		printf("i=%d\n",i);
		print_fluent("a",a);
		print_fluent("list",list);
		if (equal_Fluents(a, list))
		{
			printf("i+1=%d\n",i+1);
			return i+1;
		}
	}
	return 0;
*/
}


// function for adding fluents to state


// function for removing fluents from state
Fluent * remove_Fluent(Fluent * state, Fluent * delete)
{ }

