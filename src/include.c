/* picoc include system - can emulate system includes from built-in libraries
 * or it can include and parse files if the system has files */
 
#include "picoc.h"
#include "interpreter.h"

#ifndef NO_HASH_INCLUDE

#ifdef PERSOPORT
extern int enhanced_mode ;
void IncludeExternalTools(Picoc *pc) ;
#endif


/* initialise the built-in include libraries */
void IncludeInit(Picoc *pc)
{
#ifndef BUILTIN_MINI_STDLIB
    IncludeRegister(pc, "ctype.h", NULL, &StdCtypeFunctions[0], NULL);
    IncludeRegister(pc, "errno.h", &StdErrnoSetupFunc, NULL, NULL);
# ifndef NO_FP
    IncludeRegister(pc, "math.h", &MathSetupFunc, &MathFunctions[0], NULL);
# endif
    IncludeRegister(pc, "stdbool.h", &StdboolSetupFunc, NULL, StdboolDefs);
	
#ifdef PERSOPORT
	IncludeRegister(pc, "popen.h", &PopenSetupFunc, &PopenFunctions[0], PopenDefs) ;
	InitDirentDefs();
	IncludeRegister(pc, "dirent.h", &DirentSetupFunc, &DirentFunctions[0], DirentDefs) ;
	if( enhanced_mode ) { IncludeExternalTools(pc);	}
	IncludeRegister(pc, "stat.h", &StatSetupFunc, &StatFunctions[0], StatDefs);
	IncludeRegister(pc, "regex.h", &RegexSetupFunc, &RegexFunctions[0], RegexDefs);
	IncludeRegister(pc, "socket.h", &SocketSetupFunc, &SocketFunctions[0], SocketDefs);
	IncludeRegister(pc, "various.h", &VariousSetupFunc, &VariousFunctions[0], VariousDefs);
#endif
	
    IncludeRegister(pc, "stdio.h", &StdioSetupFunc, &StdioFunctions[0], StdioDefs);
    IncludeRegister(pc, "stdlib.h", &StdlibSetupFunc, &StdlibFunctions[0], NULL);
    IncludeRegister(pc, "string.h", &StringSetupFunc, &StringFunctions[0], NULL);
    IncludeRegister(pc, "time.h", &StdTimeSetupFunc, &StdTimeFunctions[0], StdTimeDefs);

#ifndef WIN32
    IncludeRegister(pc, "unistd.h", &UnistdSetupFunc, &UnistdFunctions[0], UnistdDefs);
# endif

#ifdef PERSOPORT
	IncludeRegister(pc, "unistd.h", &UnistdSetupFunc, &UnistdFunctions[0], UnistdDefs);
	IncludeRegister(pc, "types.h", &TypesSetupFunc, &TypesFunctions[0], TypesDefs);
#ifdef WIN32
    IncludeRegister(pc, "win.h", &WinSetupFunc, &WinFunctions[0], WinDefs);
#endif
#endif

#endif
}

/* clean up space used by the include system */
void IncludeCleanup(Picoc *pc)
{
    struct IncludeLibrary *ThisInclude = pc->IncludeLibList;
    struct IncludeLibrary *NextInclude;
    
    while (ThisInclude != NULL)
    {
        NextInclude = ThisInclude->NextLib;
        HeapFreeMem(pc, ThisInclude);
        ThisInclude = NextInclude;
    }

    pc->IncludeLibList = NULL;
}

/* register a new build-in include file */
void IncludeRegister(Picoc *pc, const char *IncludeName, void (*SetupFunction)(Picoc *pc), struct LibraryFunction *FuncList, const char *SetupCSource)
{
    struct IncludeLibrary *NewLib = HeapAllocMem(pc, sizeof(struct IncludeLibrary));
    NewLib->IncludeName = TableStrRegister(pc, IncludeName);
    NewLib->SetupFunction = SetupFunction;
    NewLib->FuncList = FuncList;
    NewLib->SetupCSource = SetupCSource;
    NewLib->NextLib = pc->IncludeLibList;
    pc->IncludeLibList = NewLib;
}

/* include all of the system headers */
void PicocIncludeAllSystemHeaders(Picoc *pc)
{
    struct IncludeLibrary *ThisInclude = pc->IncludeLibList;
    
    for (; ThisInclude != NULL; ThisInclude = ThisInclude->NextLib)
        IncludeFile(pc, ThisInclude->IncludeName);
}

/* include one of a number of predefined libraries, or perhaps an actual file */
void IncludeFile(Picoc *pc, char *FileName)
{
    struct IncludeLibrary *LInclude;
    
    /* scan for the include file name to see if it's in our list of predefined includes */
    for (LInclude = pc->IncludeLibList; LInclude != NULL; LInclude = LInclude->NextLib)
    {
        if (strcmp(LInclude->IncludeName, FileName) == 0)
        {
            /* found it - protect against multiple inclusion */
            if (!VariableDefined(pc, FileName))
            {
                VariableDefine(pc, NULL, FileName, NULL, &pc->VoidType, FALSE);
                
                /* run an extra startup function if there is one */
                if (LInclude->SetupFunction != NULL)
                    (*LInclude->SetupFunction)(pc);
                
                /* parse the setup C source code - may define types etc. */
                if (LInclude->SetupCSource != NULL)
                    PicocParse(pc, FileName, LInclude->SetupCSource, strlen(LInclude->SetupCSource), TRUE, TRUE, FALSE, FALSE);
                
                /* set up the library functions */
                if (LInclude->FuncList != NULL)
                    LibraryAdd(pc, &pc->GlobalTable, FileName, LInclude->FuncList);
            }
            
            return;
        }
    }
    
    /* not a predefined file, read a real file */
    PicocPlatformScanFile(pc, FileName);
}

#endif /* NO_HASH_INCLUDE */
