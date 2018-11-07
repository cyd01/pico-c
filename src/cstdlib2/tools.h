/*****************************************************************************************
   TOOLS C/C++ 
   Copyright (C) 1999, 2000, 2001 Leonard Nero
   Contributed by Lenny
   e-mail lenny.nero@zdnetonebox.com

   This file is part of GNU CC.
   
   Options de compilation
     -DWIN32 : Compilation sous Windows (librairie -lwsock32)
     -DCPPLUS : Compilation C++ (avec g++)
   
*****************************************************************************************/

#include "../platform.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h> /* sous /usr/ccs/lib/libm.a */
#include <locale.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>


/* Cas de la construction de la DLL */
#ifdef BUILD_DLL
#define LINKDLL extern "C" __declspec(dllexport)
#define LINKDLLCPP __declspec(dllexport)
#else
#define LINKDLL
#define LINKDLLCPP
#endif

/*
Syntaxe de compilation
sous DEC
gcc -c tools.c -lm

sous Solaris
gcc -c tools.c 

Sous Windows en mode DLL
gcc -o tools.dll -shared tools.c

Sous CygWin
gcc -c tools.c
*/

/* Definition permettant de compiler du C++  */
/* #define CPPLUS */

#ifndef CPPLUS
#define bool int
#define true 1
#define false 0
#endif

/* Definition permettant de compiler du C++ Windows  */
/* #define WIN32 */
#ifdef WIN32
#include <windows.h>
#endif

#ifndef __TOOLS
#define __TOOLS
void printversion_tools(void);

LINKDLL int mprintf( const char * ) ;
LINKDLL bool find( const char * ) ;

/**************************************************************************
		FONCTIONS DE GESTION DE CHAINES
**************************************************************************/
int maj( int ) ;
#ifndef CPPLUS
int majuscule( signed char [] ) ; /* Fonction permettant de passer une chaine de caracteres en majuscules */
/*void strcat(char *, char);*/
#else
/* LINKDLL int majuscule(signed char []); */
LINKDLL int majuscule( char [] ) ;
#endif

LINKDLL int stricmp( const char * s1 , const char * s2 ) ; /* Fonction permettant de faire des comparaisons de chaine en majuscule */
LINKDLL char * strnew( const double ) ;
LINKDLL int str( char *, double const ) ; /* Fonction permettant de remplir une chaine de caracteres avec un entier */
LINKDLL char * strbstr( char *, const char * ) ; /* Fonction permettant de retrouver une sous-chaine dans une autre en partant de la fin */
LINKDLL char * strcatc( char *, const char ) ;	/* Fonction permettant de concatener un caractere a la fin d'une chaine de caracteres */
LINKDLL char * strbcat( const char *, char * ) ; /* Fonction permettant de concatener la premiere chaine au debut de la seconde */
	/* strbcat = fonction ko */
LINKDLL int strrepeat( char *, const char *, const unsigned int ) ; /* Fonction permettant de construire une chaine de caracteres par repetition d'une autre chaine */

LINKDLL double val( const char [] ) ; /* Fonction transformant une chaine de caracteres en réel (double) */

LINKDLL char * copynew( char const [], int const, int const ) ;
LINKDLL int copy( char * , const char * , const int , const int ) ; /* Fonction permetant de des carateres d'une chaine dans une autre */

LINKDLL int pos( const char * , const char * ) ; /* Fonction permettant de retrouver la position d'une chaine dans une autre chaine */
LINKDLL int posc( const char , const char * ) ; /* Fonction permettant de retrouver le position d'un caractere dans une chaine */
LINKDLL int posi( const char * , const char * , const int ) ; /* Fonction permettant de retrouver le position d'un caractere dans une chaine a partir d'une position donnee */
LINKDLL int posic( const char , const char *, const int ) ; /* Fonction permettant de retrouver le position d'un caractere dans une chaine a partir d'une position donnee */

LINKDLL int posn( const char * , const char * ) ; /* Fonction permettant de retrouver la position d'une chaine dans une autre en partant de la fin */
LINKDLL int posnc( const char , const char * ) ; /* Fonction permettant de retrouver la position d'un caractere dans une chaine en partant de la fin */

LINKDLL int mpos( const char * , const char * ) ; /* Fonction permettant de retrouver la position d'une chaine dans une autre sans regarder la casse */
LINKDLL int strinf( const char * , const char * ) ; /* Procédure permettant de tester l'infériorité de deux chaînes de caractères */

LINKDLL char * delnew( const char * , const int , const int ) ;
LINKDLL int del( char * , const int , const int ) ; /* Fonction permettant de supprimer une partie d'une chaine de caracteres */

LINKDLL char * insertnew( const char * , const char * , const int ) ;
LINKDLL int insert( char *, const char * , const int ) ; /* Fonction permettant d'inserer une chaine dans une autre */

LINKDLL int replacec( char *, const char , const char ) ; /* Fonction permettant de remplacer un caractere par un autre dans toute une chaine */
LINKDLL int remplacec( char *, const char , const char ) ; /* Fonction permettant de remplacer un caractere par un autre dans toute une chaine */
LINKDLL int replace( char *, const char * , const char * ) ; /* Fonction permettant de remplacer une chaine par une autre dans toute une chaine */
LINKDLL int remplace( char *, const char * , const char * ) ; /* Fonction permettant de remplacer une chaine par une autre dans toute une chaine */

LINKDLL char * itos( const int i); /* Conversion d'entier en chaine de caracteres */
LINKDLL int matchpattern( const char * pattern, const char * st) ; /* Procedure permettant de verifier si une chaine match avec un pattern acceptant les caracteres jocker * et les ? */
LINKDLL int strscan( const char * st, const char * sep, ... ) ; /* Procedure permettant de rechercher dans une chaine de caracteres st les différents parametres de type char* separes par le(s) caractere(s) sep */

LINKDLL int rpad( char * st, const unsigned int len, const char motif ) ;/* rpad - ajout le motif à droite jusqu'à obtenir une longueur totale de n */
LINKDLL int drpad( char * st, const unsigned int len ) ; /* rpad - ajout des espace à droite jusqu'à obtenir une longueur totale de n */
LINKDLL int lpad( char * st, const unsigned int len, const char motif ) ; /* lpad - ajout le motif à gauche jusqu'à obtenir une longueur totale de n */
LINKDLL int dlpad( char * st, const int len ) ; /* dlpad - ajout des espace à gauche jusqu'à obtenir une longueur totale de n */
LINKDLL int rtrim( char * st, const char * motif ) ; /* rtrim - supprime à droite les caractères de la chaine motif */
LINKDLL int drtrim( char * st ) ; /* drtrim - supprime à droite les espaces tabulation et retour chariot */
LINKDLL int ltrim( char * st, const char * motif ) ; /* ltrim - supprime à gauche les caractères de la chaine motif */
LINKDLL int dltrim( char * st ) ; /* dltrim - supprime à gauche les espaces tabulation et retour chariot */
LINKDLL int trim( char * st, const char * motif ) ; /* trim - supprime à gauche et à droite les caractères de la chaine motif */
LINKDLL int dtrim( char * st ) ; /* dtrim - supprime à gauche et à droite les espaces tabulation et retour chariot */

LINKDLL int scanparam( char *, int *, char **argv, char * ) ; /* Fonction permettant de recuperer un argument de la ligne de commande et de le mettre dans la variable buf */
LINKDLL int scanparam1( char * st , int * , char ** argv ) ; /* Fonction permettant de recuperer un flag de la ligne de commande*/

LINKDLL int param_init( const int argc, const char **argv ) ; /* Copie la ligne de commande dans un tableau interne */
LINKDLL int param_nbr( void ) ; /* Donne le nombre d'arguments restant */
LINKDLL char ** param_tab( void ) ; /* Renvoie le tableau de paramètres restants */
LINKDLL int param_scan1( const char * val ) ; /* Test l'existance d'un flag et le supprime */
LINKDLL int param_scan( const char * val, char * st ) ; /* Test l'existance d'un paramètre et le supprime */
LINKDLL char * param_get( const int nb ) ; /* Récupère le contenu d'un paramètre */
LINKDLL void param_print( void ) ; /* Affiche le buffer interne */
LINKDLL void param_clean( void ) ; /* Vide le buffer interne */

/**************************************************************************
		FONCTIONS DE GESTION DE DATE
**************************************************************************/
LINKDLL int adddate( const int, char * ) ; /* Calcul de la date à partir d'aujourd'hui +/- n secondes */
#ifndef CPPLUS
LINKDLL void mysleep( const double delay ) ; /* Fonction d'attente de delay seconds */
#endif

/**************************************************************************
		FONCTIONS MATHEMATIQUES
**************************************************************************/
LINKDLL double sqr( const double ) ;
LINKDLL double myabs( const double ) ;


LINKDLL double mymin( const double , const double ) ;
LINKDLL int mymini( const int , const int ) ;
LINKDLL double mymax( const double , const double ) ;
LINKDLL int mymaxi( const int , const int ) ;
LINKDLL int sgn( const double ) ;

/**************************************************************************
		GENERATEUR DE NOMBRES ALEATOIRES
**************************************************************************/
LINKDLL void myrandseed( const int ) ;
LINKDLL double  myrandomd( void ) ;
LINKDLL int myrandom( const int ) ;
LINKDLL void myrandomize( void ) ;

/*********************************************************************************************
		GESTION DES ERREURS ERRNO
*********************************************************************************************/
LINKDLL char *sterrno( const int value ) ; /* Fonction permettant de retrouver le libellé d'une erreur a partir de la valeur errno */
LINKDLL char *ssterrno( const char * code ) ; /* Fonction permettant de retrouver le libellé d'une erreur a partir du code errno */

/**************************************************************************
		ACCES AUX FICHIERS
**************************************************************************/
LINKDLL int existfile( const char * ) ; /* Teste l'existance d'un fichier */
LINKDLL int existdir( const char * ) ;   /* Teste l'existance d'un repertoire */
LINKDLL int existlink( const char * ) ; /* Teste l'existance d'un lien symbolique */
LINKDLL int exist( const char * ) ;         /* Teste l'existance d'un fichier ou d'un repertoire ou d'un lien symbolique */
LINKDLL long filesize( const char * ) ; /* Donne la taille d'un fichier */
LINKDLL int rmalldir( const char * ) ;	/* Spprime toute une arborescence */
LINKDLL time_t filetime( const char * ) ;	/* Recupere la date de derniere modification d'un fichier */
//LINKDLL void dirname( const char *, char * ) ; /* Récupère le répertoire dans un chemin, "" si vide */

#ifndef PERSOPORT
LINKDLL void basename( const char *, char * ) ; /* Récupère le nom de fichier dans un chemin, "" si vide */
#endif

LINKDLL void URLencode( char * ) ; /* Procedure d'encodage des parametes d'une URL ( ' ' -> '+', et ? -> %XX ) */
LINKDLL void URLencodeFilename( char * ) ; /* Procedure d'encodage des chemins d'une URL ( ? -> %XX y compris pour les ' ' ) */
LINKDLL void URLdecode( char * ) ; /* Procedure de decodage d'une URL (remplace les %XX par leur valeur) */
LINKDLL int URLread( const char * URL, char * protocol, char * user, char * password, char * adress, char * port, char * path, char * name, char * param ) ; /* Procedure de lecture des elements d'une URL au format: protocol://user:password@adress:port/path/filename?param */

#endif

/* Partie specifique au C++ */ 
#ifdef CPPLUS

LINKDLLCPP char * strcat( char * , const char ) ;	/* Fonction permettant de concatener un caractere a la fin d'une chaine de caracteres */
LINKDLLCPP int pos( const char , const char * ) ; /* Fonction permettant de retrouver le position d'un caractere dans une chaine */
LINKDLLCPP int posn( const char , const char * ) ; /* Fonction permettant de retrouver la position d'un caractere dans une chaine en partant de la fin */
LINKDLLCPP int remplace( char * , const char , const char ) ; /* Fonction permettant de remplacer un caractere par un autre dans toute une chaine */

/**************************************************************************
		CLASSE T-WEB
**************************************************************************/
#ifndef TWEB
#define TWEB
class LINKDLLCPP TWeb {
  public:
	TWeb() ;
	~TWeb() ;
	int readcmd() ;
	int getcmdlen() ;
	int getcmd( char st[] ) ;
	int getarg( char arg[], char st[] ) ;

	void contenttype() ;
	void write( char st[] ) ;
	void writeln( char st[] ) ;
	void getenv( char env[], char st[] ) ;
	void writeenv() ;
  private:
	int readget() ;
	int readpost() ;
	void decode( char st[] ) ;
	char * lcmd, * meth ;
  } ;
#endif

/**************************************************************************
     		       CLASSE T-FILE
**************************************************************************/
#ifndef TFILE
#define TFILE
class LINKDLLCPP TFile {
  public:
	TFile( void ) { vDIR = NULL ; vDirent = NULL ; maskDIR = NULL ; maskFILE = NULL ; maskMAJ = 0 ; }
	~TFile( void ) ;
	int setmask( char * mask, int maskMAJ = 0 ) ;
	int nextfile( char * stfile ) ;
	int prevfile( char * stfile ) ;
	int dir( void ) ;
	int dir( char * mask ) ;
	void rewind( void ) ;

	static const int MAJ;

  private:
	bool testfile( char * stfile ) ;
	void info( void ) ;

	DIR * vDIR ;
	struct dirent * vDirent ;
	char * maskDIR, * maskFILE ;
	int maskMAJ ;
  } ;

#endif

#endif /* Fin de la partie spécifique C++ */


/*
typedef long    time_t;
typedef long _ssize_t;
typedef _ssize_t ssize_t;
typedef unsigned int size_t;
*/
