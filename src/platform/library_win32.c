#include "../interpreter.h"

void Win32SetupFunc(Picoc *pc)
{    
}

void Ctest (struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    printf("test(%d)\n", Param[0]->Val->Integer);
    Param[0]->Val->Integer = 1234;
}

void Clineno (struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    ReturnValue->Val->Integer = Parser->Line;
}

/* list of all library functions and their prototypes */
struct LibraryFunction Win32Functions[] =
{
    { Ctest,        "void test(int);" },
    { Clineno,      "int lineno(void);" },
    { NULL,         NULL }
};

void PlatformLibraryInit(Picoc *pc)
{
    IncludeRegister(pc, "picoc_unix.h", &Win32SetupFunc, &Win32Functions[0], NULL);
}
