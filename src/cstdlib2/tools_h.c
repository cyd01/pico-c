/* tools.h library for large systems - small embedded systems use clibrary.c instead */
#include "tools.c"
#include "../interpreter.h"

/* la commande bc est incluse dans le tools.h */
#include "bc_eval.c"

/* Les commandes encode64 et decode64 sont incluses dans le tools.h */
#include "base64.c"

/* Les commandes MD5Cal et MD5CalFile sont incluses dans le tools.h */
#include "md5.c"

/* Les commandes bcrypt sont incluses dans le bcrypt.h */
#include "bcrypt.c"

#include <libgen.h>

/* handy structure definitions */
const char ToolsDefs[] = "\
#define E EXIT(0)\n\
#define L LIST(NULL)\n\
";

/* tools calls */
void ToolsPrintversion_tools(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	printversion_tools() ;
}
void ToolsMaj(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = maj( Param[0]->Val->Integer ) ;
}
void ToolsMajuscule(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = majuscule( Param[0]->Val->Pointer ) ;
}
void ToolsStrnew(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = strnew( Param[0]->Val->FP ) ;
}
void ToolsStr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = str( Param[0]->Val->Pointer, Param[1]->Val->FP ) ;
}
void ToolsStrbstr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = strbstr( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsStrcatc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = strcatc( Param[0]->Val->Pointer, Param[1]->Val->Integer ) ;
}
void ToolsStrbcat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = strbcat( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsStrrepeat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = strrepeat( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer ) ;
}
void ToolsVal(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->FP = val( Param[0]->Val->Pointer ) ;
}
void ToolsCopynew(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = copynew( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer ) ;
}
void ToolsCopy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = copy( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Integer ) ;
}
void ToolsPos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = pos( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsPosc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = posc( Param[0]->Val->Integer, Param[1]->Val->Pointer ) ;
}
void ToolsPosi(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = posi( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer ) ;
}
void ToolsPosic(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = posic( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer ) ;
}
void ToolsPosn(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = posn( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsPosnc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = posnc( Param[0]->Val->Integer, Param[1]->Val->Pointer ) ;
}
void ToolsMpos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = mpos( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsStrinf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = strinf( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsDelnew(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = delnew( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer ) ;
}
void ToolsDel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = del( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer ) ;
}
void ToolsInsertnew(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = insertnew( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer ) ;
}
void ToolsInsert(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = insert( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer ) ;
}
void ToolsReplacec(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = replacec( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer ) ;
}
void ToolsRemplacec(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = remplacec( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer ) ;
}
void ToolsReplace(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = replace( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer ) ;
}
void ToolsRemplace(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = remplace( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer ) ;
}
void ToolsItos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = itos( Param[0]->Val->Integer ) ;
}
void ToolsMatchpattern(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = matchpattern( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsStrscan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
    printf("Not implemented yet!\n");
}
void ToolsRpad(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = rpad( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer ) ;
}
void ToolsDrpad(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = drpad( Param[0]->Val->Pointer, Param[1]->Val->Integer ) ;
}
void ToolsLpad(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = lpad( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer ) ;
}
void ToolsDlpad(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = dlpad( Param[0]->Val->Pointer, Param[1]->Val->Integer ) ;
}
void ToolsRtrim(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = rtrim( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsDrtrim(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = drtrim( Param[0]->Val->Pointer ) ;
}
void ToolsLtrim(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = ltrim( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsDltrim(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = dltrim( Param[0]->Val->Pointer ) ;
}
void ToolsTrim(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = trim( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsDtrim(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = dtrim( Param[0]->Val->Pointer ) ;
}
void ToolsScanparam(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = scanparam( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Pointer  ) ;
}
void ToolsScanparam1(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = scanparam1( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer ) ;
}
void ToolsParam_init(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = param_init( Param[0]->Val->Integer, Param[1]->Val->Pointer ) ;
}
void ToolsParam_nbr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = param_nbr() ;
}
void ToolsParam_tab(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = param_tab() ;
}	
void ToolsParam_scan1(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = param_scan1( Param[0]->Val->Pointer ) ;
}
void ToolsParam_scan(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = param_scan( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void ToolsParam_get(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = param_get( Param[0]->Val->Integer ) ;
}
void ToolsParam_print(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	param_print();
}
void ToolsParam_clean(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	param_clean();
}	
void ToolsAdddate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = adddate( Param[0]->Val->Integer, Param[1]->Val->Pointer ) ;
}
void ToolsSqr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->FP = sqr( Param[0]->Val->FP ) ;
}
void ToolsMyabs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->FP = myabs( Param[0]->Val->FP ) ;
}
void ToolsMymin(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->FP = mymin( Param[0]->Val->FP, Param[1]->Val->FP ) ;
}
void ToolsMymini(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = mymini( Param[0]->Val->Integer, Param[1]->Val->Integer ) ;
}
void ToolsMymax(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->FP = mymax( Param[0]->Val->FP, Param[1]->Val->FP ) ;
}
void ToolsMymaxi(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = mymaxi( Param[0]->Val->Integer, Param[1]->Val->Integer ) ;
}
void ToolsSgn(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = sgn( Param[0]->Val->FP ) ;
}	
void ToolsMyrandseed(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	myrandseed( Param[0]->Val->Integer ) ;
}	
void ToolsMyrandomd(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->FP = myrandomd() ;
}	
void ToolsMyrandom(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = myrandom( Param[0]->Val->Integer ) ;
}
void ToolsMyrandomize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	myrandomize() ;
}
void ToolsSterrno(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = sterrno( Param[0]->Val->Integer ) ;
}
void ToolsSsterrno(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = ssterrno( Param[0]->Val->Pointer ) ;
}
void ToolsExistfile(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = existfile( Param[0]->Val->Pointer ) ;
}
void ToolsExistdir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = existdir( Param[0]->Val->Pointer ) ;
}
void ToolsExistlink(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = existlink( Param[0]->Val->Pointer ) ;
}
void ToolsExist(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = exist( Param[0]->Val->Pointer ) ;
}
void ToolsFilesize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = filesize( Param[0]->Val->Pointer ) ;
}	
void ToolsRmalldir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = rmalldir( Param[0]->Val->Pointer ) ;
}
void ToolsFiletime(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = filetime( Param[0]->Val->Pointer ) ;
}
void ToolsDirname(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = dirname( Param[0]->Val->Pointer ) ;
}
void ToolsBasename(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = basename( Param[0]->Val->Pointer ) ;
}
void ToolsURLencode(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	URLencode( Param[0]->Val->Pointer ) ;
}
void ToolsURLencodeFilename(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	URLencodeFilename( Param[0]->Val->Pointer ) ;
}	
void ToolsURLdecode(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	URLdecode( Param[0]->Val->Pointer ) ;
}

void ToolsURLread(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = URLread( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Pointer, Param[4]->Val->Pointer, Param[5]->Val->Pointer, Param[6]->Val->Pointer, Param[7]->Val->Pointer, Param[8]->Val->Pointer ) ;
}

void ToolsBcEval(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->FP = bc_eval( Param[0]->Val->Pointer ) ;
}

void ToolsEncode64(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	encode64( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer ) ;
}

void ToolsDecode64(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = decode64( Param[0]->Val->Pointer ) ;
}

void ToolsMD5Cal(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	MD5Cal( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}

void ToolsMD5CalFile(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	MD5CalFile( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}

void ToolsBcryptTestPattern(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_test_pattern( Param[0]->Val->Pointer, Param[1]->Val->Integer ) ;
}

void ToolsBcryptInit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	bcrypt_init( Param[0]->Val->Integer ) ;
}

void ToolsBcryptString(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_string( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Pointer, Param[4]->Val->Pointer, Param[1]->Val->Integer) ;
}

void ToolsBuncryptString(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_string( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Pointer, Param[4]->Val->Pointer) ;
}

void ToolsBcryptStringPrintable(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_string_printable( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Pointer, Param[4]->Val->Integer) ;
}

void ToolsBuncryptStringPrintable(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_string_printable( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Pointer) ;
}

void ToolsBcryptStringBase64(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_string_base64( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Pointer, Param[4]->Val->Integer) ;
}

void ToolsBuncryptStringBase64(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_string_base64( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Pointer) ;
}

void ToolsBcryptStringBase64url(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_string_base64url( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Pointer, Param[4]->Val->Integer) ;
}

void ToolsBuncryptStringBase64url(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_string_base64url( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Pointer) ;
}

void ToolsBcryptStringAuto(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_string_auto( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Pointer, Param[3]->Val->Pointer, Param[4]->Val->Integer) ;
}

void ToolsBuncryptStringAuto(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_string_auto( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Pointer, Param[3]->Val->Pointer) ;
}

void ToolsBcryptFile(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_file( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Pointer, Param[4]->Val->Integer) ;
}

void ToolsBuncryptFile(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_file( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Pointer) ;
}

void ToolsBcryptFilePrintable(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_file_printable( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Integer) ;
}

void ToolsBuncryptFilePrintable(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_file_printable( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer) ;
}

void ToolsBcryptFileBase64(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_file_base64( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Integer) ;
}

void ToolsBuncryptFileBase64(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_file_base64( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer) ;
}

void ToolsBcryptFileBase64url(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_file_base64url( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Integer) ;
}

void ToolsBuncryptFileBase64url(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_file_base64url( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer) ;
}

void ToolsBcryptFileAuto(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = bcrypt_file_auto( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer, Param[3]->Val->Integer) ;
}

void ToolsBuncryptFileAuto(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = buncrypt_file_auto( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Pointer) ;
}

void ToolsPrintHelp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs);

void ToolsPrintHelp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	char * pst = Param[0]->Val->Pointer ;
	if( pst != NULL ) { if( strlen( pst ) > 0 ) {
		if( !strcmp( pst, "tools.h" ) ) 	{ PrintHelp( pst, ToolsFunctions, ToolsDefs ) ; }
		else if( !strcmp( pst, "dirent.h" ) ) 	{ PrintHelp( pst, DirentFunctions, DirentDefs ) ; }
		else if( !strcmp( pst, "math.h" ) ) 	{ PrintHelp( pst, MathFunctions, NULL ) ; }
		else if( !strcmp( pst, "mini.h" ) ) 	{ PrintHelp( pst, MiniFunctions, MiniDefs ) ; }
		else if( !strcmp( pst, "popen.h" ) ) 	{ PrintHelp( pst, PopenFunctions, PopenDefs ) ; }
		else if( !strcmp( pst, "stdbool.h" ) ) 	{ PrintHelp( pst, NULL, StdboolDefs ) ; }
		else if( !strcmp( pst, "stdio.h" ) ) 	{ PrintHelp( pst, StdioFunctions, StdioDefs ) ; }
		else if( !strcmp( pst, "stdlib.h" ) ) 	{ PrintHelp( pst, StdlibFunctions, NULL ) ; }
		else if( !strcmp( pst, "string.h" ) ) 	{ PrintHelp( pst, StringFunctions, NULL ) ; }
		else if( !strcmp( pst, "time.h" ) ) 	{ PrintHelp( pst, StdTimeFunctions, StdTimeDefs ) ; }
		else if( !strcmp( pst, "types.h" ) ) 	{ PrintHelp( pst, TypesFunctions, TypesDefs ) ; }
		else if( !strcmp( pst, "unistd.h" ) ) 	{ PrintHelp( pst, UnistdFunctions, UnistdDefs ) ; }
		else if( !strcmp( pst, "stat.h" ) ) 	{ PrintHelp( pst, StatFunctions, StatDefs ) ; }
		else if( !strcmp( pst, "various.h" ) ) 	{ PrintHelp( pst, VariousFunctions, VariousDefs ) ; }
		else if( !strcmp( pst, "regex.h" ) ) 	{ PrintHelp( pst, RegexFunctions, RegexDefs ) ; }
		else if( !strcmp( pst, "socket.h" ) ) 	{ PrintHelp( pst, SocketFunctions, SocketDefs ) ; }
#ifdef WIN
		else if( !strcmp( pst, "win.h" ) ) 	{ PrintHelp( pst, WinFunctions, WinDefs ) ; }
#endif
		else { printf( "Unknown prototype filename !\n" ) ; }
	} else {
		printf( "Avalaible libraries:\n" ) ;
		printf( "dirent.h, regex.h, math.h, popen.h, socket.h, stat.h, stdbool.h, stdio.h, stdlib.h, string.h, time.h, types.h, unistd.h, various.h, win.h" ) ;
		printf( "\n" ) ;
	}
	}
}

/* all tools.h functions */
struct LibraryFunction ToolsFunctions[] =
{
	{ ToolsPrintversion_tools,	"void printversion_tools( void ) ;" },
	{ ToolsMaj,			"int maj( int ) ;" },
	{ ToolsMajuscule,		"int majuscule( signed char * ) ;" },
	{ ToolsStrnew,			"char * strnew( double ) ;" },
	{ ToolsStr, 			"int str( char *, double ) ;" },
	{ ToolsStrbstr, 		"char * strbstr( char *, char * ) ;" } ,
	{ ToolsStrcatc,			"char * strcatc( char *, char ) ;" } ,
	{ ToolsStrbcat, 		"char * strbcat( char *, char * ) ;" },
	{ ToolsStrrepeat,		"int strrepeat( char *, char *, unsigned int ) ;" } ,
	{ ToolsVal,			"double val( char * ) ; " },
	{ ToolsCopynew,			"char * copynew( char *, int, int ) ;" },
	{ ToolsCopy, 			"int copy( char *, char *, int, int ) ;" },
	{ ToolsPos,			"int pos( char *, char * ) ;" },
	{ ToolsPosc,			"int posc( char, char * ) ;" },
	{ ToolsPosi,			"int posi( char *, char *, int ) ;" },
	{ ToolsPosic,			"int posic( char, char *, int ) ;" },
	{ ToolsPosn, 			"int posn( char *, char * ) ;" },
	{ ToolsPosnc,			"int posnc( char, char * ) ;" },
	{ ToolsMpos,			"int mpos( char *, char * ) ;" },
	{ ToolsStrinf,			"int strinf( char *, char * ) ;" },
	{ ToolsDelnew,			"char * delnew( char *, int, int ) ;" },
	{ ToolsDel,			"int del( char *, int, int ) ;" },
	{ ToolsInsertnew,		"char * insertnew( char *, char *, int ) ;" },
	{ ToolsInsert,			"int insert( char *, char *, int ) ;" },
	{ ToolsReplacec,		"int replacec( char *, char, char ) ;" },
	{ ToolsRemplacec,		"int remplacec( char *, char, char ) ;" },
	{ ToolsReplace,			"int replace( char *, char *, char * ) ;" },
	{ ToolsRemplace,		"int remplace( char *, char *, char * ) ;" },
	{ ToolsItos,			"char * itos( int i ) ;" },
	{ ToolsMatchpattern,		"int matchpattern( char * pattern, char * st) ;" },
	{ ToolsStrscan,			"int strscan( char * st, char * sep, ... ) ;" },
	{ ToolsRpad, 			"int rpad( char * st, unsigned int len, char motif ) ;" },
	{ ToolsDrpad, 			"int drpad( char * st, unsigned int len ) ;" },
	{ ToolsLpad, 			"int lpad( char * st, unsigned int len, char motif ) ;" },
	{ ToolsDlpad, 			"int dlpad( char * st, int len ) ;" },
	{ ToolsRtrim, 			"int rtrim( char * st, char * motif ) ;" },
	{ ToolsDrtrim, 			"int drtrim( char * st ) ;" },
	{ ToolsLtrim, 			"int ltrim( char * st, char * motif ) ;" },
	{ ToolsDltrim, 			"int dltrim( char * st ) ;" },
	{ ToolsTrim, 			"int trim( char * st, char * motif ) ;" },
	{ ToolsDtrim, 			"int dtrim( char * st ) ;" },
	{ ToolsScanparam,		"int scanparam( char *, int *, char **argv, char * ) ;" },
	{ ToolsScanparam1,		"int scanparam1( char * st, int *, char ** argv ) ;" },
	{ ToolsParam_init,		"int param_init( int argc, char **argv ) ;" },
	{ ToolsParam_nbr,		"int param_nbr( void ) ;" },
	{ ToolsParam_tab,		"char ** param_tab( void ) ;" },
	{ ToolsParam_scan1,		"int param_scan1( char * val ) ;" },
	{ ToolsParam_scan,		"int param_scan( char * val, char * st ) ;" },
	{ ToolsParam_get,		"char * param_get( int nb ) ;" },
	{ ToolsParam_print,		"void param_print( void ) ;" },
	{ ToolsParam_clean,		"void param_clean( void ) ;" },
	{ ToolsAdddate,			"int adddate( int, char * ) ;" },
	{ ToolsSqr,			"double sqr( double ) ;" },
	{ ToolsMyabs,			"double myabs( double ) ;" },
	{ ToolsMymin,			"double mymin( double, double ) ;" },
	{ ToolsMymini,			"int mymini( int, int ) ;" },
	{ ToolsMymax,			"double mymax( double, double ) ;" },
	{ ToolsMymaxi,			"int mymaxi( int, int ) ;" },
	{ ToolsSgn,			"int sgn( double ) ;" },
	{ ToolsMyrandseed,		"void myrandseed( int ) ;" },
	{ ToolsMyrandomd,		"double myrandomd( void ) ;" },
	{ ToolsMyrandom,		"int myrandom( int ) ;" },
	{ ToolsMyrandomize,		"void myrandomize( void ) ;" },
	{ ToolsSterrno,			"char *sterrno( int value ) ;" },
	{ ToolsSsterrno,		"char *ssterrno( char * code ) ;" },
	{ ToolsExistfile,		"int existfile( char * ) ;" },
	{ ToolsExistdir,		"int existdir( char * ) ;" },
	{ ToolsExistlink,		"int existlink( char * ) ;" },
	{ ToolsExist,			"int exist( char * ) ;" },
	{ ToolsFilesize,		"long filesize( char * ) ;" },
	{ ToolsRmalldir,		"int rmalldir( char * ) ;" },
	{ ToolsFiletime,		"time_t filetime( char * ) ;" },
	{ ToolsDirname,			"char * dirname( char * ) ;" },
	{ ToolsBasename,		"char * basename( char * ) ;" },
	{ ToolsURLencode,		"void URLencode( char * ) ;" },
	{ ToolsURLencodeFilename,	"void URLencodeFilename( char * ) ;" },
	{ ToolsURLdecode,		"void URLdecode( char * ) ;" },
	{ ToolsURLread,			"int URLread( char * URL, char * protocol, char * user, char * password, char * adress, char * port, char * path, char * name, char * param ) ;" },
	{ ToolsBcEval, 			"double bc( char * str ) ;" },
	{ ToolsEncode64,		"void base64_encode( char * orig, char * dest, int nbcar) ;" },
	{ ToolsDecode64,		"int base64_decode( char * buffer ) ;" },
	{ ToolsMD5Cal,			"void MD5Cal( char * inString, char * outString ) ;" },
	{ ToolsMD5CalFile,		"void MD5CalFile (char * filename, char * outString ) ;" },
	{ ToolsBcryptTestPattern,	"int bcrypt_test_pattern( char * pattern, unsigned int pattern_length ) ;" },
	{ ToolsBcryptInit,		"void bcrypt_init( long t ) ;" },
	{ ToolsBcryptString,		"int bcrypt_string( char * st_in, char * st_out, unsigned int length, char * init_pattern, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptString,		"int buncrypt_string( char * st_in, char * st_out, unsigned int length, char * init_pattern, char * key ) ;" },
	{ ToolsBcryptStringPrintable,	"int bcrypt_string_printable( char * st_in, char * st_out, unsigned int length, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptStringPrintable, "int buncrypt_string_printable( char * st_in, char * st_out, unsigned int length, char * key ) ;" },
	{ ToolsBcryptStringBase64,	"int bcrypt_string_base64( char * st_in, char * st_out, unsigned int length, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptStringBase64,	"int buncrypt_string_base64( char * st_in, char * st_out, unsigned int length, char * key ) ;" },
	{ ToolsBcryptStringBase64url,	"int bcrypt_string_base64url( char * st_in, char * st_out, unsigned int length, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptStringBase64url,	"int buncrypt_string_base64url( char * st_in, char * st_out, unsigned int length, char * key ) ;" },
	{ ToolsBcryptStringAuto,	"int bcrypt_string_auto( char * st, unsigned int length, char * init_pattern, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptStringAuto,	"int buncrypt_string_auto( char * st, unsigned int length, char * init_pattern, char * key ) ;" },
	{ ToolsBcryptFile,		"int bcrypt_file( char * filename_in, char * filename_out, char * init_pattern, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptFile,		"int buncrypt_file( char * filename_in, char * filename_out, char * init_pattern, char * key ) ;" },
	{ ToolsBcryptFilePrintable,	"int bcrypt_file_printable( char * filename_in, char * filename_out, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptFilePrintable,	"int buncrypt_file_printable( char * filename, char * filename_out, char * key ) ;" },
	{ ToolsBcryptFileBase64,	"int bcrypt_file_base64( char * filename_in, char * filename_out, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptFileBase64,	"int buncrypt_file_base64( char * filename, char * filename_out, char * key ) ;" },
	{ ToolsBcryptFileBase64url,	"int bcrypt_file_base64url( char * filename_in, char * filename_out, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptFileBase64url,	"int buncrypt_file_base64url( char * filename, char * filename_out, char * key ) ;" },
	{ ToolsBcryptFileAuto,		"int bcrypt_file_auto( char * filename, char * init_pattern, char * key, unsigned int maxlinesize ) ;" },
	{ ToolsBuncryptFileAuto,	"int buncrypt_file_auto( char * filename, char * init_pattern, char * key ) ;" },
	{ ToolsPrintHelp,		"void printhelp( char * filename ) ;" },
	{ NULL,         		NULL }
};

/* creates various system-dependent definitions */
void ToolsSetupFunc(Picoc *pc)
{

    /* make a "struct __DIRStruct" which is the same size as a native DIR structure */
    /* StructDirType = TypeCreateOpaqueStruct(NULL, TableStrRegister("__DIRStruct"), sizeof(DIR)); */
    
    /* get a DIR * type */
    /* DirPtrType = TypeGetMatching(NULL, StructDirType, TypePointer, 0, StrEmpty, TRUE); */

    /* make a "struct __DirentStruct" which is the same size as a native dirent structure */
    /*TypeCreateOpaqueStruct(NULL, TableStrRegister("__DirentStruct"), sizeof(struct dirent));*/
	
    /* define EOF equal to the system EOF */
}


/* Les commandes mini sont incluses dans le mini.h */
#include "mini_h.c"

void IncludeExternalTools(Picoc *pc) {
	IncludeRegister(pc, "mini.h", &MiniSetupFunc, &MiniFunctions[0], MiniDefs) ;
	IncludeRegister(pc, "tools.h", &ToolsSetupFunc, &ToolsFunctions[0], ToolsDefs) ; 
}
