/* mini.h library for large systems - small embedded systems use clibrary.c instead */
#include "mini.c"
#include "../interpreter.h"

/* handy structure definitions */
const char MiniDefs[] = "\
";

void MiniDelINI(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = delINI( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer ) ;
}

void MiniReadINI(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = readINI( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Pointer ) ;
}

void MiniWriteINI(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = writeINI( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Pointer ) ;
}

/* all mini.h functions */
struct LibraryFunction MiniFunctions[] =
{
	{ MiniDelINI,         "int delINI( char * filename, char * section, char * key ) ;" },
	{ MiniReadINI,        "int readINI( char * filename, char * section, char * key, char * pStr) ;" },
	{ MiniWriteINI,       "int writeINI( char * filename, char * section, char * key, char * value ) ;" },
	{ NULL,         NULL }
} ; 


/* creates various system-dependent definitions */
void MiniSetupFunc(Picoc *pc)
{
}
