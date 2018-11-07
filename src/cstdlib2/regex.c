/* regex.h library for large systems - small embedded systems use clibrary.c instead */
#include <sys/types.h>
#include "regex.h"
#include "../interpreter.h"

/* Equivalent des #define NAME VALUE */
static int REG_EXTENDEDValue = REG_EXTENDED ;
static int REG_ICASEValue = REG_ICASE ;
static int REG_NOSUBValue = REG_NOSUB ;
static int REG_NEWLINEValue = REG_NEWLINE ;
static int REG_NOTBOLValue = REG_NOTBOL ;
static int REG_NOTEOLValue = REG_NOTEOL ;
static int REG_NOMATCHValue = REG_NOMATCH ;
static int REG_BADPATValue = REG_BADPAT ;
static int REG_ECOLLATEValue = REG_ECOLLATE ;
static int REG_ECTYPEValue = REG_ECTYPE ;
static int REG_EESCAPEValue = REG_EESCAPE ;
static int REG_ESUBREGValue = REG_ESUBREG ;
static int REG_EBRACKValue = REG_EBRACK ;
static int REG_EPARENValue = REG_EPAREN ;
static int REG_EBRACEValue = REG_EBRACE ;
static int REG_BADBRValue = REG_BADBR ;
static int REG_ERANGEValue = REG_ERANGE ;
static int REG_ESPACEValue = REG_ESPACE ;
static int REG_BADRPTValue = REG_BADRPT ;
/*static int REG_ENOSYSValue = REG_ENOSYS ;*/

typedef struct REGEX { regex_t * ptr ; } REGEXStruct ;
/*
The structure type regex_t contains at least the following member:
size_t    re_nsub    number of parenthesised subexpressions
*/

typedef struct REGMATCH { regmatch_t * ptr ; } REGMATCHStruct ;
/*
The structure type regmatch_t contains at least the following members:
regoff_t    rm_so    byte offset from start of string
                     to start of substring
regoff_t    rm_eo    byte offset from start of string
                     of the first character after the end of substring
*/


/* handy structure definitions */
const char RegexDefs[1024] = "\
typedef int regoff_t ;\n\
typedef struct __REGEXtruct regex_t ;\n\
typedef struct __REGMATCHtruct {\n\
	regoff_t rm_so ;\n\
	regoff_t rm_eo ;\n\
} regmatch_t ;\n\
";

/* regex calls */
void RegexRegcomp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = regcomp( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer ) ;
}
void RegexRegexec(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = regexec( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Pointer, Param[4]->Val->Integer ) ;
}
void RegexRegerror(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = regerror( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Integer ) ;
}
void RegexRegfree(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	regfree( Param[0]->Val->Pointer ) ;
}

/* all regex functions */
struct LibraryFunction RegexFunctions[] =
{
    { RegexRegcomp,	"int regcomp( regex_t *, char *, int ) ;" },
    { RegexRegexec,	"int regexec( regex_t *, char *, size_t, regmatch_t *, int ) ;" },
    { RegexRegerror,	"size_t regerror( int, regex_t *, char *, size_t ) ;" },
    { RegexRegfree,	"void regfree( regex_t * ) ;" },
    { NULL,         NULL }
};

/* creates various system-dependent definitions */
void PicocParse(const char *FileName, const char *Source, int SourceLen, int RunIt, int CleanupNow, int CleanupSource, int EnableDebugger) ;
void RegexSetupFunc(Picoc *pc)
{
    /* struct ValueType *StructRegexType ; */
    /* struct ValueType *StructRegmatchType ; */
	
    /* make a "struct __REGEXtruct" which is the same size as a native regex_t structure */
    /* StructRegexType = */TypeCreateOpaqueStruct(pc, NULL, TableStrRegister(pc, "__REGEXtruct"), sizeof(regex_t)); 
	
    /* make a "struct __REGMATCHtruct" which is the same size as a native regmatch_t structure */
    /*StructRegmatchType = TypeCreateOpaqueStruct(NULL, TableStrRegister("__REGMATCHtruct"), sizeof(regmatch_t));*/
	
    /* define definitions */
    VariableDefinePlatformVar(pc, NULL, "REG_EXTENDED", &pc->IntType, (union AnyValue *)&REG_EXTENDEDValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_ICASE", &pc->IntType, (union AnyValue *)&REG_ICASEValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_NOSUB", &pc->IntType, (union AnyValue *)&REG_NOSUBValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_NEWLINE", &pc->IntType, (union AnyValue *)&REG_NEWLINEValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_NOTBOL", &pc->IntType, (union AnyValue *)&REG_NOTBOLValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_NOTEOL", &pc->IntType, (union AnyValue *)&REG_NOTEOLValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_NOMATCH", &pc->IntType, (union AnyValue *)&REG_NOMATCHValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_BADPAT", &pc->IntType, (union AnyValue *)&REG_BADPATValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_ECOLLATE", &pc->IntType, (union AnyValue *)&REG_ECOLLATEValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_ECTYPE", &pc->IntType, (union AnyValue *)&REG_ECTYPEValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_EESCAPE", &pc->IntType, (union AnyValue *)&REG_EESCAPEValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_ESUBREG", &pc->IntType, (union AnyValue *)&REG_ESUBREGValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_EBRACK", &pc->IntType, (union AnyValue *)&REG_EBRACKValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_EPAREN", &pc->IntType, (union AnyValue *)&REG_EPARENValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_EBRACE", &pc->IntType, (union AnyValue *)&REG_EBRACEValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_BADBR", &pc->IntType, (union AnyValue *)&REG_BADBRValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_ERANGE", &pc->IntType, (union AnyValue *)&REG_ERANGEValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_ESPACE", &pc->IntType, (union AnyValue *)&REG_ESPACEValue, FALSE);
    VariableDefinePlatformVar(pc, NULL, "REG_BADRPT", &pc->IntType, (union AnyValue *)&REG_BADRPTValue, FALSE);
    /*VariableDefinePlatformVar(NULL, "REG_ENOSYS", &IntType, (union AnyValue *)&REG_ENOSYSValue, FALSE);*/
    

    /*PicocParse("regex.h", RegexDefine, strlen(RegexDefine), TRUE, TRUE, FALSE, FALSE);*/
}
