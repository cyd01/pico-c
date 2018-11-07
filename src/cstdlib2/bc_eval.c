#include "../platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>

/*
Syntaxe de compilation en double
 gcc -o bc_eval.exe bc_eval.c -Wall -O3 -lm -mno-cygwin -DMAIN -std=c99
Syntaxe de compilation en long double
 gcc -o bc_eval.exe bc_eval.c -Wall -O3 -lm -mno-cygwin -DLD -DMAIN -std=c99
*/

/*
long double atold (const char *nptr);
long double strtold (const char *nptr, char **endptr);  atold = strtold(nptr, (char **)NULL)
double=64bits, précision=15 décimales +-1.7e-308 -> +-1.7e+308
long double=80bits, précision 38 décimales +-1e-4932 -> +-1e+4932
float precision pi = 3.141593
double precision pi = 3.141592653589793
long double precision pi = 3.141592653589793239 

pi = 4*atan(1) = 2*asin(1) = acos(-1)

Type de donnée	Signification	Taille (en octets)	Plage de valeurs acceptée
char	Caractère	1	-128 à 127
unsigned char	Caractère non signé	1	0 à 255
short int	Entier court	2	-32 768 à 32 767
unsigned short int	Entier court non signé	2	0 à 65 535
int	Entier	2 (sur processeur 16 bits)
4 (sur processeur 32 bits)	-32 768 à 32 767
-2 147 483 648 à 2 147 483 647
unsigned int	Entier non signé	2 (sur processeur 16 bits)
4 (sur processeur 32 bits)	0 à 65 535
0 à 4 294 967 295
long int	Entier long	4	-2 147 483 648 à 2 147 483 647
unsigned long int	Entier long non signé	4	0 à 4 294 967 295
float	Flottant (réel)	4	3.4*10-38 à 3.4*1038
double	Flottant double	8	1.7*10-308 à 1.7*10308
long double	Flottant double long	10	3.4*10-4932 à 3.4*104932
*/


#ifndef LD

#define BC_ERROR 1.7E-308
#define BC_PI 3.141592653589793
#define BC_PATTERN "%15.13g"
#define BC_STRTOD strtod
typedef double bc_double ;

#else

/* #define BC_ERROR 3.4E-4932 */
#define BC_ERROR 1.7E-308
#define BC_PI 3.141592653589793239
              /* 3.1415926535897932384626433832795 */
#define BC_PATTERN "%19.17Lg"
#define BC_STRTOD strtold
typedef long double bc_double ;

#endif


bc_double bc_eval( const char * str ) {
	bc_double bc_error = (bc_double)BC_ERROR ; /* Valeur renvoyee en cas d'erreur */
	bc_double bc_result = (bc_double)0.0 ;
	bc_double dres, dres1 ;

	char *deb, *fin, *cmd=NULL, *pst ;
	unsigned char c ;
	unsigned int i, j, k, p ;
	long int m, n ;
	static unsigned int bc_seed = 0 ;

	bc_result = bc_error ;

	if( str==NULL ) return bc_error ;
	if( strlen(str) == 0 ) { return (bc_double)0.0L ; }
	
	/* Allocation de memoire */
	if( ( cmd=(char*)malloc( strlen(str) + 256 ) ) == NULL ) { return bc_error ; }
	strcpy( cmd, str ) ;

	/* Remplace les , par des ., les {, [ par des }, ] et passage en minuscule */
	for( k=0 ; k<strlen(cmd) ; k++ ) {
		if( cmd[k]==',' ) cmd[k]='.' ;
		else if ( (cmd[k]=='[')||(cmd[k]=='{') ) cmd[k]='(' ;
		else if ( (cmd[k]==']')||(cmd[k]=='}') ) cmd[k]=')' ;
		else if( (cmd[k]>='A')&&(cmd[k]<='Z') ) cmd[k]=cmd[k]-'A'+'a' ;
		}

	/* Verifie les parentheses ouvrantes et fermantes */
	p = 0 ;
	for( i=0 ; i<strlen(cmd) ; i++ ) {
		if( cmd[i]=='(' ) p++ ;
		else if( cmd[i]==')' ) p-- ;
		if( p<0 ) { free( cmd ) ; return bc_error ; }
		}
	if( p!= 0 ) { free( cmd ) ; return bc_error ; }

	/* Remplace les ², ³ par des ^2, ^3  et les  ¼ ½ ¾ par .25*, .50*, .75*  */
	for( i=0 ; i<strlen(cmd) ; i++ ) {
		if( (cmd[i]=='²')||(cmd[i]=='³') ) {
			for( k=strlen(cmd) ; k>i ; k-- ) cmd[k+1]=cmd[k] ;
			switch(cmd[i]) {
				case '²': cmd[i+1] = '2' ; break ;
				case '³': cmd[i+1] = '3' ; break ;
				}
			cmd[i] = '^' ;
			}
		else if( (cmd[i]=='¼')||(cmd[i]=='½')||(cmd[i]=='¾') ) {
			if( cmd[i+1]=='*' ) for( k=strlen(cmd) ; k>i ; k-- ) cmd[k+2]=cmd[k] ;
			else for( k=strlen(cmd) ; k>i ; k-- ) cmd[k+3]=cmd[k] ;
			switch(cmd[i]) {
				case '¼': cmd[i+1] = '2' ; cmd[i+2] = '5' ; break ;
				case '½': cmd[i+1] = '5' ; cmd[i+2] = '0' ; break ;
				case '¾': cmd[i+1] = '7' ; cmd[i+2] = '5' ; break ;
				}
			cmd[i] = '.' ; cmd[i+3] = '*' ;
			}
		}
		
	/* Modification des operateurs à deux caractères: On remplace les && || <= >= == != <> par des ? @ ' ` = ! !   */
	for( i=0 ; i<(strlen(cmd)-1) ; i++ ) {
		if( ((cmd[i]=='&')&&(cmd[i+1]=='&')) || ((cmd[i]=='|')&&(cmd[i+1]=='|')) 
			|| ((cmd[i]=='<')&&(cmd[i+1]=='=')) || ((cmd[i]=='>')&&(cmd[i+1]=='='))
			|| ((cmd[i]=='=')&&(cmd[i+1]=='=')) || ((cmd[i]=='!')&&(cmd[i+1]=='='))
			|| ((cmd[i]=='<')&&(cmd[i+1]=='>')) ) {
			if( cmd[i]=='&' ) cmd[i+1]='?' ;
			else if( cmd[i]=='|' ) cmd[i+1]='@' ;
			else if( cmd[i]=='!' ) cmd[i+1]='!' ;
			else if( cmd[i]=='<' ) { if(cmd[i+1]=='>') cmd[i+1]='!' ; else cmd[i+1]='\'' ; }
			else if( cmd[i]=='>' ) cmd[i+1]='`' ;
			for( k=i ; k<strlen(cmd) ; k++ ) { cmd[k]=cmd[k+1]; if( cmd[k]=='\0' ) break ; }
			}
		}

	/* Rajoute les signes * maquants */
	if( strlen(cmd) > 1 )
	for( i=1 ; i<strlen(cmd) ; i++ ) {
		if( cmd[i]=='(' ) 
			if( (cmd[i-1]==')') || ( (cmd[i-1]>='0')&&(cmd[i-1]<='9') ) ) {
				for( k=strlen(cmd) ; k>=i ; k-- ) cmd[k+1]=cmd[k] ;
				cmd[i] = '*' ;
				}
		}

	/* Ajoute un 0 quand la chaine commence par un - suivi d'une fonction */
	if( (cmd[0]=='-')&& !( (cmd[1]>='0')&&(cmd[1]<='9') ) )
		{ for( k=strlen(cmd) ; k>=0 ; k-- ) { cmd[k+1] = cmd[k] ; if(k==0) break ; } cmd[0] = '0' ; }
			
	/* Ajoute un 0 si la chaîne se termine par un . */
	if( cmd[strlen(cmd)-1]=='.' ) strcat( cmd, "0" ) ;

	/* Nettoyage */
	while( (cmd[strlen(cmd)-1]=='\"')||(cmd[strlen(cmd)-1]=='\t')
		||(cmd[strlen(cmd)-1]==' ')||(cmd[strlen(cmd)-1]=='\r')
		||(cmd[strlen(cmd)-1]=='\n') ) cmd[strlen(cmd)-1]='\0' ;
	while( (cmd[0]=='\"')||(cmd[0]=='\t')||(cmd[0]==' ')||(cmd[0]=='\r')||(cmd[0]=='\n')||(cmd[0]=='+') )
		for( k=0 ; k<strlen(cmd) ; k++ ) cmd[k]=cmd[k+1] ;
			
	while(  (i=(strstr(cmd," ")!=NULL?strstr(cmd," ")-cmd+1:0)) > 0 )
		for( k=i-1 ; k<strlen(cmd) ; k++ ) { cmd[k]=cmd[k+1]; if( cmd[k]=='\0' ) break ; }
	while(  (i=(strstr(cmd,"\t")!=NULL?strstr(cmd,"\t")-cmd+1:0)) > 0 )
		for( k=i-1 ; k<strlen(cmd) ; k++ ) { cmd[k]=cmd[k+1]; if( cmd[k]=='\0' ) break ; }
	while(  (i=(strstr(cmd,"+-")!=NULL?strstr(cmd,"+-")-cmd+1:0)) > 0 )
		for( k=i-1 ; k<strlen(cmd) ; k++ ) { cmd[k]=cmd[k+1]; if( cmd[k]=='\0' ) break ; }
	while(  (i=(strstr(cmd,"(+")!=NULL?strstr(cmd,"(+")-cmd+1:0)) > 0 )
		for( k=i ; k<strlen(cmd) ; k++ ) { cmd[k]=cmd[k+1]; if( cmd[k]=='\0' ) break ; }

	/* Verifie le premier caractere	*/
	c = cmd[0] ;
	if( (c=='^')||(c=='*')||(c=='/')||(c=='%')||(c=='<')||(c=='>')||(c=='=')||(c=='!')||(c=='&')||(c=='|')||(c=='?')||(c=='@')||(c=='\'')||(c=='`') ) 
		{ free( cmd ) ; return bc_error ; }

	/* Verifie le dernier caractere */
	c = cmd[strlen(cmd)-1] ;
	if( ((c<'0')||(c>'9'))&&(c!=')')&&(c!='.') )
		{ free( cmd ) ; return bc_error ; }

	/* Chaine vide */
	if( (strlen(cmd)==0)||(!strcmp(cmd,"()")) ) { free(cmd) ; return (bc_double)0. ; }
	
	/* Allocation de memoire */
	if( ( deb=(char*)malloc( strlen(cmd) + 1 ) ) == NULL ) { free(cmd) ; return bc_error ; }
	if( ( fin=(char*)malloc( strlen(cmd) + 1 ) ) == NULL ) { free(cmd) ; free(deb) ; return bc_error ; }

/* printf("cmd=%s|\n", cmd ) ; */
		
	/* Recherche de nombre seul */
	i=( (((cmd[0]=='-')||(cmd[0]=='+'))&&(strlen(cmd)>1)) 
		|| ( (cmd[0]>='0')&&(cmd[0]<='9') )
		|| (cmd[0]=='.') ) ;
	if( cmd[0]=='.' ) j=1; else j=0; /* decompte le nombre de . */
	if( strlen(cmd)>1 )
		for( k=1 ; k<strlen(cmd) ; k++ ) {
			if( cmd[k] == '.' ) { if( j>0 ) { i=0 ; break ; } else j++ ; }
			else if( ! ((cmd[k]>='0')&&(cmd[k]<='9')) ) { i=0 ; break ; }
			}

	if( i==1 ) /* on a trouvé un nombre */
		/* bc_result = atof( cmd ) ; */
		{
		bc_result = (bc_double)BC_STRTOD( cmd, &pst ) ;
		if( bc_result==HUGE_VAL ) bc_result=bc_error ;
		else if( bc_result==0 ) { if( pst==cmd ) bc_result=bc_error ; }
		if( strlen( pst ) != 0 ) bc_result=bc_error ;
		}
	else {
	/* Recherche d'operateurs hors parenthèses (par ordre inverse de priorité) */
	n=0 ;
	for( i=0 ; i<strlen( cmd ) ; i++ ) {
		if( ((cmd[i]=='?')||(cmd[i]=='@')) && (  /* ? = &&   @ = ||  */
			(cmd[i-1]==')')||(cmd[i-1]=='.')||( (cmd[i-1]>='0')&&(cmd[i-1]<='9') )
			) ) 
			{ if( (n==0)
				||(cmd[n]=='?')||(cmd[n]=='@')
				||(cmd[n]=='&')||(cmd[n]=='|')
				||(cmd[n]=='=')||(cmd[n]=='!')
				||(cmd[n]=='<')||(cmd[n]=='>')||(cmd[n]=='\'')||(cmd[n]=='`')
				||(cmd[n]=='-')||(cmd[n]=='+')
				||(cmd[n]=='*')||(cmd[n]=='/')||(cmd[n]=='%')
				||(cmd[n]=='^') ) n=i ; }

		else if( ((cmd[i]=='&')||(cmd[i]=='|')) && (  /* & = ET bit-a-bit   | = OU bit-a-bit */
			(cmd[i-1]==')')||(cmd[i-1]=='.')||( (cmd[i-1]>='0')&&(cmd[i-1]<='9') )
			) ) 
			{ if( (n==0)
				||(cmd[n]=='&')||(cmd[n]=='|')
				||(cmd[n]=='=')||(cmd[n]=='!')
				||(cmd[n]=='<')||(cmd[n]=='>')||(cmd[n]=='\'')||(cmd[n]=='`')
				||(cmd[n]=='-')||(cmd[n]=='+')
				||(cmd[n]=='*')||(cmd[n]=='/')||(cmd[n]=='%')
				||(cmd[n]=='^') ) n=i ; }

		else if( ((cmd[i]=='=')||(cmd[i]=='!')) && (
			(cmd[i-1]==')')||(cmd[i-1]=='.')||( (cmd[i-1]>='0')&&(cmd[i-1]<='9') )
			) ) 
			{ if( (n==0)
				||(cmd[n]=='=')||(cmd[n]=='!')
				||(cmd[n]=='<')||(cmd[n]=='>')||(cmd[n]=='\'')||(cmd[n]=='`')
				||(cmd[n]=='-')||(cmd[n]=='+')
				||(cmd[n]=='*')||(cmd[n]=='/')||(cmd[n]=='%')
				||(cmd[n]=='^') ) n=i ; }
				
		else if( ((cmd[i]=='<')||(cmd[i]=='>')||(cmd[i]=='\'')||(cmd[i]=='`')) && ( /* ' = <=     ` = >=  */
			(cmd[i-1]==')')||(cmd[i-1]=='.')||( (cmd[i-1]>='0')&&(cmd[i-1]<='9') )
			) ) 
			{ if( (n==0)
				||(cmd[n]=='<')||(cmd[n]=='>')||(cmd[n]=='\'')||(cmd[n]=='`')
				||(cmd[n]=='-')||(cmd[n]=='+')
				||(cmd[n]=='*')||(cmd[n]=='/')||(cmd[n]=='%')
				||(cmd[n]=='^') ) n=i ; }
		
		else if( ((cmd[i]=='-')||(cmd[i]=='+')) && (
			(cmd[i-1]==')')||(cmd[i-1]=='.')||( (cmd[i-1]>='0')&&(cmd[i-1]<='9') )
			) ) 
			{ if( (n==0)
				||(cmd[n]=='-')||(cmd[n]=='+')
				||(cmd[n]=='*')||(cmd[n]=='/')||(cmd[n]=='%')
				||(cmd[n]=='^') ) n=i ; }
			
		else if( ((cmd[i]=='*')||(cmd[i]=='/')||(cmd[i]=='%')) && (
			(cmd[i-1]==')')||(cmd[i-1]=='.')||( (cmd[i-1]>='0')&&(cmd[i-1]<='9') )
			) )
			{ if( (n==0)
				||(cmd[n]=='*')||(cmd[n]=='/')||(cmd[n]=='%')
				||(cmd[n]=='^') ) n=i ; }
			
		else if( (cmd[i]=='^') && (
			(cmd[i-1]==')')||(cmd[i-1]=='.')||( (cmd[i-1]>='0')&&(cmd[i-1]<='9') )
			) )
			{ if( ( n==0 )
				||(cmd[n]=='^') ) n=i ; }
			
		else if( cmd[i] == '(' ) {
			p = 1 ;
			do { 
				i++ ; 
				if( cmd[i]=='(' ) p++ ;
				if( cmd[i]==')' ) p-- ;
				}
			while( (i<strlen( cmd ))&&(p!=0) ) ;
			}
		}

	if( n>0 ) { /* Operateur trouve */
		memcpy( deb, cmd, n ) ; deb[n] = '\0' ;
		memcpy( fin, cmd+n+1 , strlen(cmd)-(n+1) ) ; fin[strlen(cmd)-(n+1)] = '\0' ;
		switch( cmd[n] ) {
			case '?': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = dres && bc_result ;
				break ;
			case '@': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = dres || bc_result ;
				break ;
			case '&': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = (long int)dres & (long int)bc_result ; 
				break ;
			case '|': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = (long int)dres | (long int)bc_result ; 
				break ;
			case '=': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = dres == bc_result ;
				break ;
			case '!':
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = dres != bc_result ;
				break ;
			case '<': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = dres < bc_result ;
				break ;
			case '>':
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = dres > bc_result ;
				break ;
			case '\'': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = dres <= bc_result ;
				break ;
			case '`': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = dres >= bc_result ;
				break ;
			case '-': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result=dres-bc_result ; 
				break ;
			case '+': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result=dres+bc_result ; 
				break ;
			case '*': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result=dres*bc_result ; 
				break ;
			case '/': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error ) {
					if( bc_result==0 ) bc_result=bc_error ; 
					else bc_result=dres/bc_result ; 
					}
				break ;
			case '%': /* Modulo */
				while( strlen(deb)>7 ) {
					c=deb[7] ; deb[7]='\0' ;
					m =  (long int)(bc_eval(deb)) %  (long int)(bc_eval(fin)) ;
					deb[7] = c ;
					pst=deb+7;
					sprintf( deb, "%ld%s", m, pst ) ;
					}
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error )
					bc_result = (long int)dres % (long int)bc_result ;
				break ;
			case '^': 
				if( (dres=bc_eval(deb))==bc_error ) bc_result=bc_error ;
				else if( (bc_result=bc_eval(fin))!=bc_error ) {
					if( (dres==0)&&(bc_result==-1) ) bc_result=bc_error ;
					else if( (dres<0)&&( bc_result!=ceil(bc_result) ) ) bc_result=bc_error ;
					else bc_result=pow( dres, bc_result ) ;
					}

				break ;
			}
		}
	
	else {

		/* Recherche de parenthèse */
		if( cmd[0]=='(' ) {
			p=1 ; i=1 ;
			while( (p!=0)&&(i<strlen(cmd)) ) {
				if( cmd[i]=='(' ) p++ ;
				if( cmd[i]==')' ) p-- ;
				i++;
				}
			if( (p==0)&&(i>2) ) {
				memcpy( deb, cmd+1, i-2 ) ; deb[i-2] = '\0' ;
				for( k=0 ; k<(strlen(cmd)-i+1) ; k++ ) { cmd[k]=cmd[k+i]; if( cmd[k]=='\0' ) break ; }
				bc_result = bc_eval( deb ) ; 
				}
			}

		/* Recherche de fonctions */
		else if( (toupper(cmd[0])>='A')&&(toupper(cmd[0])<='Z') ) {
			j = ( strstr(cmd,"(")!=NULL?strstr(cmd,"(")-cmd+1:0 )  ;
			p=1 ; i=j;
			while( (p!=0)&&(i<strlen(cmd)) ) {
				if( cmd[i]=='(' ) p++ ;
				if( cmd[i]==')' ) p-- ;
				i++;
				}
			if( (p==0)&&(i>=(j+1)) ) {
				memcpy( deb, cmd, j ) ; deb[j] = '\0' ;
				memcpy( fin, cmd+j, i-(j+1) ) ; fin[i-(j+1)] = '\0' ;
				for( k=0 ; k<(strlen(cmd)-i+1) ; k++ ) { cmd[k]=cmd[k+i] ; if( cmd[k]=='\0' ) break ; }

				if( !strcmp(deb,"a(") ) /* Arrangement */
					{
					for( k=0 ; (k<strlen(fin))&&(fin[k]!=';') ; k++ )
						{ deb[k]=fin[k] ; deb[k+1]='\0' ; }
					strcpy( fin, fin+k+1 ) ;
					dres = bc_eval( deb ) ;
					bc_result = bc_eval( fin ) ;
					if( dres==bc_result ) bc_result = 1 ;
					else if( dres > bc_result ) bc_result = bc_error ;
					else {	dres1 = bc_result ;
						for( k = bc_result-1 ; k >= (dres1-dres+1) ; k-- )
							bc_result = bc_result * k ;
						}
					}
				else if( !strcmp(deb,"abs(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=fabs( bc_result ) ; }
				else if( !strcmp(deb,"acos(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=((bc_result>1)||(bc_result<-1))?bc_error:acos(bc_result) ;
					}
				else if( !strcmp(deb,"acosh(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=(bc_result<1)?bc_error:acosh(bc_result) ;
					}
				else if( !strcmp(deb,"asin(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=((bc_result>1)||(bc_result<-1))?bc_error:asin(bc_result) ;
					}
				else if( !strcmp(deb,"asinh(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=asinh( bc_result ) ; }
				else if( !strcmp(deb,"atan(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=atan( bc_result ) ; }
				else if( !strcmp(deb,"atanh(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=((bc_result>=1)||(bc_result<=-1))?bc_error:atanh(bc_result) ;
					}
				else if( !strcmp(deb,"bin(") ) {
					n = 0 ; bc_result = 1 ;
					if( strlen(fin)>0 ) {
						if( (strlen(fin)==(8*sizeof(long int)))&&(fin[0]=='1') ) {/* Cas d'un nombre negatif */
							for( i=(8*sizeof(long int)-1) ; i>=0 ; i-- ) {
								if( fin[i]=='1' ) { fin[i]='0' ; break ; }
								else if( fin[i]=='0' ) fin[i]='1' ;
								else bc_result = bc_error ;
								}
							for( i=0 ; i<(8*sizeof(long int)) ; i++ ) { 
								if( fin[i]=='0' ) fin[i]='1' ; 
								else if( fin[i]=='1' ) fin[i]='0' ; 
								else bc_result = bc_error ;
								}
							if( bc_result!=bc_error ) bc_result = -1.0 ;
							}
						for( i=strlen(fin),j=0 ; i>0 ; i--, j++ ) {
							if(fin[i-1]=='1') n=n+(long int)(pow(2.0,(bc_double)1.0*j)) ;
							else if(fin[i-1]!='0') bc_result=bc_error ;
							}
						}
					if( bc_result!=bc_error ) bc_result = bc_result*n ;
					}
				else if( !strcmp(deb,"c(") ) /* Combinaison */
					{
					for( k=0 ; (k<strlen(fin))&&(fin[k]!=';') ; k++ )
						{ deb[k]=fin[k] ; deb[k+1]='\0' ; }
					strcpy( fin, fin+k+1 ) ;
					dres = bc_eval( deb ) ;
					bc_result = bc_eval( fin ) ;
					if( dres==bc_result ) bc_result = 1 ;
					else if( dres > bc_result ) bc_result = bc_error ;
					else {	dres1 = bc_result ;
						for( k = bc_result-1 ; k >= (dres1-dres+1) ; k-- )
							bc_result = bc_result * k ;
						if( dres>1 )
						for( k=2 ; k<=dres ; k++ )
							bc_result=bc_result / k ;
						}
					}
				else if( !strcmp(deb,"cbr(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=pow( bc_result, 3 ) ; }
				else if( !strcmp(deb,"cbrt(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=cbrt( bc_result ) ; }
				else if( !strcmp(deb,"ceil(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=ceil( bc_result ) ; }
				else if( !strcmp(deb,"comp(") ) /* Complement à 1 */
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=~(long int)bc_result ; }
				else if( !strcmp(deb,"cos(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=cos( bc_result ) ; }
				else if( !strcmp(deb,"cosh(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=cosh( bc_result ) ; }
				else if( !strcmp(deb,"cotan(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=(bc_result==0)?bc_error:cosh(bc_result)/sin(bc_result) ;
					}
				else if( !strcmp(deb,"deg2rad(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result= acos(-1.0)*(bc_result/180.0) ; }
				else if( !strcmp(deb,"exp(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=exp( bc_result ) ; }
				else if( !strcmp(deb,"fact(") ) { 
					bc_result = 1 ;	
					if( ( j = bc_eval( fin ) ) == bc_error ) bc_result = bc_error ;
					else if( j>1 ) for( i=2 ; i<=j ; i++ ) bc_result=bc_result*i ;
					}
				else if( !strcmp(deb,"floor(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=floor( bc_result ) ; }
				else if( !strcmp(deb,"help(") ) {
					printf("Operators: ^, / * %%, + -, < > <= >=, == !=, & |, && ||\n") ;
					printf( "Known functions: a, abs, acos, acosh, asin, asinh, atan, atanh, bin, c, cbr, cbrt, ceil, comp, cos, cosh, cotan, deg2rad, exp, fact, floor, help, hex, int, inv, ln, log, not, oct, pi, rad2deg, rand, sgn, sin, sinh, sqr, sqrt, tan, tanh, time\n" );
					bc_result=0. ;
					return 0. ;
					}
				else if( !strcmp(deb,"hex(") ) 
					{ if( sscanf(fin,"%lX",(long unsigned int *)&n)==0 ) bc_result=bc_error ; else bc_result=1.0*n ; }
				else if( !strcmp(deb,"int(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=(int)( bc_result ) ; }
				else if( !strcmp(deb,"inv(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=(bc_result==0)?bc_error:(1/bc_result) ;
					}
				else if( !strcmp(deb,"ln(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=(bc_result<=0)?bc_error:log(bc_result) ;
					}
				else if( !strcmp(deb,"log(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=(bc_result<=0)?bc_error:log10(bc_result) ;
					}
				else if( !strcmp(deb,"not(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error )
						bc_result=(bc_result==0.0)?1.0:0.0 ;
					}
				else if( !strcmp(deb,"oct(") ) 
					{ if( sscanf(fin,"%lo",(long unsigned int *)&n)==0 ) bc_result=bc_error ; else bc_result=1.0*n ; }
				else if( !strcmp(deb,"pi(") ) bc_result = BC_PI ;
				else if( !strcmp(deb,"rad2deg(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result= bc_result*180.0/acos(-1.0) ; }
				else if( !strcmp(deb,"rand(") )
					{ bc_seed = (unsigned int)(time(NULL)*cos(bc_seed+time(NULL))) ;
					  srand( bc_seed ) ;
					  if( strlen(fin)>0) {
							if( (bc_result=bc_eval( fin ))!=bc_error ) {
							if( bc_result==0 ) bc_result=(bc_double)(1.0*rand())/(RAND_MAX+1.0) ;
							else {
								dres=(bc_double)1.0*floor( fabs(bc_result) ) ;
								bc_result=(bc_double)( 1+(int)(dres*1.0*rand()/(RAND_MAX+1.0)) );
								}
							}
						}
					else { bc_result=(bc_double)(1.0*rand())/(RAND_MAX+1.0) ; }
					}
				else if( !strcmp(deb,"sgn(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) {
						if( bc_result > 0. ) bc_result=1.0 ;
						else if( bc_result < 0. ) bc_result=-1.0 ; }
						}
				else if( !strcmp(deb,"sin(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=sin( bc_result ) ; }
				else if( !strcmp(deb,"sinh(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=sinh( bc_result ) ; }
				else if( !strcmp(deb,"sqr(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=bc_result*bc_result ; }
				else if( !strcmp(deb,"sqrt(") ) 
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=(bc_result<0)?bc_error:sqrt(bc_result) ;
					}
				else if( !strcmp(deb,"tan(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) 
						bc_result=(bc_result==(3.141592653589793239/2))?bc_error:tan(bc_result) ;
					}
				else if( !strcmp(deb,"tanh(") )
					{ if( (bc_result=bc_eval( fin ))!=bc_error ) bc_result=tanh( bc_result ) ; }
				else if( !strcmp(deb,"time(") ) bc_result = (bc_double) time(0) ;

				else bc_result = bc_error ;
				}
			else { bc_result = 0. ; } /* nombre de parentheses incoherentes */
			}
		else {
			/* bc_result = atof( cmd ) ; */
			bc_result = (bc_double)BC_STRTOD( cmd, &pst ) ;
			if( bc_result==HUGE_VAL ) bc_result=bc_error ;
			else if( bc_result==0. ) { if( pst==cmd ) bc_result=bc_error ; }
			if( strlen( pst ) != 0 ) bc_result=bc_error ;
			}
		}
	}

	free( cmd ) ; free( deb ) ; free( fin ) ;
	return bc_result ;
	}



bc_double bc_function( const char * function, const int nbvar, ... ) {
	bc_double bc_error = BC_ERROR ; /* Valeur renvoyee en cas d'erreur */
	bc_double bc_result = 0. ;
	bc_double value ;

	char * str = NULL, *var, buffer[256] ;
	int num, i, j ;
	va_list ap;

	bc_result = bc_error ;

	if( ( str = (char*)malloc( strlen(function)+nbvar*250 ) ) != NULL ) {
		strcpy( str, function ) ;
		if( nbvar>0 ) {
			va_start( ap, nbvar ) ;
			
			for( num=1 ; num<=nbvar ; num++ ) {
				var = (char*) va_arg (ap, char *);
				value = (bc_double) va_arg (ap, bc_double) ;
				if( strlen(var) == 0 ) { va_end( ap ) ; break ; }
				for( i=0 ; i<strlen(str) ; i++ ) {
					if( (strstr(str+i,var)==(str+i)) 
						&& ((i==0) || !( (toupper(str[i-1])>='A')&&(toupper(str[i-1])>='Z')) )
						&& !( (toupper(str[i-1+strlen(var)])>='A')&&(toupper(str[i-1+strlen(var)])>='Z') )
						) {

						sprintf( buffer, BC_PATTERN, value ) ;
						
						if( strlen( buffer ) > 0 ) {
							for( j=strlen(str) ; j>=i ; j-- ) 
								str[j+strlen(buffer)-strlen(var)]=str[j] ;
							for( j=0 ; j<strlen(buffer) ; j++ ) str[i+j]=buffer[j] ;
							}
						}
					}
				}
	
			va_end( ap ) ;
			}

		bc_result = bc_eval( str ) ;
		free( str ) ;
		}

	return bc_result ;
	}


bc_double bc_resolve( const char * function, const char * name, const bc_double value_init, const bc_double precision, const long int nb_iter_max ) {
	bc_double bc_error = BC_ERROR ; /* Valeur renvoyee en cas d'erreur */
	bc_double bc_result = 0. ;
	bc_double res, value, pente ;

	unsigned long int iter = 1 ;
	bc_result = bc_error ;
	value = value_init ;

	res = bc_function( function, 1, name, value ) ;
	while( (fabs(res)>precision) && (iter<nb_iter_max) ) {
		iter++ ;
		pente=( bc_function( function, 1, name, value ) - bc_function( function, 1, name, value+(1000*precision) ) ) / (1000*precision) ;
		value = value+res/pente ;
		res = bc_function( function, 1, name, value ) ;
		}

/* printf("iter=%ld\n",iter) ; */
		
	if( fabs(res)<=precision ) bc_result = value ;
	
	return bc_result ;
	}


void bc_base( const char c, const bc_double f, char * stres ) {
	char st[1024] = "" ;
	long int v, i, ex ;

	if( stres==NULL ) return ;

	for( i=0 ; i<(8*sizeof(long int)) ; i++ ) st[i]='0' ;
	st[8*sizeof(long int)]='\0' ; 
	
	switch( toupper(c) ) {
		case 'X': sprintf( stres, "%lX", (long int)f ) ; break ;
		case 'O': sprintf( stres, "%lo", (long int)f ) ; break ;
		case 'B':
			v = labs((long int)f) ;
			ex=(long int)(log((bc_double)v)/log(2));
			for( i=ex ; i>=0 ; i-- ) {
				if(v-(pow(2.0,(bc_double)i))>=0) {
					v=v-(long int)(pow(2.0,(bc_double)i));
					st[8*sizeof(long int)-i-1] = '1' ;
					}
				}
			if( f<0 ) { /* Cas d'un nombre negatif */
				for( i=0 ; i<(8*sizeof(long int)) ; i++ ) 
					if( st[i]=='0' ) st[i]='1' ; 
					else if( st[i]=='1' ) st[i]='0' ;
				for( i=(8*sizeof(long int)-1) ; i>=0 ; i-- ) {
					if( st[i]=='0' ) { st[i]='1' ; break ; }
					else if( st[i]=='1' ) st[i]='0' ;
					}
				}
			if( strlen(st) == 0 ) strcpy( st, "0" ) ;
			/* On supprime les zeros devant */
			while( st[0]=='0' ) for( i=0 ; i<strlen(st) ; i++ ) st[i] = st[i+1] ;
			sprintf( stres, "%s", st ) ; break ;
		default : sprintf( stres, "%ld", (long int)f ) ; break ;
		}
	}


void bc_print( const bc_double d ) {
	char float_format[] = BC_PATTERN ;
	char buf[256] ;
	int i;
	
	if( d == BC_ERROR ) { printf( "Error" ) ; return ; }
	
	sprintf( buf, float_format, (double)d ) ;
	/* Même dans le cas de long double on reconverti en double.
	   printf sous MinGW (sous Windows) ne sait pas traiter les long double
	   Apprement les calculs sont tout de même corrects, le résultat de bc_eval peut être considéré comme bon
	*/

	while( buf[strlen(buf)-1]==' ' ) buf[strlen(buf)-1]='\0' ;
	if( (buf[strlen(buf)-1]=='.')||(buf[strlen(buf)-1]=='e') ) buf[strlen(buf)-1]='\0' ;
	while( buf[0]==' ' ) for( i=0 ; i<strlen(buf) ; i++ ) buf[i]=buf[i+1] ;

	printf( "%s", buf ) ;
	}


/*
void print_log( const char *fmt, ... ) {
	FILE * fp ;
	va_list ap;
	if( ( fp = fopen( "msh.log", "a" ) ) == NULL ) return ;
	va_start( ap, fmt ) ;
	vfprintf( fp, fmt, ap ) ;
	fclose( fp ) ;
	va_end( ap ) ;
	}
*/

void bc_usage( const char * progname ) { fprintf(stderr,"Usage: %s [-b] [-o] [-x] string\n", progname) ; }
	
int bc_main(int argc , char **argv ) {
	char stres[156] = "" ;
	int i=1, j;
	char o_flag = ' ' ;
	if( argc<=1 ) { bc_usage( argv[0] ) ; exit(1) ; }
	else {
		for( j=1 ; j<argc ; j++ ) {
			if( argv[j][0] != '-' ) break ;
			if( !strcmp( argv[j], "-b" )||!strcmp( argv[j], "-B" ) ) { o_flag = 'b' ; i++ ; }
			else if( !strcmp( argv[j], "-o" )||!strcmp( argv[j], "-O" ) ) { o_flag = 'o' ; i++ ; }
			else if( !strcmp( argv[j], "-x" )||!strcmp( argv[j], "-X" ) ) { o_flag = 'x' ; i++ ; }
			else if( !strcmp( argv[j], "-h" ) ) { bc_usage( argv[0] ) ; exit(1) ; }
			}
		switch( o_flag ) { 
			case 'b': bc_base( 'b', bc_eval( argv[i] ), stres ) ; printf( "%s\n", stres ) ; break ;
			case 'o': bc_base( 'o', bc_eval( argv[i] ), stres ) ; printf( "%s\n", stres ) ; break ;
			case 'x': bc_base( 'x', bc_eval( argv[i] ), stres ) ; printf( "%s\n", stres ) ;break ;
			default: bc_print( bc_eval( argv[i] ) ) ; printf( "\n" ) ; break ;
			}
		}
	
	return 0 ;
	}
	
#ifdef MAIN
int main(int argc , char **argv ) {
	return bc_main( argc, argv ) ;
	}
#endif
