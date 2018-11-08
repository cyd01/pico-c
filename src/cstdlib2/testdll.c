/* gcc -o testdll.dll -shared testdll.c */

#include <windows.h>
#include <stdio.h>

#define LINKDLL __declspec(dllexport)

int myputs( char * st ) ;

typedef struct myputs_s {
	char * st ;
	} MYPUTS_S ;

LINKDLL int myputs_h( void * st ) {
	MYPUTS_S * st_s ;
	st_s = (MYPUTS_S *) st ;
	return myputs( st_s->st ) ;
}

int myputs( char * st ) {
	printf("%s",st);
}
