#include "../interpreter.h"
#include <strings.h>
#include "tools.h"

/* Equivalent des #define NAME VALUE */
static int RAND_MAXValue = RAND_MAX ;

#ifndef WIN32
#ifdef AIX_HOST
#include <sys/wait.h>
#else
#include <wait.h>
#endif
#else
pid_t wait( int *status ) ;
pid_t waitpid(pid_t pid, int *status, int options) ;
#endif

extern int ParseInteractiveMode ;

int existfile( const char * filename ) ;

void VariousBcopy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	memcpy( Param[1]->Val->Pointer, Param[0]->Val->Pointer, Param[2]->Val->Integer ) ;
}
    
void VariousBzero(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    memset( Param[0]->Val->Pointer, 0, Param[1]->Val->Integer ) ;
}

void VariousWait(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = wait( Param[0]->Val->Pointer );
}

void VariousWaitpid(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = waitpid( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer );
}

void PicocPlatformScanFile(const char *FileName) ;
void VariousInclude(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	int return_code = 0 ;
	if( ParseInteractiveMode ) {
		fprintf( stderr, "This function is not available in interactive mode !\n" ) ; 
		ReturnValue->Val->Integer = -1 ;
		return ;
	}
	if( !existfile( Param[0]->Val->Pointer ) ) {
		return_code = -1 ;
		fprintf( stderr, "Unable to open file %s !\n", (char*)Param[0]->Val->Pointer ) ;
	} else {
		PicocPlatformScanFile( Param[0]->Val->Pointer ) ;
		return_code = 0 ;
	}
	ReturnValue->Val->Integer = return_code ;
}

void PicocParse(const char *FileName, const char *Source, int SourceLen, int RunIt, int CleanupNow, int CleanupSource, int EnableDebugger) ;
void VariousIncludeStr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	int return_code = 0 ;
	char * str = Param[0]->Val->Pointer ;
	if( ParseInteractiveMode ) {
		fprintf( stderr, "This function is not available in interactive mode !\n" ) ; 
		ReturnValue->Val->Integer = -1 ;
		return ;
	}
	if( (str!=NULL) && (strlen(str)>0) ) {
		PicocParse("nofile", str, strlen(str), TRUE, FALSE, TRUE, TRUE ) ;
	} else {
		return_code = -1 ;
	}
	ReturnValue->Val->Integer = return_code ;
}
	
void VariousEXIT(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	exit( Param[0]->Val->Integer ) ;
}

/* list all the strings (complete le fichier table.c) */
int TableList( Picoc *pc, char * st )
{
    int nb=0 ;
    struct TableEntry *Entry;
    struct TableEntry *NextEntry;
    int Count;
    
    for (Count = 0; Count < (pc->StringTable).Size; Count++)
    {
        for (Entry = (pc->StringTable).HashTable[Count]; Entry != NULL; Entry = NextEntry)
        {
            NextEntry = Entry->Next;
	    if( (st == NULL) || (strlen(st)==0) )  {
		printf("%s\n",&Entry->p.Key[0]) ; 
		nb++ ;
	    } else if ( matchpattern(st,&Entry->p.Key[0]) ) {
		if( (strstr(&Entry->p.Key[0],"*")==NULL) && (strstr(&Entry->p.Key[0],"?")==NULL) ) {
			printf("%s\n",&Entry->p.Key[0]) ;
			nb++ ;
		}
	    }
	    
        }
    }
    return nb;
}

void VariousLIST(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	int nb = TableList( Parser->pc, Param[0]->Val->Pointer ) ;
	printf( "Total: %d\n",nb ) ;
	ReturnValue->Val->Integer = nb ;
}

#ifdef WIN32
#include "rundll.c"
int runDLL( char * dllname, char * functionname, void * param )  ;
void VariousRunDLL(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{	
	ReturnValue->Val->Integer = runDLL( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer ) ;
}
#endif

/* handy structure definitions */
const char VariousDefs[] = "\
";


/* all various.h functions */
struct LibraryFunction VariousFunctions[] =
{
	{ VariousBcopy,		"void bcopy( void *src, void *dest, size_t n ) ;" },
	{ VariousBzero,		"void bzero( void *s, size_t n ) ;" },
	{ VariousWait,		"pid_t wait( int *status ) ;" },
	{ VariousWaitpid,	"pid_t waitpid( pid_t pid, int *status, int options ) ;" },
	{ VariousInclude,	"int INCLUDE( char * filename ) ;" },
	{ VariousIncludeStr,	"int INCLUDESTR( char * str ) ;" },
	{ VariousEXIT,		"void EXIT( int retval ) ;" },
	{ VariousLIST,		"int LIST( char * st ) ;" },
#ifdef WIN32
	{ VariousRunDLL,	"int rundll( char * dllname, char * functionname, void * param ) ;" },
#endif
	{ NULL,			NULL }
};

/* creates various system-dependent definitions */
void VariousSetupFunc(Picoc *pc)
{
	/* define definitions */
	VariableDefinePlatformVar(pc, NULL, "RAND_MAX", &pc->IntType, (union AnyValue *)&RAND_MAXValue, FALSE);
}
