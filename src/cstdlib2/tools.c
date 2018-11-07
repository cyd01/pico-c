/* TOOLS C/C++ 
   Copyright (C) 1999, 2000, 2001 Leonard Nero
   Contributed by Lenny
   e-mail lenny.nero@zdnetonebox.com

This file is part of GNU CC.
*/

#include "tools.h"


#ifdef DEBUG_MODE
#include "../leaktracker.h"
#endif


/* Numero de version de la librairie */
const char __tools_version_header[20] = "1.23 05/02/2008" ;
const char __tools_version_body[20] =   "1.38 24/02/2000" ;

void printversion_tools(void) {
	printf( "Version librairie TOOLS\nheader : %s\nbody : %s\n", __tools_version_header, __tools_version_body ) ;
	}


/* Partie specifique Windows */
#ifdef WIN32
int WINAPI
dll_init_tools(HANDLE h, DWORD reason, void *foo)
{
    return 1;
}  
#endif

int mprintf( const char * ch )
{	char * s;
	size_t i;
	/*set_new_handler(0);s=new char[strlen(ch)+1];*/
	if( ( s = (char *) malloc( strlen( ch ) + 1 ) ) == NULL ) return 1;
	strcpy(s,ch);
	for(i=0;i<strlen(s);i++)
		{		
		switch(s[i])
				{
case -23 : s[i]=-126;break;case -24 : s[i]=-118;break;case -22 : s[i]=-120;break;case -21 : s[i]=-119;break;
case -32 : s[i]=-123;break;case -31 : s[i]=-96;break;case -30 : s[i]=-125;break;case -28 : s[i]=-124;break;case -27 : s[i]=-122;break;
case -7 : s[i]=-105;break;case -6 : s[i]=-93;break;case -5 : s[i]=-106;break;case -4 : s[i]=-127;break;
case -20 : s[i]=-115;break;case -19 : s[i]=-95;break;case -18 : s[i]=-116;break;case -17 : s[i]=-117;break;
case -14 : s[i]=-107;break;case -13 : s[i]=-94;break;case -12 : s[i]=-109;break;case -10 : s[i]=-108;break;
case -1 : s[i]=-104;break;case -25 : s[i]=-121;break;case -15 : s[i]=-92;break;
				}
			}
	printf("%s",s);
	/*delete[] s;*/free(s);
	return 0 ;
	}

bool find( const char nom[] ) {
	bool test = true ;
	FILE * fp ;
	fp = fopen( nom, "r" ) ;
	if( fp == NULL ) test = false ;
	else fclose( fp ) ;
	return test ;
	}


/**************************************************************************
		FONCTIONS DE GESTION DE CHAINES
**************************************************************************/
int maj( int c ) {
  	if((c>='A') && (c<='Z')) return c;
	if((c>='a') && (c<='z')) {c=toupper(c);return c;}

	if((c=='è') || (c=='é') || (c=='ê') || (c=='ë')) c='E';
	if((c==-118) || (c==-126) || (c==-120) || (c==-119)) c='E';

	if((c=='à') || (c=='á') || (c=='â') || (c=='ä') || (c=='å')) c='A';
	if((c==-123) || (c==-96) || (c==-125) || (c==-124) || (c==-122)) c='A';

	if((c=='ù') || (c=='ú') || (c=='û') || (c=='ü')) c='U';
	if((c==-105) || (c==-93) || (c==-106) || (c==-127)) c='U';

	if((c=='ì') || (c=='í') || (c=='î') || (c=='ï')) c='I';
	if((c==-115) || (c==-95) || (c==-116) || (c==-117)) c='I';

	if((c=='ò') || (c=='ó') || (c=='ô') || (c=='ö')) c='O';
	if((c==-107) || (c==-94) || (c==-109) || (c==-108)) c='O';

	if(c=='ÿ') c='Y';
	if(c==-104) c='Y';

	if(c=='ç') c='C';
	if(c==-121) c='C';

	if(c=='ñ') c='N';
	if(c==-92) c='N';
	return c ;
	}

/* Fonction permettant de passer une chaine de caracteres en majuscules */
#ifdef CPPLUS
int majuscule(char ch[])
{	size_t i;
	if(ch==NULL) return -1;
	for(i=0;i<strlen(ch);i++) {ch[i]=maj(ch[i]);}
	return strlen(ch);}

int majuscule(signed char ch[])
{	return majuscule((char*)ch);}
#else
int majuscule(signed char ch[])
{	unsigned int i;
	if(ch==NULL) return -1;
	for(i=0;i<strlen((const char*)ch);i++) {ch[i]=maj(ch[i]);}
	return strlen((const char*)ch);}
#endif

/* Fonction de comparaison de chaine en majuscule */
int stricmp( const char * s1, const char * s2 ) {
	char * ss1, * ss2 ;
	int pos ;
	ss1 = (char *) malloc( strlen( s1 ) + 2 ) ;
	ss2 = (char *) malloc( strlen( s2 ) + 2 ) ;
	strcpy( ss1, s1 ) ; majuscule( (signed char*) ss1 ) ;
	strcpy( ss2, s2 ) ; majuscule( (signed char*) ss2 ) ;
	pos = strcmp( ss1, ss2 ) ;
	free( ss1 ) ; free( ss2 ) ;
	return pos ;
	}

/*
void strcat(char * ch1, char ch2)
{	char st[3];
	st[0]=ch2;st[1]='\0';
	strcat(ch1,st);}
*/

char * strnew( const double f ) {
	char * s, * st ;
	s = (char *) malloc( 30 ) ;
	if( s == NULL ) return NULL ;
	sprintf( s, "%0.14g", f ) ;
	st = (char *) malloc( strlen( s ) + 1 ) ;
	if( st == NULL ) return NULL ;
	strcpy( st, s ) ;
	free( s ) ;
	return st ; 
	}

/* Fonction permettant de remplir une chaine de caracteres avec un entier */
int str( char * s, double const f ) {
	if( s == NULL ) return -1 ;
	sprintf( s, "%0.14g", f ) ;
	return 0 ;
	}
	
/* Fonction permettant de retrouver une sous-chaine dans une autre en partant de la fin */
char * strbstr( char * ch1, const char * ch2 ) {
	char * p, * res ;
        p = ch1 ;
        if( strlen( ch1 ) > 1 ) {
                p += strlen( ch1 ) - 1 ;
                while( ( ( res = (char*) strstr( p, ch2 ) ) == NULL ) && ( p != ch1 ) )
                        { p-- ; }
                }
        else { if( strcmp( ch1, ch2 ) ) p = NULL ; }
        return p ; 
        }

/* Fonction permettant de concatener un caractere a la fin d'une chaine de caracteres */
char * strcatc( char * st , const char c ) {
	char cc[2] ;
	cc[0] = c ; cc[1] = '\0' ;
	strcat( st, cc ) ;
	return st ;
	}
	
/* Fonction permettant de concatener la première chaîne au début de la seconde */
char * strbcat( const char * st, char * buf ) {
	char * st1 ;
	st1 = (char*) malloc( strlen( st ) + strlen( buf ) + 1 ) ;
	if( st1 == NULL ) return NULL ;
	strcpy( st1, st ) ;
	strcat( st1, buf ) ;
	strcpy( buf, st1 ) ;
	free( st1 ) ;
	return buf ;
	}

/* Fonction permettant de construire une chaine de caracteres par repetition d'une autre chaine */
LINKDLL int strrepeat( char * st, const char * init, const unsigned int n ) {
	unsigned int i ;
	if( ( st==NULL ) || ( init==NULL ) ) return 0 ;
	st[0] = '\0' ;
	if( ( n > 0 ) && ( strlen(init) > 0 ) )
		for( i=0 ; i<n ; i++ )
			strcat( st, init ) ;
	return strlen( st ) ;
	}

/* Fonction transformant une chaine de caracteres en réel (double) */
double val(const char ch[]) {
	double f ;
	if( ch == NULL ) return -1 ;
	f = atof( ch ) ;
	return f ; 
	}

char * copynew(char const st[], int const i, int const j) {
	char * s ;
	int len = strlen( st ) , k ;
	
	if( st == NULL ) return NULL ;
	if( ( j > 0 ) && ( i > 0 ) && ( i <= len ) ) {
		s = (char *) malloc( j + 1 ) ;
		if( s == NULL ) return NULL ;
		for( k = 0 ; k < j ; k++ ) {
			 if( ( i + k - 1 ) < len ) s[k] = st[i+k-1] ;
		 	else s[k] = '\0' ; 
		 	}
		s[j] = '\0' ;
		return s ; 
		}
	else return NULL ; 
	}

/* Fonction permettant de copier des carateres d'une chaine dans une autre 
	s: chaine en sortie
	st: chaine initiale
	i: position de départ
	j: nombre de caracteres a copier */
int copy( char * s, const char * st, const int i, const int j ) {
	int k, len = strlen( st ) ;
	if( ( s == NULL ) || ( st == NULL ) ) return -1 ;
	if( ( j > 0 ) && ( i > 0 ) && ( i <= len ) ) {
		for( k = 0 ; k < j ; k++ ) {
			if( ( i + k - 1 ) < len ) s[k] = st[i+k-1] ;
		 	else s[k] = '\0' ; 
		 	}
		s[j] = '\0' ;
		return 0 ; 
		}
	else return -2 ;
	}

/* Fonction permettant de retrouver la position d'une chaine dans une autre chaine */
int pos( const char * c, const char * ch ) {
	char * c1 , * ch1 , * cc ;
	int res ;
	if( ( ch == NULL ) || ( c == NULL ) ) return -1 ;
	if( ( c1 = (char *) malloc( strlen( c ) + 1 ) ) == NULL ) return -2 ;
	if( ( ch1 = (char *) malloc( strlen( ch ) + 1 ) ) == NULL ) { free( c1 ) ; return -3 ; }
	strcpy( c1, c ) ; strcpy( ch1, ch ) ;
	cc = (char *) strstr( ch1, c1 ) ;
	if( cc == NULL ) res = 0 ;
	else res = (int) ( cc - ch1 ) + 1 ;
	if( (size_t) res > strlen( ch ) ) res = 0 ;
	free( ch1 ) ;
	free( c1 ) ;
	return res ; 
	}

/* Fonction permettant de retrouver la position d'un caractere dans une chaine */
int posc( const char c, const char * ch ) {
	char * ch1 , * cc ;
	int res ;
	if( ch == NULL ) return -1 ;
	if( ( ch1 = (char *) malloc( strlen( ch ) + 1 ) ) == NULL ) return -2 ;
	strcpy( ch1, ch ) ;
	cc = (char *) strchr( ch1, c ) ;
	if( cc == NULL ) res = 0 ;
	else res = (int) ( cc - ch1 ) + 1 ;
	if( (size_t) res > strlen( ch ) ) res = 0 ;
	free( ch1 ) ;
	return res ; 
	}

/* Fonction permettant de retrouver la position d'une chaîne de caracteres dans une chaine a partir d'une position donnee */
int posi( const char * c, const char * ch, const int ipos ) {
	int res ;
	if( ( c == NULL ) || ( ch == NULL ) ) return -1 ;
	if( ( ipos <= 0 ) || ( (size_t) ipos > strlen( ch ) ) ) return 0 ;
	res = pos( c, ch + ( ipos - 1 ) ) ;
	if( res > 0 ) return res + ( ipos -1 ) ;
	else return 0 ;
	}

/* Fonction permettant de retrouver la position d'un caractere dans une chaine a partir d'une position donnee */
int posic( const char c, const char * ch, const int ipos ) {
	int res ;
	if( ch == NULL ) return -1 ;
	if( ( ipos <= 0 ) || ( (size_t) ipos > strlen( ch ) ) ) return 0 ;
	res = posc( c, ch + ( ipos - 1 ) ) ;
	if( res > 0 ) return res + ( ipos - 1 ) ;
	else return 0 ;
	}

/* Fonction permettant de retrouver la position d'une chaine dans une autre en partant de la fin */
int posn( const char * c, const char * ch ) {
	char * c1 , * ch1 ;
	char * cc, * s ;
	int res = 0 ;
	if( ( ch == NULL ) || ( c == NULL ) ) return -1 ;
	if( ( c1 = (char *) malloc( strlen( c ) + 1 ) ) == NULL ) return -2 ;
	if( ( ch1 = (char *) malloc( strlen( ch ) + 1 ) ) == NULL ) { free( c1 ) ; return -3 ; }
	strcpy( c1, c ) ; strcpy( ch1, ch ) ;
	s = &( ch1[ strlen( ch1 ) ] ) ;
	while( ( s >= ch1 ) && ( res == 0 ) ) {
		cc = (char *) strstr( s, c1 ) ;
		if( cc != NULL ) res = (int)( cc - ch1 ) + 1 ;
		s-- ; 
		}
	if( (size_t) res > strlen( ch ) ) res = 0 ;
	free( ch1 ) ;
	free( c1 ) ;
	return res ;
	}

/* Fonction permettant de retrouver la position d'un caractere dans une chaine en partant de la fin */
int posnc( const char c, const char * ch ) {
	char * ch1, * cc ;
	int res ;
	if( ch == NULL ) return -1 ;
	if( ( ch1 = (char *) malloc( strlen( ch ) + 1 ) ) == NULL ) return -2 ; 
	strcpy( ch1, ch ) ;
	cc = (char *) strrchr( ch1, c ) ;
	if( cc == NULL ) res = 0 ;
	else res = (int) ( cc - ch1 ) + 1 ;
	if( (size_t) res > strlen( ch ) ) res = 0 ;
	free( ch1 ) ;
	return res ;
	}

/* Fonction permettant de retrouver la position d'une chaine dans une autre sans regarder la casse */
int mpos( const char * c, const char * ch ) {
	int res = 0 ;
	char * c1, * c2 ;
	if( ( c == NULL ) || ( ch == NULL ) ) return -1 ;
	if( ( strlen( c ) == 0 ) || ( strlen( ch ) == 0 ) ) return 0 ;
	if( ( c1 = (char *) malloc( strlen( c ) + 1 ) ) == NULL ) return -2 ;
	if( ( c2 = (char *) malloc( strlen( ch ) + 1 ) ) == NULL ) { free( c1 ) ; return -3 ; }
	strcpy( c1, c ) ; strcpy( c2, ch ) ;
	majuscule( (signed char*) c1 ) ; majuscule( (signed char*) c2 ) ;
	res = pos( c1, c2 ) ;
	if( (size_t) res > strlen( ch ) ) res = 0 ;
	free( c2 ) ;
	free( c1 ) ;
	return res ;
	}

/* Procédure permettant de tester l'infériorité de deux chaînes de caractères */
int strinf( const char * a, const char * b ) {
	int lena ;
	int lenb ;
	int lenmin, i ;
	int test ;
	
	if( a == NULL ) return 1 ;
	if( b == NULL ) return 0 ;
	if( strlen( a ) == 0 ) return 1 ;
	if( strlen( b ) == 0 ) return 0 ;

	lena = strlen( a ) ;
	lenb = strlen( b ) ;
	
	if( lena < lenb ) lenmin = lena ; else lenmin = lenb ;
	
	test = 1 ;
	i = 0 ;
	while( i < lenmin ) {
		if( a[i] > b[i] ) { test = 0 ; i = lenmin + 1 ; }
		if( a[i] < b[i] ) { break ; }
		i++ ;
		}
	
	if( (test == true) && ( i == lenmin ) ) {
		if( lena > lenb ) test = 0 ;
		}
	
	return test ;
	}

char * delnew( const char * ch, const int i, const int j ) {
	char * ch1, * ch2 ;
	int ii ;
	if( ch == NULL ) return NULL ;
	if( ( ch1 = (char *) malloc( strlen( ch ) + 1 ) ) == NULL ) return NULL ;
	strcpy( ch1, ch ) ;
	ii = del( ch1, i, j ) ;
	if( ii < 0 ) { free( ch1 ) ; return NULL ; }
	if( ( ch2 = (char *) malloc( strlen( ch1 ) + 1 ) ) == NULL ) { free( ch1 ) ; return NULL ; }
	strcpy( ch2, ch1 ) ;
	free(ch1) ;
	return ch2 ; 
	}

/* Fonction permettant de supprimer une partie d'une chaine de caracteres */
int del( char * ch, const int start, const int length ) {
	int k, len = strlen( ch ) ;
	if( ch == NULL ) return -1 ;
	if( ( start == 1 ) && ( length >= len ) ) { ch[0] = '\0' ; len = 0 ; }
	if( ( start > 0 ) && ( start <= len ) && ( length > 0 ) ) {
		for( k = start - 1 ; k < ( len - length ) ; k++ ) {
			if( k < ( len - length ) ) ch[k] = ch[ k + length ] ;
			else ch = '\0' ; 
			}
		k = len - length ;
		if( ( start + length ) > len ) k = start - 1 ;
		ch[k] = '\0' ; 
		}
	return strlen( ch ) ; 
	}

char * insertnew( const char * ch, const char * c, const int ipos ) {
	int res ;
	char * ch1 ;
	if( ( c == NULL ) || ( ch == NULL ) ) return NULL ;
	if( ( ch1 = (char *) malloc( strlen( ch ) + strlen( c ) + 1 ) ) == NULL ) return NULL ;
	strcpy( ch1, ch ) ;
	res = insert( ch1, c, ipos ) ;
	if( res < 0 ) return NULL ;
	return ch1 ; 
	}

/* Fonction permettant d'inserer une chaine dans une autre */
int insert( char * ch, const char * c, const int ipos ) {
	int i = ipos, len = strlen( c ), k ;
	if( ( ch == NULL ) || ( c == NULL ) ) return -1 ;
	if( len > 0 ) {
		if( (size_t) i > ( strlen( ch ) + 1 ) ) i = strlen( ch ) + 1 ;
		for( k = strlen( ch ) ; k >= ( i - 1 ) ; k-- ) ch[k + len] = ch[k] ;
		for( k = 0 ; k < len ; k++ ) ch[k + i - 1] = c[k] ; 
		}
	return strlen( ch ) ; 
	}

/* Fonction permettant de remplacer un caractere par un autre dans toute une chaine */
int replacec( char * ch, const char c1, const char c2 ) {
	int i, nb = 0 ;
	if( c1 == c2 ) return 0 ;
	while( ( i = posc( c1, ch ) ) > 0 ) { ch[ i - 1 ] = c2 ; nb++ ; }
	return nb ;
	}
int remplacec( char * ch, const char c1, const char c2 ) {
	return replacec( ch, c1, c2 ) ;
	}
	
/* Fonction permettant de remplacer une chaine par une autre dans toute une chaine */
int replace( char * ch, const char * c1, const char * c2 ) {
	int i, nb = 0 ;
	if( !strcmp( c1, c2 ) ) return 0 ;
	while( ( i = pos( c1, ch ) ) > 0 ) {
		if( del( ch, i, strlen( c1 ) ) < 0 ) { nb = -1 ; }
		if( insert( ch, c2, i ) < 0 ) { nb =-2 ; }
		if( nb >= 0 ) { nb++ ; }
		}
	return nb ;
	}
int remplace( char * ch, const char * c1, const char * c2 ) {
	return replace( ch, c1, c2 ) ;
	}

char __bufferchar[35] = "" ;
char * itos( const int i ) {
	sprintf( __bufferchar, "%d", i ) ; 
	return __bufferchar ; 
	}

/* Procedure permettant de verifier si une chaine match avec un pattern acceptant les caracteres jocker * et les ? */
int matchpattern( const char * pattern, const char * st) {
	unsigned int i = 0, j = 0 , k ;

	if( pattern == NULL ) return 1 ;
	if( strlen( pattern ) == 0 ) return 1 ;
	if( st == NULL ) return 0 ;
	if( strlen( st ) == 0 ) return 0 ;
	
	do {
		if( pattern[j] == '*' ) { /* cas où on a une etoile */
			if( j == ( strlen( pattern ) - 1 ) ) return 1 ; /* Etoile en fin */
			for( k=(strlen( st )-1) ; k >= i ; k-- ) {
				if( st[k]==pattern[j+1] ) {
					if( matchpattern( pattern+j+1, st+k ) ) return 1 ;
						}
					if( k == 0 ) return 0 ;
					}
			return 0 ;
			}
		if( pattern[j] != '*' ) { /* cas où il n'y a pas d'étoile */
			if( (st[i]!=pattern[j]) && (pattern[j]!='?') ) return 0;
			i++ ; 
			j++ ;
			}
		}
	while ( ( i <= strlen( st ) ) && ( j <= strlen( pattern ) ) ) ;

	return 1 ;
	}

/* strscan - scanner de chaine de caracteres
	permet de rechercher dans une chaine de caracteres st les différents parametres de 
	type char* separes par le(s) caractere(s) sep
*/
int strscan( const char * st, const char * sep, ... ) {
	char * pst ;
	int nb = 0, i = 0, j = 0 ;
	va_list ap ;
	
	if( st == NULL ) return 0 ;
	if( strlen( st ) == 0 ) return 0 ;
	
	va_start( ap, sep ) ;
	if( ( pst = va_arg( ap, char* ) ) == NULL ) return 0 ;

	if( (sep == NULL) || ( strlen(sep) == 0 ) ) {
		strcpy( pst, st ) ;
		return 1 ;
		}
	else {pst[0]='\0' ; nb++; }

	while( (pst != NULL ) && ( st[i]!='\0' ) ) {
		while( strstr( st+i, sep ) == ( st + i ) ) {
			pst[j] = '\0' ;
			if( ( pst = va_arg( ap, char* ) ) == NULL ) return nb ;
			pst[0]='\0' ;
			j = 0 ;
			i = i + strlen( sep ) ;
			nb++ ;
			}
		pst[j] = st[i] ; 
		pst[j+1]='\0' ;
		i++ ;
		j++ ;
		}
	pst[j]='\0' ;
	
	va_end( ap ) ;	
	return nb ;	
	}

/* rpad - ajout le motif à droite jusqu'à obtenir une longueur totale de n */
int rpad( char * st, const unsigned int len, const char motif ) {
	if( st == NULL ) return 0 ;
	while( strlen( st ) < len ) {
		st[strlen(st)+1] = '\0' ;
		st[strlen(st)] = motif ;
		}
	return strlen( st ) ;
	}

/* drpad - ajout des espace à droite jusqu'à obtenir une longueur totale de n */
int drpad( char * st, const unsigned int len ) { return rpad( st, len, ' ' ) ; }

/* lpad - ajout le motif à gauche jusqu'à obtenir une longueur totale de n */
int lpad( char * st, const unsigned int len, const char motif ) {
	char b[2] ;
	if( st == NULL ) return 0 ;
	b[0] = motif ; b[1] = '\0' ;
	while( strlen( st ) < len ) {
		insert( st, b, 1 ) ;
		}
	return strlen( st ) ;
	}

/* dlpad - ajout des espace à gauche jusqu'à obtenir une longueur totale de n */
int dlpad( char * st, const int len ) { return lpad( st, len, ' ' ) ; }

/* rtrim - supprime à droite les caractères de la chaine motif */
int rtrim( char * st, const char * motif ) {
	if( st == NULL ) return 0 ;
	if( motif == NULL ) return strlen( st ) ;
	if( strlen(motif) == 0 ) return strlen( st ) ;
	
	while( posc( st[strlen(st)-1], motif ) ) st[strlen(st)-1] = '\0' ;
	return strlen( st ) ;
	}

/* drtrim - supprime à droite les espaces tabulation et retour chariot */
int drtrim( char * st ) { return rtrim( st, " \t\r\n" ) ; }

/* ltrim - supprime à gauche les caractères de la chaine motif */
int ltrim( char * st, const char * motif ) {
	if( st == NULL ) return 0 ;
	if( motif == NULL ) return strlen( st ) ;
	if( strlen(motif) == 0 ) return strlen( st ) ;
	
	while( posc( st[0], motif ) ) del( st, 1, 1 ) ;
	return strlen( st ) ;
	}

/* dltrim - supprime à gauche les espaces tabulation et retour chariot */
int dltrim( char * st ) { return ltrim( st, " \t\r\n" ) ; }

/* trim - supprime à gauche et à droite les caractères de la chaine motif */
int trim( char * st, const char * motif ) { rtrim( st, motif ) ; return ltrim( st, motif ) ; }

/* dtrim - supprime à gauche et à droite les espaces tabulation et retour chariot */
int dtrim( char * st ) { rtrim( st, " \t\r\n" ) ; return ltrim( st, " \t\r\n" ) ; }

/**************************************************************************
		FONCTIONS DE GESTION DE LA LIGNE DE COMMANDE
**************************************************************************/
/* Fonction permettant de recuperer un argument de la ligne de commande et de le mettre dans la variable buf */
int scanparam( char * st, int * argc1, char ** argv, char * buf ) {
	/* st: la chaine recherchee
        ATTENTION aux pointeurs
        Exemple d'appel: scanparam("-r",&argc,argv,buf);
        */
        
        int i, res = 1, pos = 1 ;
        int argc = *argc1 ;
        if( ( *argc1 <= 1 ) || ( argv == NULL ) || ( buf == NULL ) ) return -1 ;
        for( i = 1 ; i < argc ; i++ ) {
        	if( ( !strcmp( argv[i], st ) ) && ( i < ( argc -1 ) ) ) 
        		{ res = 0 ; pos = i ; }
        	}
        if( res == 0 ) {
        	strcpy( buf, argv[pos + 1] ) ;
        	free( argv[pos] ) ; free( argv[pos + 1] ) ;
                if( pos < ( argc - 2 ) ) {
                        for( i = pos ; i < ( argc - 2 ) ; i++ )
				{ argv[i] = argv[i+2] ; }
                        }
                ( *argc1 ) = argc - 2 ;
                }

        return res ;
        }

/* Fonction permettant de recuperer un flag de la ligne de commande*/
int scanparam1( char * st, int * argc1, char ** argv ) {
        /* st: la chaine recherchee
        ATTENTION aux pointeurs
        Exemple d'appel: scanparam("-r",&argc,argv);
	Le code retour vaut zero si la valeur est trouvée
        */

        int i, res = 1 , pos = 1 ;
        int argc = *argc1 ;
        if( ( *argc1 <= 1 ) || ( argv == NULL ) ) return -1 ;
        for( i = 1 ; i < argc ; i++ )
                { if( !strcmp( argv[i], st ) ) { res = 0 ; pos =i ; } }
        if( res == 0 ) {
                free( argv[pos] ) ;
                if( pos < ( argc - 1 ) ) {
                        for( i = pos ; i < ( argc - 1 ) ; i++ )
				{ argv[i] = argv[i + 1] ; }
                        }
                ( *argc1 ) = argc - 1 ;
                }

        return res ;
        }

/* Définition du tableau interne de gestion de la ligne de commande */
static int __tools_argc = 0 ;
static char ** __tools_argv = NULL ;

/* Copie la ligne de commande dans un tableau interne */
int param_init( const int argc, const char **argv ) {
	int i ;
	if( argc > 0 ) {
		if( __tools_argv != NULL ) { param_clean() ; __tools_argc = 0 ; }
		if( ( __tools_argv = (char**) malloc( argc*sizeof(char*) ) ) == NULL ) return 0 ;
		__tools_argc = argc ;
		for( i = 0 ; i < argc ; i++ ) {
			if( ( __tools_argv[i] = (char*)malloc( strlen( argv[i] ) + 1 ) ) == NULL ) return 0 ;
			strcpy( __tools_argv[i], argv[i] ) ;
			}
		}
	return 1 ;
	}
	
/* Donne le nombre d'arguments restant */
int param_nbr( void ) {
	return __tools_argc ;
	}

/* Renvoie le tableau de paramètres restants */
char ** param_tab( void ) {
	return __tools_argv ;
	}

/* Test l'existance d'un flag et le supprime */
int param_scan1( const char * val ) {
	int i, j ;
	if( __tools_argv != NULL ) 
	if( __tools_argc > 0 ) {
		for( i = 0 ; i < __tools_argc ; i++ ) 
			if( __tools_argv[i] != NULL )
			if( !strcmp( __tools_argv[i], val ) ) {
				free( __tools_argv[i] ) ;
				__tools_argv[i] = NULL ;
				if( i < (__tools_argc-1) ) {
					for( j = i ; j < (__tools_argc-1) ; j++ ) {
						__tools_argv[j] = (char*)malloc( strlen(__tools_argv[j+1]) + 1 ) ;
						strcpy( __tools_argv[j], __tools_argv[j+1] ) ;
						free( __tools_argv[j+1] ) ; 
						__tools_argv[j+1] = NULL ;
						/* __tools_argv[j] = __tools_argv[j+1] ; */
						}
					} 
				/* __tools_argv[ __tools_argc-1 ] = NULL ; */
				__tools_argc-- ;
				return 1 ;
				}
		}
	return 0 ;
	}

/* Test l'existance d'un paramètre et le supprime */
int param_scan( const char * val, char * st ) {
	int i, j ;
	if( __tools_argv != NULL ) 
	if( __tools_argc > 0 ) {
		for( i = 0 ; i < (__tools_argc-1) ; i++ ) 
			if( __tools_argv[i] != NULL )
			if( !strcmp( __tools_argv[i], val ) ) {
				if( __tools_argv[i+1] != NULL ) strcpy( st, __tools_argv[i+1] ) ;
				free( __tools_argv[i] ) ; __tools_argv[i] = NULL ; 
				free( __tools_argv[i+1] ) ; __tools_argv[i+1] = NULL ;
				if( i < (__tools_argc-2) ) {
					for( j = i ; j < (__tools_argc-2) ; j++ ) 
					if( __tools_argv[j+2] != NULL ) {
						__tools_argv[j] = (char*) malloc( strlen(__tools_argv[j+2]) + 1 ) ;
						strcpy( __tools_argv[j], __tools_argv[j+2] ) ;
						free( __tools_argv[j+2] ) ;
						__tools_argv[j+2] = NULL ;
						/* __tools_argv[j] = __tools_argv[j+2] ; */
						}
					} 
				/* __tools_argv[ __tools_argc-1 ] = NULL ; */
				/* __tools_argv[ __tools_argc-2 ] = NULL ; */
				__tools_argc -= 2 ;
				return 1 ;
				}
		}
	return 0 ;
	}
	
/* Récupère le contenu d'un paramètre */
char * param_get( const int nb ) {
	if( nb < 0 ) return NULL ;
	if( nb >= __tools_argc ) return NULL ;
	if( __tools_argv != NULL ) {
		return __tools_argv[nb] ;
		}
	return NULL ;
	}

/* Affiche le buffer interne */
void param_print( void ) {
	int i ;
	if( __tools_argv != NULL ) 
	if( __tools_argc > 0 ) {
		for( i = 0 ; i < __tools_argc ; i++ ) 
			if( __tools_argv[i] != NULL ) {
				printf( "%d: %s\n", i, __tools_argv[i] ) ;
				}
		}
	}

/* Vide le buffer interne */
void param_clean( void ) {
	int i ;
	if( __tools_argv != NULL ) 
	if( __tools_argc > 0 ) {
		for( i = 0 ; i < __tools_argc ; i++ ) 
			if( __tools_argv[i] != NULL ) {
				free( __tools_argv[i] ) ;
				__tools_argv[i] = NULL ;
				}
		free( __tools_argv ) ;
		__tools_argv = NULL ;
		}
	__tools_argc = 0 ;
	}

/**************************************************************************
		FONCTIONS DE GESTION DE DATE
**************************************************************************/
char __TIMEPATTERN[256] = "%A %d %B %Y %j %m %y %b %a %w %W %I%p %X %Z" ; /* Variable a modifier pour redefinir le format d'affichage */
/* Calcul de la date à partir d'aujourd'hui +/- n secondes
'%A'	The full weekday name ('Friday')
'%a'	The abbreviated weekday name ('Fri')
'%B'	The full month name ('October')
'%b'%h'	The abbreviated month name ('Oct')
'%C'	Short for '%a %b %e %H:%M:%S %Y' ('Fri Oct  1 15:30:34 1993')
'%c'	Short for '%m/%d/%y %H:%M:%S' ('10/01/93 15:30:34')
'%e'	The day of the month, blank padded to two characters (' 2')
'%D'	Short for '%m/%d/%y' ('10/01/93')
'%d'	The day of the month, zero padded to two characters ('02')
'%H'	The hour (0-24), zero padded to two characters ('15')
'%I'	The hour (1-12), zero padded to two characters ('03')
'%j'	The Julian day, zero padded to three characters ('275')
'%k'	The hour (0-24), space padded to two characters ('15')
'%l'	The hour (1-12), space padded to two characters(' 3')
'%M'	The minutes, zero padded to two characters ('30')
'%m'	The month (1-12), zero padded to two characters ('10')
'%n'	A newline ('\n')
'%p'	AM or PM ('PM')
'%R'	Short for '%H:%M' ('15:30')
'%r'	Short for '%I:%M:%S %p' ('03:30:35 PM')
'%S'	The seconds, zero padded to two characters ('35')
'%T'%X'	Short for '%H:%M:%S' ('15:30:35')
'%t'	A tab ('\t')
'%U'	The week of the year, with the first week defined by the first Sunday of the year, zero padded to two characters ('39')
'%W'	The week of the year, with the first week defined by the first Monday of the year, zero padded to two characters ('39')
'%w'	The day of the week (0-6) ('5')
'%x'	Short for '%m/%d/%y' ('10/01/93')
'%y'	The year (00-99) of the century ('93')
'%Y'	The year, zero padded to four digits ('1993')
'%Z'	The timezone abbreviation ('EDT')
'%%'	A percent symbol ('%')

struct tm {
  int    tm_sec;     seconds after the minute [0-60] 
  int    tm_min;     minutes after the hour [0-59] 
  int    tm_hour;    hours since midnight [0-23] 
  int    tm_mday;    day of the month [1-31] 
  int    tm_mon;     months since January [0-11] 
  int    tm_year;    years since 1900 
  int    tm_wday;    days since Sunday [0-6] 
  int    tm_yday;    days since January 1 [0-365] 
  int    tm_isdst;   Daylight Savings Time flag 
  long   tm_gmtoff;  offset from GMT in seconds 
  char * tm_zone;    timezone abbreviation 
};*/

int adddate( const int secondes, char * buf ) {
	char * pays = "fr_FR.ISO8859-1" ;
	time_t temps ;
	struct tm date ;
	 	
	setlocale( LC_TIME, pays ) ;
	temps = time( & temps ) ;
	/*temps=temps-(3600*24*jours);*/
	temps = temps - secondes ;
	date = * localtime( & temps ) ;
	/*strftime(buf,255,"%A %d %B %Y %j %m %y",&date);*/
	strftime( buf, 255, __TIMEPATTERN, & date ) ;
	return 0 ;
	}	

/* Fonction permettant d'attendre (seconde avec virgule) */
#ifndef CPPLUS
void mysleep( const double delay ) {
#ifdef WIN32
	/* _sleep( (unsigned long)( 1000. * delay ) ) ; */
	Sleep( (unsigned long)( 1000. * delay ) ) ;
#else
	sleep( (unsigned int) ceil( delay ) ) ;
#endif
	}
#endif


/**************************************************************************
		FONCTIONS MATHEMATIQUES
**************************************************************************/
double sqr( const double f ) {
	return pow( f, 2 ) ;
	}

double myabs( const double dd ) {
	if( dd < 0 ) return -dd ;
	else return dd ;
	}


double mymin( const double f1, const double f2 ) {
	if( f1 <= f2 ) return f1 ;
	else return f2 ;
	}

int mymini( const int f1, const int f2 ) {
	if( f1 <= f2 ) return f1 ;
	else return f2 ;
	}

double mymax( const double f1, const double f2 ) {
	if( f1 >= f2 ) return f1 ;
	else return f2 ;
	}

int mymaxi( const int f1, const int f2 ) {
	if( f1 >= f2 ) return f1 ;
	else return f2 ;
	}

int sgn( const double a ) {
	if( a < 0 ) return -1 ;
	else if( a > 0 ) return 1 ;
	else return 0 ; 
	}


/*********************************************************************************************
		GENERATEUR DE NOMBRES ALEATOIRES
*********************************************************************************************/
int __MYRANDSEED = 0 ; /* Initialisation du generateur de nombre aléatoire */
int __MYCOUNTRAND = 0 ;

void myrandseed( const int myseed ) {
	__MYRANDSEED = myseed ;
	__MYCOUNTRAND= myseed ;
	}

double myrandomd( void ) {
	double dd = 0.5 * ( sin ( (double) __MYCOUNTRAND ) + 1 ) ;
	__MYCOUNTRAND = __MYRANDSEED + __MYCOUNTRAND ;
	dd = 1000 * dd ;
	dd = dd - floor( dd ) ;
	return dd ;
	}

int myrandom( const int num ) {
	return (int) ( floor ( num * myrandomd() ) ) ;
	}

void myrandomize( void ) {
	long int h ;
	h = time( 0L ) ;
	myrandseed( h ) ;
	}

/*********************************************************************************************
		GESTION DES ERREURS ERRNO
*********************************************************************************************/
#ifndef __ERRNO
#define __ERRNO

const int MAX_ERRNO = 139 ;

const struct {
	const char * code ;
	const int value ;
	char * libelle ;
	}
SERRNO[] = 
{
{"NULL",0,""},
{"EPERM",1,"Not super-user"},
{"ENOENT",2,"No such file or directory"},
{"ESRCH",3,"No such process"},
{"EINTR",4,"Interrupted system call"},
{"EIO",5,"I/O error"},
{"ENXIO",6,"No such device or address"},
{"E2BIG",7,"Arg list too long"},
{"ENOEXEC",8,"Exec format error"},
{"EBADF",9,"Bad file number"},
{"ECHILD",10,"No children"},
{"EAGAIN",11,"No more processes"},
{"ENOMEM",12,"Not enough core"},
{"EACCES",13,"Permission denied"},
{"EFAULT",14,"Bad address"},
{"ENOTBLK",15,"Block device required"},
{"EBUSY",16,"Mount device busy"},
{"EEXIST",17,"File exists"},
{"EXDEV",18,"Cross-device link"},
{"ENODEV",19,"No such device"},
{"ENOTDIR",20,"Not a directory"},
{"EISDIR",21,"Is a directory"},
{"EINVAL",22,"Invalid argument"},
{"ENFILE",23,"Too many open files in system"},
{"EMFILE",24,"Too many open files"},
{"ENOTTY",25,"Not a typewriter"},
{"ETXTBSY",26,"Text file busy"},
{"EFBIG",27,"File too large"},
{"ENOSPC",28,"No space left on device"},
{"ESPIPE",29,"Illegal seek"},
{"EROFS",30,"Read only file system"},
{"EMLINK",31,"Too many links"},
{"EPIPE",32,"Broken pipe"},
{"EDOM",33,"Math arg out of domain of func"},
{"ERANGE",34,"Math result not representable"},
{"ENOMSG",35,"No message of desired type"},
{"EIDRM",36,"Identifier removed"},
{"ECHRNG",37,"Channel number out of range"},
{"EL2NSYNC",38,"Level 2 not synchronized"},
{"EL3HLT",39,"Level 3 halted"},
{"EL3RST",40,"Level 3 reset"},
{"ELNRNG",41,"Link number out of range"},
{"EUNATCH",42,"Protocol driver not attached"},
{"ENOCSI",43,"No CSI structure available"},
{"EL2HLT",44,"Level 2 halted"},
{"EDEADLK",45,"Deadlock condition"},
{"ENOLCK",46,"No record locks available"},
{"NULL",47,""},
{"NULL",48,""},
{"NULL",49,""},
{"EBADE",50,"Invalid exchange"},
{"EBADR",51,"Invalid request descriptor"},
{"EXFULL",52,"Exchange full"},
{"ENOANO",53,"No anode"},
{"EBADRQC",54,"Invalid request code"},
{"EBADSLT",55,"Invalid slot"},
{"EDEADLOCK",56,"File locking deadlock error"},
{"EBFONT",57,"Bad font file fmt"},
{"NULL",58,""},
{"NULL",59,""},
{"ENOSTR",60,"Device not a stream"},
{"ENODATA",61,"No data (for no delay io)"},
{"ETIME",62,"Timer expired"},
{"ENOSR",63,"Out of streams resources"},
{"ENONET",64,"Machine is not on the network"},
{"ENOPKG",65,"Package not installed"},
{"EREMOTE",66,"The object is remote"},
{"ENOLINK",67,"The link has been severed"},
{"EADV",68,"Advertise error"},
{"ESRMNT",69,"Srmount error"},
{"ECOMM",70,"Communication error on send"},
{"EPROTO",71,"Protocol error"},
{"NULL",72,""},
{"NULL",73,""},
{"EMULTIHOP",74,"Multihop attempted"},
{"ELBIN",75,"Inode is remote (not really error)"},
{"EDOTDOT",76,"Cross mount point (not really error)"},
{"EBADMSG",77,"Trying to read unreadable message"},
{"NULL",78,""},
{"EFTYPE",79,"Inappropriate file type or format"},
{"ENOTUNIQ",80,"Given log. name not unique"},
{"EBADFD",81,"f.d. invalid for this operation"},
{"EREMCHG",82,"Remote address changed"},
{"ELIBACC",83,"Can\"t access a needed shared lib"},
{"ELIBBAD",84,"Accessing a corrupted shared lib"},
{"ELIBSCN",85,".lib section in a.out corrupted"},
{"ELIBMAX",86,"Attempting to link in too many libs"},
{"ELIBEXEC",87,"Attempting to exec a shared library"},
{"ENOSYS",88,"Function not implemented"},
{"ENMFILE",89,"No more files"},
{"ENOTEMPTY",90,"Directory not empty"},
{"ENAMETOOLONG",91,"File or path name too long"},
{"ELOOP",92,"Too many symbolic links"},
{"NULL",93,""},
{"NULL",94,""},
{"EOPNOTSUPP",95,"Operation not supported on transport endpoint"},
{"EPFNOSUPPORT",96,"Protocol family not supported"},
{"NULL",97,""},
{"NULL",98,""},
{"NULL",99,""},
{"NULL",100,""},
{"NULL",101,""},
{"NULL",102,""},
{"NULL",103,""},
{"ECONNRESET",104,"Connection reset by peer"},
{"ENOBUFS",105,"No buffer space available"},
{"EAFNOSUPPORT",106,"Address family not supported by protocol family"},
{"EPROTOTYPE",107,"Protocol wrong type for socket"},
{"ENOTSOCK",108,"Socket operation on non-socket"},
{"ENOPROTOOPT",109,"Protocol not available"},
{"ESHUTDOWN",110,"Can\"t send after socket shutdown"},
{"ECONNREFUSED",111,"Connection refused"},
{"EADDRINUSE",112,"Address already in use"},
{"ECONNABORTED",113,"Connection aborted"},
{"ENETUNREACH",114,"Network is unreachable"},
{"ENETDOWN",115,"Network interface is not configured"},
{"ETIMEDOUT",116,"Connection timed out"},
{"EHOSTDOWN",117,"Host is down"},
{"EHOSTUNREACH",118,"Host is unreachable"},
{"EINPROGRESS",119,"Connection already in progress"},
{"EALREADY",120,"Socket already connected"},
{"EDESTADDRREQ",121,"Destination address required"},
{"EMSGSIZE",122,"Message too long"},
{"EPROTONOSUPPORT",123,"Unknown protocol"},
{"ESOCKTNOSUPPORT",124,"Socket type not supported"},
{"EADDRNOTAVAIL",125,"Address not available"},
{"ENETRESET",126,""},
{"EISCONN",127,"Socket is already connected"},
{"ENOTCONN",128,"Socket is not connected"},
{"ETOOMANYREFS",129,""},
{"EPROCLIM",130,""},
{"EUSERS",131,""},
{"EDQUOT",132,""},
{"ESTALE",133,""},
{"ENOTSUP",134,"Not supported"},
{"ENOMEDIUM",135,"No medium (in tape drive)"},
{"ENOSHARE",136,"No such host or network path"},
{"ECASECLASH",137,"Filename exists with different case"},
{"EILSEQ",138,""},
{"EOVERFLOW",139,"Value too large for defined data type"},
{"EWOULDBLOCK",11,"Operation would block"},
{"__ELASTERROR",2000,"Users can add values starting here"}
} ;

/* Fonction permettant de retrouver le libellé d'une erreur a partir de la valeur errno */
char *sterrno( const int value ) {
	if( ( value < 0 ) || ( value > MAX_ERRNO ) ) return NULL ;
	return SERRNO[value].libelle ;
	}
	
/* Fonction permettant de retrouver le libellé d'une erreur a partir du code errno */
char *ssterrno( const char * code ) {
	int i ;
	for( i = 0 ; i <= MAX_ERRNO ; i++ ) 
		if( !strcmp( code, SERRNO[i].code ) ) return sterrno( i ) ;
	return NULL ;
	}
#endif

/*********************************************************************************************
		PARTIE ACCES AUX FICHIERS
*********************************************************************************************/
/* Teste l'existance d'un fichier */
int existfile( const char * filename ) {
	struct stat statBuf ;
	
	if( filename == NULL ) return 0 ;
	if( stat( filename, &statBuf ) == -1 ) return 0 ;
	
	if( ( statBuf.st_mode & S_IFMT ) == S_IFREG ) { return 1 ; }
	else { return 0 ; }
	}

/* Teste l'existance d'un repertoire */
int existdir( const char * name ) {
	struct stat statBuf ;
	char * dirname ;
	
	if( name == NULL ) return 0 ;
	dirname = (char*) malloc( strlen( name ) + 4 ) ;
	strcpy( dirname, name ) ;
	while( (dirname[strlen(dirname)-1]=='/')||(dirname[strlen(dirname)-1]=='\\') ) dirname[strlen(dirname)-1]='\0' ;
	if( stat( dirname, &statBuf ) == -1 ) { 
		strcat( dirname, "/." ) ;
		if( stat( dirname, &statBuf ) == -1 ) { free( dirname ) ; return 0 ; }
		}
	
	if( ( statBuf.st_mode & S_IFMT) == S_IFDIR ) { free( dirname ) ; return 1 ; }
	else { free( dirname ) ; return 0 ; }
	}

/* Teste l'existance d'un lien symbolique */
int existlink( const char * linkname ) {
	struct stat statBuf ;
	
	if( linkname == NULL ) return 0 ;
	if( stat( linkname, &statBuf ) == -1 ) return 0 ;
	
	if( ( statBuf.st_mode & S_IFMT) == S_IFDIR ) { return 1 ; }
	else { return 0 ; }
	}

/* Teste l'existance d'un fichier ou d'un repertoire ou d'un lien symbolique */
int exist( const char * name ) {
	return ( existfile( name ) || existdir( name ) || existlink( name ) ) ;
	}

/* Donne la taille d'un fichier */
long filesize( const char * filename ) {
	FILE * fp ;
	long length ;

	if( filename == NULL ) return 0 ;
	if( strlen( filename ) <= 0 ) return 0 ;
	
	if( ( fp = fopen( filename, "r" ) ) == 0 ) return 0 ;
	
	fseek( fp, 0L, SEEK_END ) ;
	length = ftell( fp ) ;
	
	fclose( fp ) ;
	return length ;
	}

/* Supprime toute une arborescence */
int rmalldir( const char * name ) {
	int return_code = 0 ;
	DIR * dir ;
	struct dirent * de ;
	char * buffer ;
	
	if( existfile( name ) ) { if( unlink( name )==0 ) return 1 ; else return 0 ; }
	if( existdir( name ) ) {
		if( ( dir = opendir( name ) ) == NULL ) return 0 ;
		while( ( de = readdir( dir ) ) != NULL ) 
			if( strcmp( de->d_name, "." ) && strcmp( de->d_name, ".." ) ) {
				if( ( buffer = (char*) malloc( strlen(name)+strlen(de->d_name) + 3 ) ) == NULL ) {
						closedir( dir ) ; return 0 ; }
				if( name[ strlen( name ) - 1 ] == '/' ) sprintf( buffer,"%s%s", name, de->d_name );
				else sprintf( buffer,"%s/%s", name, de->d_name ) ;
				if( existdir( buffer ) ) return_code += rmalldir( buffer ) ;
				else {
					if( unlink( buffer )==0 ) return_code++ ;
					else { chmod( buffer, 400 ) ; if( unlink( buffer )==0 ) return_code++ ; }
					}
				free( buffer ) ;
				}
		if( rmdir( name ) == 0 ) return_code++ ;
		else { chmod( name, 400 ) ; if( rmdir( name ) == 0 ) return_code++ ; }
		closedir( dir ) ;
		}
	return return_code ;
	}
/* Recupere la date de derniere modification d'un fichier */
LINKDLL time_t filetime( const char * name ) {
	struct stat statBuf ;
	
	if( stat( name, &statBuf ) == -1 ) return 0 ;
	else return statBuf.st_mtime ;
	}

/* Récupère le répertoire dans un chemin, "" si vide */
/*LINKDLL void dirname( const char * path, char * dir ) {
	int i ;
	if( existdir( path ) ) { strcpy( dir, path ) ; return ; }
	if( ( i = posnc( '/', path ) ) == 0 ) i = posnc( '\\', path ) ;
	if( i > 0 ) {
		strcpy( dir, path ) ;
		dir[i-1] = '\0' ;
		}
	else strcpy( dir, "" ) ;
	}	
*/

#ifndef PERSOPORT
/* Récupère le nom de fichier dans un chemin, "" si vide */
LINKDLL void basename( const char * path, char * base ) {
	int i ;
	strcpy( base, path ) ;
	if( existdir( base ) ) { strcpy( base, "" ) ; return ; }
	/* if( ( i = posnc( '/', path ) ) == 0 ) i = posnc( '\\', path ) ; */
	i = ( posnc( '/', path )>=posnc( '\\', path ) ? posnc( '/', path ) : posnc( '\\', path ) ) ;
	if( i > 0 ) {
		del( base, 1, i ) ;
		}
	}
#endif

/* Procedure d'encodage des parametes d'une URL ( ' ' -> '+', et ? -> %XX ) */
void URLencode( char * st ) {
	size_t i ; 
	int c ;
	char * h = "0123456789abcdef" ;

	if( strlen( st ) <= 0 ) return ;
	for( i = 0 ; i < strlen( st ); i++ ) {
		c = st[i] ;
	
		if( ( ( 'a' <= c ) && ( c <= 'z' ) )
		|| ( ( 'A' <= c ) && ( c <= 'Z' ) )
		|| ( ( '0' <= c ) && ( c <= '9' ) )
		/* || ( c == '-' ) || ( c == '_' ) || ( c == '.' ) */
		/* || ( c == '&' ) || ( c == '=' ) */
		)
			continue ;
		else if( c == ' ' )
			st[i] = '+' ;
		else {
			del( st, i + 1, 1 ) ;
			insert( st, "   ", i + 1 ) ;
			st[i] = '%' ;
			st[i + 1] = h[c >> 4] ;
			st[i + 2] = h[c & 0x0f] ;
			i += 2 ;
			}
		}	
	}

void URLencodeFilename( char * st ) {
	size_t i ;
	int c ;
	char * h = "0123456789abcdef" ;

	if( strlen( st ) <= 0 ) return ;
	for( i = 0 ; i < strlen( st ) ; i++ ) {
		c = st[i] ;
	
		if( ( ( 'a' <= c ) && ( c <= 'z' ) )
		|| ( ( 'A' <= c ) && ( c <= 'Z' ) )
		|| ( ( '0' <= c ) && ( c <= '9' ) )
		/* || ( c == '-' ) || ( c == '_' ) || ( c == '.' )  */
		)
			continue ;
		else {
			del( st, i + 1, 1 ) ;
			insert( st, "   ", i + 1 ) ;
			st[i] = '%' ;
			st[i + 1] = h[c >> 4] ;
			st[i + 2] = h[c & 0x0f] ;
			i += 2 ;
			}
		}	
	}

void URLdecode( char * st ) {
	size_t i ;
	char c, c1, c2 ;

	if( strlen( st ) <= 0 ) return ;
	for( i = 0 ; i < strlen( st ) ; i++ ) {
		c = st[i] ;
		if( c == '%' ){
			c1 = st[i+1] ;
			c2 = st[i+2] ;
			if( c1 == EOF || c2 == EOF )  return ;
			c1 = tolower( c1 ) ;
			c2 = tolower( c2 ) ;
			if( !isxdigit( c1 ) || !isxdigit( c2 ) ) return ;
			if( c1 <= '9' )
				c1 = c1 - '0' ;
			else
				c1 = c1 - 'a' + 10 ;
			if( c2 <= '9' )
				c2 = c2 - '0' ;
			else
				c2 = c2 - 'a' + 10 ;
			del( st, i + 2, 2) ;
			st[i] = 16 * c1 + c2 ;
			} 
		else if( c == '+' )
			st[i] = ' ' ;
		}
	}

int URLread( const char * URL, char * protocol, char * user, char * password, char * adress, char * port, char * path, char * name, char * param ) {
	/*  Format: protocol://user:password@adress:port/path/filename?param */
	int i, j ;
	char * buf ; 
	
	buf = (char*) malloc( strlen( URL ) + 1 ) ;
	
	strcpy( buf, URL ) ; strcpy( protocol, "") ; strcpy (user, "" ) ; strcpy( password, "" ) ;
	strcpy( adress, "" ) ; strcpy( port, "" ) ; strcpy( path, "" ) ; strcpy( name, "" ) ; strcpy( param, "" ) ;

	while( ( buf[ strlen( buf ) - 1 ] == ' ' ) || ( buf[ strlen( buf ) - 1 ] == '\r' ) || ( buf[ strlen( buf ) - 1 ] == '\n' ) || ( buf[ strlen( buf ) - 1 ] == '\t' ) ) buf[ strlen( buf ) - 1 ] = '\0' ;
	while( ( buf[0] == ' ' ) || ( buf[0] == '\t' ) ) del( buf, 1, 1 ) ;

	if( ( i = pos( "?", buf ) ) > 0 ) {
		strcpy( param, buf + i ) ;
		buf[i-1] = '\0' ;
		}	

	if( ( i = pos( "://", buf ) ) > 0 ) {
		copy( protocol, buf, 1, i - 1 ) ;
		del( buf, 1, i + 2 ) ;
		}
	if( ( i = pos( "@", buf ) ) > 0 ) {
		if( ( j = pos( ":", buf ) ) > i ) { free( buf ) ; return -2 ; }
		copy( user, buf, 1, j - 1) ;
		copy( password, buf,  j + 1, i - j - 1 ) ;
		del( buf, 1, i ) ;
		}
	if( ( i = pos( ":", buf ) ) > 0 ) {
		if( ( j = pos( "/", buf ) ) < i ) j = strlen( buf ) + 1 ;
		copy( adress, buf, 1, i - 1 ) ;
		copy( port, buf, i + 1, j - i - 1 ) ;
		del( buf, 1 , j ) ;
		}
	else {
		if( ( i = pos( "/", buf ) ) <= 0 ) { strcpy( adress, buf ) ; free( buf ) ; return 0 ; }
		copy( adress, buf, 1, i - 1 ) ;
		del( buf, 1, i ) ;
		}

	if( ( i = posn( "/", buf ) ) > 0 ) {
		copy( path, buf, 1, i - 1 ) ;
		del( buf, 1, i ) ;
		}
	strcpy( name, buf ) ;	

	if( strcmp( path, "" ) ) {
		if( path[ strlen( path ) - 1 ] != '/' ) strcat( path, "/" ) ;	
		j = 1 ;
		while( ( i = posi( "/", path, j ) ) > 0 ) {
			copy( buf, path, j, i - j ) ;
			URLencodeFilename( buf ) ;
			del( path, j, i - j ) ;
			insert( path, buf, j ) ;
			j = i + 1 ;
			}
		if( path[ strlen( path ) - 1 ] == '/' ) path[ strlen( path ) - 1 ] = '\0' ;
		}
		
	URLencodeFilename( name ) ;
	URLencode( param ) ;
	
	free( buf ) ;
	return 0 ;		
	}

/* Partie spécifique au C++ */
#ifdef CPPLUS		

/* Fonction permettant de concatener un caractere a la fin d'une chaine de caracteres */
char * strcat( char *st, const char c ) {
	char cc[2] ;
	cc[0] = c ;
	cc[1] = '\0' ;
	strcat( st, cc ) ;
	return st ;
	}

/* Fonction permettant de retrouver le position d'un caractere dans une chaine */
int pos( const char c, const char * ch ) {
	char * ch1, * cc ;
	int res ;
	if( ch == NULL ) return -1 ;
	if( ( ch1 = (char *) malloc( strlen( ch ) + 1 ) ) == NULL ) return -2 ;
	strcpy( ch1, ch ) ;
	cc = (char *) strchr( ch1, c ) ;
	if( cc == NULL ) res = 0 ;
	else res = (int) ( cc - ch1 ) + 1 ;
	free( ch1 ) ;
	return res ; 
	}

/* Fonction permettant de retrouver la position d'un caractere dans une chaine en partant de la fin */
int posn( const char c, const char * ch ) {
	char * ch1, * cc ;
	int res ;
	if( ch == NULL ) return -1 ;
	if( ( ch1 = (char *) malloc( strlen( ch ) + 1 ) ) == NULL ) return -2 ;
	strcpy( ch1, ch ) ;
	cc = (char *) strrchr( ch1, c ) ;
	if( cc == NULL ) res = 0 ;
	else res = (int) ( cc - ch1 ) + 1 ;
	free( ch1 ) ;
	return res ;
	}

/* Fonction permettant de remplacer un caractere par un autre dans toute une chaine */
int remplace( char * ch, const char c1, const char c2 ) {
	int i, nb = 0 ;
	while( ( i = posc( c1, ch ) ) > 0 ) { ch[i-1] = c2 ; nb++ ; }
	return nb ;
	}

/*********************************************************************************************
		CLASSE T-WEB
*********************************************************************************************/
TWeb::TWeb() {lcmd=NULL;meth=NULL;}

TWeb::~TWeb() 
	{if(lcmd!=NULL) free(lcmd);
	 if(meth!=NULL) free(meth);
	}

int TWeb::readcmd()
	{
	char * st;
	st=::getenv("REQUEST_METHOD");
	if(st==NULL) return -1;
	if(meth!=NULL) free(meth);
	meth=(char *)malloc(strlen(st)+2);
	if(meth==NULL) return -2;
	strcpy(meth,st);
	majuscule(meth);
	if(!strcmp(meth,"GET")) return readget();
	if(!strcmp(meth,"POST")) return readpost();
	return -3;
	}

int TWeb::readget()
	{
	char * st;
	st=::getenv("QUERY_STRING");
	if(st==NULL) return -1;
	if(lcmd!=NULL) free(lcmd);
	lcmd=(char *)malloc(strlen(st)+2);
	if(lcmd==NULL) return -2;
	strcpy(lcmd,st);
	return strlen(lcmd);
	}

int TWeb::readpost()
	{
	char * st;
	int nb;
	st=::getenv("CONTENT_LENGTH");
	if(st==NULL) return -1;
	nb=atoi(st);
	if(lcmd!=NULL) free(lcmd);
	lcmd=(char *)malloc(nb+3);
	if(lcmd==NULL) return -2;
	fgets(lcmd,nb+1,stdin);
	return strlen(lcmd);
	}

int TWeb::getcmdlen() {return strlen(lcmd);}

int TWeb::getcmd(char st[]) {strcpy(st,lcmd);decode(st);return strlen(st);}

int TWeb::getarg(char arg[], char st[])
	{
	int n;
	char * st2, * arg2;
	arg2=(char *)malloc(strlen(arg)+3);
	if(arg2==NULL) return -2;
	strcpy(arg2,arg);strcat(arg2,"=");
	n=mpos(arg2,lcmd);
	if(n<=0) {strcpy(st,"");return -1;}
	st2=(char *)malloc(strlen(lcmd)-n+2);
	if(st2==NULL) return -2;
	copy(st2,lcmd,n+strlen(arg2),strlen(lcmd)-(n+strlen(arg)));
	n=posc('&',st2);
	if(n<=0) n=strlen(st2)+1;
	if(n>1) copy(st,st2,1,n-1);
	else strcpy(st,"");
	free(arg2);
	free(st2);
	decode(st);
	return strlen(st);
	}

int calchexadec(char st[])
	{
	char ch1,ch2;
	int i=0;
	majuscule(st);
	ch1=st[0];ch2=st[1];
	if((ch1>='A') && (ch1<='F')) i=16*(ch1-55);
	else i=16*(ch1-48);
	if((ch2>='A') && (ch2<='F')) i=i+(ch2-55);
	else i=i+(ch2-48);
	return i;
	}

void TWeb::decode(char st[])
	{
	int n,m;
	char st2[10], ch;	

	while((n=posc('+',st))>0) {st[n-1]=' ';}
	while((n=pos("%0D%0A",st))>0) {del(st,n,6);insert(st,"\n",n);}
	while((n=pos("%09",st))>0) {del(st,n,3);insert(st,"\t",n);}
	while((n=pos("%25",st))>0) {del(st,n,3);insert(st,"¤¤",n);}
	while((n=posc('\%',st))>0) 
		{
		copy(st2,st,n+1,2);
		del(st,n,3);
		m=calchexadec(st2);
		ch=m;
		st2[0]=ch;
		st2[1]='\0';
		insert(st,st2,n);
		}
	while((n=pos("¤¤",st))>0) {del(st,n,2);insert(st,"\%",n);}
	}

void TWeb::contenttype() {/* Envoie de l'entête HTML */printf("Content-type: text/html\n\n");}

void TWeb::write(char st[]) {printf("%s",st);}

void TWeb::writeln(char st[]) {printf("%s<br>\n",st);}

void TWeb::getenv(char env[], char st[]) 
	{char * pst;pst=::getenv(env);if(pst!=NULL) strcpy(st,pst);else strcpy(st,"");}

void TWeb::writeenv()
	{
	char st[5000];
	getenv("SERVER_SOFTWARE",st);printf("<p>SERVEUR_SOFTWARE<br>%s<br></p>\n",st);
	getenv("SERVER_NAME",st);printf("<p>SERVER_NAME<br>%s<br></p>\n",st);
	getenv("GATEWAY_INTERFACE",st);printf("<p>GATEWAY_INTERFACE<br>%s<br></p>\n",st);
	getenv("SERVER_PROTOCOL",st);printf("<p>SERVER_PROTOCOL<br>%s<br></p>\n",st);
	getenv("SERVER_PORT",st);printf("<p>SERVER_PORT<br>%s<br></p>\n",st);
	getenv("REQUEST_METHOD",st);printf("<p>REQUEST_METHOD<br>%s<br></p>\n",st);
	getenv("SCRIPT_NAME",st);printf("<p>SCRIPT_NAME<br>%s<br></p>\n",st);
	getenv("REMOTE_HOST",st);printf("<p>REMOTE_HOST<br>%s<br></p>\n",st);
	getenv("REMOTE_ADDR",st);printf("<p>REMOTE_ADDR<br>%s<br></p>\n",st);
	getenv("AUTH_TYPE",st);printf("<p>AUTH_TYPE<br>%s<br></p>\n",st);
	getenv("REMOTE_USER",st);printf("<p>REMOTE_USER<br>%s<br></p>\n",st);
	getenv("REMOTE_IDENT",st);printf("<p>REMOTE_IDENT<br>%s<br></p>\n",st);
	getenv("CONTENT_LENGTH",st);printf("<p>CONTENT_LENGTH<br>%s<br></p>\n",st);
	getenv("PATH_INFO",st);printf("<p>PATH_INFO<br>%s<br></p>\n",st);
	getenv("QUERY_STRING",st);printf("<p>QUERY_STRING<br>%s<br></p>\n",st);
	getenv("PATH_TRANSLATED",st);printf("<p>PATH_TRANSLATED<br>%s<br></p>\n",st);
	getenv("HTTP_ACCEPT",st);printf("<p>HTTP_ACCEPT<br>%s<br></p>\n",st);
	getenv("HTTP_USER_AGENT",st);printf("<p>HTTP_USER_AGENT<br>%s<br></p>\n",st);
	}


/*********************************************************************************************
		       CLASSE T-FILE
*********************************************************************************************/
TFile::~TFile(void)
	{
	if(vDIR!=NULL) {/*delete[] vDIR;*/free(vDIR);vDIR=NULL;}
	if(vDirent!=NULL) {/*delete[] vDirent;*/free(vDirent);vDirent=NULL;}
	if(maskDIR!=NULL) {/*delete[] maskDIR;*/free(maskDIR);maskDIR=NULL;}
	if(maskFILE!=NULL) {/*delete[] maskFILE;*/free(maskFILE);maskFILE=NULL;}
	}

int TFile::setmask(char * mask, int MAJ)
	{
	int i;
	char stmask[strlen(mask)+2];
	maskMAJ=0;
	while((i=posc('\\',mask))!=0) {mask[i-1]='/';}
	strcpy(stmask,mask);
	if((i=posc(':',stmask))>0) 
		if(stmask[i]!='/') insert(stmask,"/",i+1);
	if(vDIR != NULL) {closedir(vDIR);vDIR=NULL;}
	vDIR=opendir(stmask);
	if(vDIR!=NULL)
		{
		if(maskDIR!=NULL) {/*delete[] maskDIR;*/free(maskDIR);maskDIR=NULL;}
		/*maskDIR=new char[strlen(stmask)+1];*/
		maskDIR=(char*)malloc(strlen(stmask)+1);
		if(maskDIR==NULL) {return 0;}
		strcpy(maskDIR,stmask);
		if(maskFILE!=NULL) {/*delete[] maskFILE;*/free(maskFILE);maskFILE=NULL;}
		/*maskFILE=new char[4];*/
		maskFILE=(char*)malloc(4);
		if(maskFILE==NULL) {return 0;}
		strcpy(maskFILE,"*.*");maskMAJ=MAJ;
		}
	if(vDIR==NULL)
		{
		char st[strlen(mask)+2];
		int i;
		i=posnc('/',mask);if(i<=0) {return 0;}
		copy(st,stmask,1,i);
		vDIR=opendir(st);if(vDIR==NULL) {return 0;}
		if(maskDIR!=NULL) {/*delete[] maskDIR;*/free(maskDIR);maskDIR=NULL;}
		/*maskDIR=new char[strlen(st)+1];*/
		maskDIR=(char*)malloc(strlen(st)+1);
		if(maskDIR==NULL) {return 0;}
		strcpy(maskDIR,st);

		copy(st,stmask,i+1,strlen(stmask)-i);
		if(maskFILE!=NULL) {/*delete[] maskFILE;*/free(maskFILE);maskFILE=NULL;}
		/*maskFILE=new char[strlen(st)+1];*/
		maskFILE=(char*)malloc(strlen(st)+1);
		if(maskFILE==NULL) {return 0;}
		strcpy(maskFILE,st);maskMAJ=MAJ;
		}
	if(maskMAJ==1) majuscule(maskFILE);
	if(maskDIR[strlen(maskDIR)-1]=='/') maskDIR[strlen(maskDIR)-1]='\0' ;
/* printf("#%s#%s#\n",maskDIR,maskFILE); */
	return 1;
	}

int TFile::nextfile(char * stfile)
	{
	bool test=false;

	while(!test)
	{
	vDirent=readdir(vDIR);
	if(vDirent==NULL) {strcpy(stfile,"");return 0;}
	test=testfile(vDirent->d_name);
	}
	strcpy(stfile,vDirent->d_name);
	return 1;
	}

int TFile::prevfile(char * stfile)
	{
	char actualFILE[256],newFILE[256];
	strcpy(actualFILE,vDirent->d_name);
	strcpy(stfile,"");

	rewinddir(vDIR);
	while(nextfile(newFILE)>0)
		{
		if(!strcmp(newFILE,actualFILE)) 
			{if(!strcmp(stfile,"")) {return 0;}
			 else { rewinddir(vDIR);
				do {nextfile(newFILE);} while(!strcmp(newFILE,stfile));
				nextfile(newFILE);
				return 1;}
			}
		else {strcpy(stfile,newFILE);}
		}
	strcpy(stfile,"");
	return 0;
	}

int TFile::dir(void)
	{char stfile[256];
	int i=0;
	while(nextfile(stfile)>0) {printf("%s/%s\n",maskDIR,stfile);i++;};return i;}

int TFile::dir(char * mask)
	{setmask(mask);return dir();}

void TFile::rewind(void)
	{rewinddir(vDIR);}

bool TFile::testfile(char * stfile)
	{
	char nom[256];
	bool test=true;
	int i,j;
	if(!strcmp(maskFILE,"*.*") || !strcmp(maskFILE,"*")) return true;
	if(strlen(stfile)<strlen(maskFILE)) return false;
	i=posnc('\\',stfile);
	if(i<=0) i=posnc(':',stfile);
	if(i<=0) i=1;
	copy(nom,stfile,i,strlen(stfile)-(i-1));
	i=strlen(nom);
	j=strlen(maskFILE);
	if(maskMAJ==1) majuscule(nom);
	while (test && (i>0) && (j>0))
		{

/* printf(" %c %c\n",nom[i-1],maskFILE[j-1]); */

		if(nom[i-1]==maskFILE[j-1]) {i--;j--;}
		else
		   {
		   if(maskFILE[j-1]=='?') 
			{/*if(nom[i-1]==maskFILE[j-2]) {j--;} else */{i--;j--;}}
		   else
			{
			if(maskFILE[j-1]=='*')
			   {if(j==1) {i=0;j=0;}
			    else if(nom[i-1]==maskFILE[j-2]) {j--;} else {i--;}}
			else {test=false;}
			}
		   }
		}
	if(j>0) test=false;
	/* Verifie l'accessibilite au fichier */
	/* if(access(maskFILE,0)!=0) test=false; */
	return test;
	}

void TFile::info(void)
	{
#ifdef CPPLUS
	printf(" ");
#else
	printf("%d %d %d %d  %d\n",vDirent->__d_reserved[0],vDirent->__d_reserved[1],vDirent->__d_reserved[2],vDirent->__d_reserved[3],vDirent->d_ino);
#endif
	}

extern int const TFile::MAJ = 1;

#endif /* Fin de la partie specifique C++ */


/* Fonction MAIN de test de la library */
/*
int main(int argc, char **argv, char **arge)
{

	char buffer[256] , p1[256], p2[256],p3[256];
	
printf( "%d\n", strscan( "/ABC/", "/", p1,p2,p3) ); printf( "#%s#%s#%s#\n",p1,p2,p3 );


#ifdef DEBUG_MODE
	_leaktracker61_EnableReportLeakOnApplication_Exit("tools.leaktracker.log", 1);
	_leaktracker61_DumpAllLeaks("tools.leaktracker.log", 0);
	printf("Leak tracker log in tools.leaktracker.log file\n");
#endif

	return 0;
}
*/


