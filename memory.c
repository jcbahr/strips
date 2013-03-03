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

Action * new_Action ()
{
	Action * act = (Action *) calloc (1, sizeof(Action) + 1);
	act->name = (char *) malloc (sizeof(char) + 1);
	act->next = NULL;

	return act;
}
