#ifdef WIN32
#include <windows.h>
#include <stdio.h> 

/* Exemple d'appel dans pico-c
struct { char * st ; } st_s;
char st[256];
strcpy( st, "Ceci est un test\n" );
st_s.st=st;
rundll("cstdlib2/testdll.dll","myputs_h",&st_s);
*/
typedef int (__cdecl *MYPROC)( void* ) ; 

int runDLL( char * dllname, char * functionname, void * param ) 
{ 
    HINSTANCE hinstLib; 
    MYPROC ProcAdd; 
    //BOOL fFreeResult, fRunTimeLinkSuccess = FALSE; 
 
    /* Get a handle to the DLL module. */
 
    hinstLib = LoadLibrary(TEXT(dllname)); 
 
    /* If the handle is valid, try to get the function address. */
 
    if (hinstLib != NULL) 
    { 
        ProcAdd = (MYPROC) GetProcAddress(hinstLib,functionname); 
 
        /* If the function address is valid, call the function. */
 
        if (NULL != ProcAdd) 
        {
            //fRunTimeLinkSuccess = TRUE;
            (ProcAdd) ( param ); 
        } else {
		fprintf( stderr, "Unable to run function %s\n", functionname );
	}
	
        /* Free the DLL module. */
	//fFreeResult = 
	FreeLibrary(hinstLib); 
    } else {
	fprintf(stderr,"Unable to load DLL %s\n", dllname);
    }

    /* If unable to call the DLL function, use an alternative. */
    /* if (! fRunTimeLinkSuccess) printf("Message printed from executable\n"); */

    return 0;

}


#endif
