/* complement a stdio.h pour ajouter popen et pclose */
#include <stdio.h>
#include "../interpreter.h"

/* define definition */
const char PopenDefs[] = "" ;

/* popen calls */
void PopenPopen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = popen( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}

void PopenPclose(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = pclose( Param[0]->Val->Pointer ) ;
}

/* all stdio.h functions */
struct LibraryFunction PopenFunctions[] =
{
    { PopenPopen,	"FILE * popen( char * commande, char * type ) ;" },
    { PopenPclose,	"int pclose( FILE * stream) ;" },
    { NULL,         NULL }
};

/* creates various system-dependent definitions */
void PopenSetupFunc(Picoc *pc)
{
	/* printf("PATH_MAX=%d\n",PATH_MAX); */
}
