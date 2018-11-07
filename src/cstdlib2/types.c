/* types.h library for large systems - small embedded systems use clibrary.c instead */
#include <sys/types.h>
#include <limits.h>
#include "../interpreter.h"

/* define definition */
static int S_PATH_MAX = PATH_MAX ;

/* handy structure definitions */
#ifdef WIN32
const char TypesDefs[] = "\
typedef unsigned int dev_t ;\n\
typedef short ino_t ;\n\
typedef unsigned short mode_t ;\n\
" ;
#else
const char TypesDefs[] = "\
typedef unsigned int dev_t ;\n\
typedef unsigned int ino_t ;\n\
typedef unsigned int mode_t ;\n\
typedef unsigned int nlink_t ;\n\
typedef	int blksize_t ;\n\
typedef long blkcnt_t ;\n\
" ;
#endif

/* all types functions */
struct LibraryFunction TypesFunctions[] =
{
    { NULL,         NULL }
} ;

/* creates various system-dependent definitions */
void TypesSetupFunc(Picoc *pc)
{
	VariableDefinePlatformVar(pc, NULL, "PATH_MAX", &pc->IntType, (union AnyValue *)&S_PATH_MAX, FALSE);
}
