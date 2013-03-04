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
