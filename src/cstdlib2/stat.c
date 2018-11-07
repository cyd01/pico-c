/* stat.h library for large systems - small embedded systems use clibrary.c instead */
#include <sys/types.h>
#include <sys/stat.h>
#include "../interpreter.h"

/* Equivalent des #define NAME VALUE */
static int S_IFIFOValue = S_IFIFO ;
static int S_IFCHRValue = S_IFCHR ;
static int S_IFBLKValue = S_IFBLK ;
static int S_IFDIRValue = S_IFDIR ;
static int S_IFREGValue = S_IFREG ;
static int S_IFMTValue = S_IFMT ;
static int S_IEXECValue = S_IEXEC ;
static int S_IWRITEValue = S_IWRITE ;
static int S_IREADValue = S_IREAD ;
static int S_IRWXUValue = S_IRWXU ;
static int S_IXUSRValue = S_IXUSR ;
static int S_IWUSRValue = S_IWUSR ;
static int S_IRUSRValue = S_IRUSR ;


/* define definition */
const char StatDefine [] ="\
#define	S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)\n\
#define	S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)\n\
#define	S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)\n\
#define	S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)\n\
#define	S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)\n\
";

/* handy structure definitions */
typedef struct StatStructDef { 
	unsigned int st_dev ;
	unsigned int st_ino ;
	unsigned int st_mode ;
	short st_nlink ;
	short st_uid ;
	short st_gid ;
	unsigned int st_rdev ;
	long st_size ;
	int st_atime_h ;
	int st_mtime_h ;
	int st_ctime_h ;
} StatStruct ;

#ifdef WIN32
const char StatDefs[] = "\
struct stat \
{\n\
	dev_t	st_dev;\n\
	ino_t	st_ino;\n\
	mode_t	st_mode;\n\
	short	st_nlink;\n\
	short	st_uid;\n\
	short	st_gid;\n\
	dev_t	st_rdev;\n\
	off_t	st_size;\n\
	time_t	st_atime;\n\
	time_t	st_mtime;\n\
	time_t	st_ctime;\n\
} ;\n\
";
#else
const char StatDefs[] = "\
struct timespec { long tv_sec ; long tv_nsec ; } ;\n\
struct stat { unsigned int st_dev; unsigned int st_ino; int st_mode; short st_nlink; short st_uid; short st_gid; unsigned int st_rdev; long st_size; int st_atime; int st_mtime; int st_ctime; } ;\n\
";

#endif
/* stat calls */
void StatStat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
#ifdef WIN32
	ReturnValue->Val->Integer = stat( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
#else
	struct stat st ;
	StatStruct * s ;
	int ret ;
	ret = stat( Param[0]->Val->Pointer, &st ) ;
	s = (StatStruct *)Param[1]->Val->Pointer ;
	s->st_dev = (unsigned int)st.st_dev ;
	s->st_ino = (unsigned int)st.st_ino ;
	s->st_mode = st.st_mode ;
	s->st_nlink = st.st_nlink ;
	s->st_uid = st.st_uid ;
	s->st_gid = st.st_gid ;
	s->st_rdev = st.st_rdev ;
	s->st_size = st.st_size ;
	s->st_atime_h = st.st_atim.tv_sec ;
	s->st_mtime_h = st.st_mtim.tv_sec ;
	s->st_ctime_h = st.st_ctim.tv_sec ;
	ReturnValue->Val->Integer = ret ;
#endif
}
void StatFstat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = fstat( Param[0]->Val->Integer, Param[1]->Val->Pointer ) ;
}

/* all stat functions */
struct LibraryFunction StatFunctions[] =
{
    { StatStat,		"int stat( char *file_name, struct stat *buf ) ;" },
    { StatFstat,	"int fstat( int filedes, struct stat *buf ) ;" },
    { NULL,         NULL }
};

/* creates various system-dependent definitions */
void PicocParse(const char *FileName, const char *Source, int SourceLen, int RunIt, int CleanupNow, int CleanupSource, int EnableDebugger) ;
void StatSetupFunc(Picoc *pc)
{
    /* make a "struct tm" which is the same size as a native tm structure */
/*
#ifndef WIN32
    TypeCreateOpaqueStruct(NULL, TableStrRegister("stat"), sizeof(struct stat)); 
#endif
*/
    /* define definitions */
    VariableDefinePlatformVar(pc, NULL, "S_IFIFO", &pc->IntType, (union AnyValue *)&S_IFIFOValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IFCHR", &pc->IntType, (union AnyValue *)&S_IFCHRValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IFBLK", &pc->IntType, (union AnyValue *)&S_IFBLKValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IFDIR", &pc->IntType, (union AnyValue *)&S_IFDIRValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IFREG", &pc->IntType, (union AnyValue *)&S_IFREGValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IFMT", &pc->IntType, (union AnyValue *)&S_IFMTValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IEXEC", &pc->IntType, (union AnyValue *)&S_IEXECValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IWRITE", &pc->IntType, (union AnyValue *)&S_IWRITEValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IREAD", &pc->IntType, (union AnyValue *)&S_IREADValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IRWXU", &pc->IntType, (union AnyValue *)&S_IRWXUValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IXUSR", &pc->IntType, (union AnyValue *)&S_IXUSRValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IWUSR", &pc->IntType, (union AnyValue *)&S_IWUSRValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "S_IRUSR", &pc->IntType, (union AnyValue *)&S_IRUSRValue, FALSE);
    
    //PicocParse("stat.h", StatDefine, strlen(StatDefine), TRUE, TRUE, FALSE, FALSE);
}
