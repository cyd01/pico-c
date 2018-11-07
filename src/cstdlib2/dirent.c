/* dirent.h library for large systems - small embedded systems use clibrary.c instead */
#include "../interpreter.h"
#include <dirent.h>

typedef struct dir { DIR * ptr ; } DIRStruct ;
typedef struct dirent DirentStruct ;

/* handy structure definitions */
#ifdef WIN32
char DirentDefs[1024] = "\
typedef struct dir {\n\
	void * ptr ;\n\
} DIR ;\n\
";
/* struct dirent { long d_ino; unsigned short d_reclen; unsigned short d_namlen; char d_name[260]; };  */

#else
char DirentDefs[1024] = "\
typedef struct dir {\n\
	void * ptr ;\n\
} DIR ; \n\
";
#endif

/* dirent calls */
void DirentOpendir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    DIR * dir = opendir( Param[0]->Val->Pointer ) ;
    DIRStruct * ds ;
    ds = (DIRStruct *)malloc( sizeof( DIRStruct ) ) ;
    ds->ptr = (void*)dir ;
    ReturnValue->Val->Pointer = ds ;
}
void DirentClosedir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    DIRStruct * ds = (DIRStruct *)Param[0]->Val->Pointer ;
    DIR * dir = ds->ptr ;
    int ret = closedir( dir ) ;
    free( ds ) ;
    ReturnValue->Val->Integer = ret ;
}
void DirentReaddir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    DIRStruct * ds = (DIRStruct *)Param[0]->Val->Pointer ;
    DIR * dir = ds->ptr ;
    ReturnValue->Val->Pointer = readdir(dir);
}
void DirentRewinddir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    DIRStruct * ds = (DIRStruct *)Param[0]->Val->Pointer ;
    DIR * dir = ds->ptr ;
    rewinddir(dir);
}
void DirentTelldir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    DIRStruct * ds = (DIRStruct *)Param[0]->Val->Pointer ;
    DIR * dir = ds->ptr ;
    ReturnValue->Val->Integer = telldir(dir);
}
void DirentSeekdir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    DIRStruct * ds = (DIRStruct *)Param[0]->Val->Pointer ;
    DIR * dir = ds->ptr ;
    seekdir(dir, Param[1]->Val->Integer);
}
void DirentGetname(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
	struct dirent *dp = Param[0]->Val->Pointer ;
	ReturnValue->Val->Pointer = (char*)dp->d_name ;
}

/* all dirent functions */
struct LibraryFunction DirentFunctions[] =
{
    { DirentOpendir,    "DIR * opendir( char * name ) ;" },
    { DirentClosedir, 	"int closedir( DIR * dirp ) ;" },
    { DirentReaddir,  	"struct dirent * readdir( DIR * dirp ) ;" },
    { DirentRewinddir,	"void rewinddir( DIR * dirp ) ;" },
    { DirentTelldir,	"long telldir( DIR * dirp ) ;" },
    { DirentSeekdir,	"void seekdir( DIR * dirp, long offset ) ;" },
    { DirentGetname,	"char * dirent_getname( struct dirent * dp ) ;" },
    { NULL,         NULL }
};

/* creates various system-dependent definitions */
void InitDirentDefs(void) {
	char buffer[1024] ;
	struct dirent de ;
#ifdef WIN32
	sprintf( buffer, "struct dirent { long d_ino; char vide[%d]; char d_name[%d]; };", (int)(&(de.d_name))-(int)(&(de.d_ino))-sizeof(de.d_ino), sizeof(de.d_name) );
#else
	sprintf( buffer, "struct dirent { long d_ino; char vide[%lu]; char d_name[%lu]; };", (long unsigned int)(&(de.d_name))-(long unsigned int)(&(de.d_ino))-sizeof(de.d_ino), sizeof(de.d_name) );
#endif
	strcat( DirentDefs, buffer ) ;
}

void DirentSetupFunc(Picoc *pc)
{
    /*struct ValueType *StructDirType;*/
    /*struct ValueType *DirPtrType;*/

    /* make a "struct __DIRStruct" which is the same size as a native DIR structure */
    /* TypeCreateOpaqueStruct(NULL, TableStrRegister("__DIRStruct"), sizeof(DIR)); */

/*
#ifndef WIN32
	TypeCreateOpaqueStruct(NULL, TableStrRegister("dirent"), sizeof(struct dirent));
#endif
*/
    
    /* get a DIR * type */
    /*DirPtrType = TypeGetMatching(NULL, StructDirType, TypePointer, 0, StrEmpty, TRUE);*/

    /* make a "struct __DirentStruct" which is the same size as a native dirent structure */
    /*TypeCreateOpaqueStruct(NULL, TableStrRegister("__DirentStruct"), sizeof(struct dirent));*/

}
