#include "../platform.h"
#include "build.h"

#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

//int stricmp( const char * s1, const char * s2 ) ;
int picoc_main(int argc, char **argv) ;

int main1( int argc, char ** argv ) { return picoc_main( argc, argv ) ; }

void picoc_usage( char * progname ) {
	printf( "%s, A very small C interpreter\nUsage: %s [-h] [-i] [-m] [-n] [-o] [<filename1>...] [- <arg1>...]\n", progname, progname) ;
	printf( "	-h: this help message\n" ) ;
	printf( "	-i: force interactive mode at the end of scripts\n" ) ;
	printf( "	-m: run main() function automaticaly\n" ) ;
	printf( "	-n: don't print prompt\n" ) ;
	printf( "	-o: the original \"old\" mode\n" ) ;
	printf( "	-v: print version\n" ) ;
	printf( "Exemples:\n" ) ;
	printf( "	%s script1.pcc script2.pcc\n", progname ) ;
	printf( "	%s -i script.pcc\n", progname ) ;
	printf( "	%s -m script1.pcc script2.pcc - arg1 agr2\n", progname ) ;
	printf( "Build time:\n" ) ;
	printf( "	%s\n", BUILD_TIME ) ;
}

#include "../picoc.h"
#include "../platform.h"
#ifndef PICOC_STACK_SIZE
#define PICOC_STACK_SIZE (128*1024)   
#endif

int enhanced_mode = 1 ;

int ParseInteractiveMode = 0 ;

extern int PicocExitValue;

void PicocParseInteractiveNoStartPrompt(Picoc *pc, int EnableDebugger);

int main( int argc, char ** argv ) {
	int return_code = 0 ;
	int noprompt = 0 ;
	int interactivemode = 0 ;
	int oldmode = 0 ;
	int runmain = 0 ;
	int i=1, j ;
	int ParamCount = 1 ;

	char *binname	= argv[0]+strlen(argv[0]) ;
	while( binname!=argv[0] ) {
		if( (binname[0]=='/')||(binname[0]=='\\') ) { binname++ ; break ; }
		binname-- ;
	}
	if( stricmp(binname,"pcc.exe") && strcmp(binname,"pcc") ) { 
		enhanced_mode = 0 ; 
	} else {
		strcpy(INTERACTIVE_PROMPT_STATEMENT,"pcc> ");
		strcpy(INTERACTIVE_PROMPT_LINE     ,"   > ");
	}

	if( argc == 1 ) { interactivemode = 1 ; }
	if( argc>1 )
		for( i=1 ; i<argc ; i++ ) {
			if( !strcmp( argv[i], "-i" ) ) { interactivemode = 1 ; }
			if( !strcmp( argv[i], "-m" ) ) { runmain = 1 ; }
			if( !strcmp( argv[i], "-n" ) ) { noprompt = 1 ; }
			if( !strcmp( argv[i], "-o" ) ) { oldmode = 1 ; break ; }
			if( !strcmp( argv[i], "-h" ) ) { picoc_usage( binname ) ; return 0 ; }
			if( !strcmp( argv[i], "-v" ) ) { printf( "Version: %s\n",PICOC_VERSION ) ; return 0 ; }
			if( !strcmp( argv[i], "-" ) ) { i++ ; break ; }
			if( argv[i][0]!='-' ) { break ; }
		}
	ParamCount = i ;
	if( noprompt ) {
		strcpy( INTERACTIVE_PROMPT_STATEMENT, "" ) ;
		strcpy( INTERACTIVE_PROMPT_LINE, "" ) ;
	}
	if( oldmode ) {
		int arc = argc-1 ;
		char ** arv = NULL ;
		arv = (char**)malloc( (arc)*sizeof(char*) ) ;
		for( j=0 ; j<i ; j++ ) {
			arv[j] = (char*) malloc( strlen(argv[j])+1 ) ; 
			strcpy( arv[j], argv[j] ) ;
		}
		for( j=i ; j<arc ; j++ ) {
			arv[j] = (char*) malloc( strlen(argv[j+1])+1 ) ; 
			strcpy( arv[j], argv[j+1] ) ;
		}
		
		return_code = picoc_main( arc, arv ) ;
		for( i=arc-1 ; i>=0 ; i-- ) { free( arv[i] ); }
		free(arv);
	} else {
		int StackSize = getenv("STACKSIZE") ? atoi(getenv("STACKSIZE")) : PICOC_STACK_SIZE;
		Picoc pc;
		
    		PicocInitialise(&pc,StackSize);
		PicocIncludeAllSystemHeaders(&pc);	
		
		if( i==argc ) { interactivemode = 1 ; }
		if( i<argc ) 
			for( j=i ; j<argc ; j++ ) {
				if( !strcmp(argv[j], "-") ) { break ; }
				ParamCount++;
				PicocPlatformScanFile(&pc, argv[j]);
				/*PicocCallMain(argc - j, &argv[j]);*/
			}

		if( runmain ) {
			PicocCallMain(&pc, argc - ParamCount, &argv[ParamCount]);
		}

		if( interactivemode ) { /* Interactive */
			ParseInteractiveMode = 1 ;
			if( noprompt ) { PicocParseInteractiveNoStartPrompt(&pc,TRUE); }
			else { PicocParseInteractive(&pc) ; }
		}
		
		PicocCleanup(&pc);
		return_code = pc.PicocExitValue;
	}
	return return_code ;
}

int main2( int argc, char ** argv ) {
	int return_code = 0, i ;
	int arc = argc + 1 ;
	char ** arv = NULL;
	
	arv = (char**)malloc( (argc+1)*sizeof(char*) ) ;
	arv[0] = (char*) malloc( strlen(argv[0])+1 ) ;
	strcpy( arv[0], argv[0] );

	if( argc==1 ) {
		arv[1] = (char*)malloc( 3 ) ;
		strcpy( arv[1], "-i" ) ;
	} else {
		if( !strcmp( argv[1], "-h" ) ) {
			picoc_usage( "pico-c" ) ;
			return 0 ;
		}else if( !strcmp( argv[1], "-o" ) ) {
			arc=arc-2 ;
			if( argc>2 ) {
				for( i=1 ; i<(argc-1) ; i++ ) {
					arv[i] = (char*) malloc( strlen(argv[i+1])+1 ) ;
					strcpy( arv[i], argv[i+1] );
				}
			}
		} else {
			arv[1] = (char*)malloc( 3 ) ;
			strcpy( arv[1], "-s" ) ;
			if( argc>1 ) {
				for( i=1 ; i<argc ; i++ ) {
					arv[i+1] = (char*) malloc( strlen(argv[i])+1 ) ;
					strcpy( arv[i+1], argv[i] );
				}
			}
		}
	}

/* printf("arc=%d\n",arc);for( i=0; i<arc ; i++) { printf("arv[%d]=%s\n",i,arv[i]); } */

	return_code = picoc_main( arc, arv ) ;
	for( i=arc-1 ; i>=0 ; i-- ) { free( arv[i] ); }
		
	free(arv);
	return return_code ;
}
