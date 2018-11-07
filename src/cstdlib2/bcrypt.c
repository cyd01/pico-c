#include "bcrypt.h"

static const char bcrypt_pattern_hexa[] = "ABCDEF" ;
static const char bcrypt_pattern_letters[] = "AZERTYUIOPQSDFGHJKLMWXCVBN" ;
static const char bcrypt_pattern_alpha[] = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn" ;
static const char bcrypt_pattern_alphanum[] = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn0123456789" ;
static const char bcrypt_pattern_base64[] = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn0123456789+/" ;
static const char bcrypt_pattern_base64url[] = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn0123456789-_" ;
static const char bcrypt_pattern_printable[] = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn0123456789 +-*/%_!:;.,?$=@&#(){}[]<>'`^" ;

static int bcrypt_verbose = 0 ;

static void bcrypt_scramble( char * pattern, const unsigned int pattern_length, const char * key, const unsigned int key_length ) {
	int unsigned i, j = 0, k, num, nrun ;
	char c ;
	if( key == NULL ) return ;
	if( key_length == 0 ) return ;
	
	nrun = (int)( ( key_length / 2 ) / pattern_length )+1 ; /* Pour utiliser toute la longueur de la clé si elle est plus longue que le pattern */
	/* if( nrun == 0 ) nrun = 1 ; */
	if( bcrypt_verbose ) printf( "Scramble: %d run(s)\n", nrun );
	
	for( k = 0 ; k < nrun ; k ++ ) {
		for( i = 0 ; i < pattern_length ; i++ ) {
			num = ( i + key[j] ) % pattern_length ;
			c = pattern[i] ;
			pattern[i] = pattern[num] ;
			pattern[num] = c ;
			j++ ;
			if( j >= key_length ) j = 0 ;
			}
		}
	}
	
int bcrypt_test_pattern( const char * pattern, const unsigned int pattern_length ) {
	unsigned int i, j ;

	if( pattern == NULL ) return 0 ;
	if( pattern_length < 2 ) return 0 ;
	if( (pattern[0]=='\n')||(pattern[0]=='\r') ) return 0 ;
	for( i=1 ;  i < pattern_length ; i++ ) {
		if( (pattern[i]=='\n')||(pattern[i]=='\r') ) return 0 ;
		for( j = 0 ; j < i ; j++ )
			if( pattern[j] == pattern[i] ) return 0 ;
		}

	return 1 ;
	}
	
static int bcrypt_init_scramble( char * init_scramble, const char * pattern ) {
	unsigned int i ;	
	sprintf( init_scramble, "%05d", rand() ) ;
	for( i = 0 ; i < 5 ; i++ ) { 
		init_scramble[i] = init_scramble[strlen(init_scramble)-1-i] ; 
		init_scramble[i] = pattern[ init_scramble[i]%strlen( pattern ) + 1 ] ; 
		}
	init_scramble[5] = '\0' ;
	return 5 ;
	}

void bcrypt_init( const long t ) {
	if( t == 0 ) srand( time(0) ) ;
	else srand( t ) ;
	}
	
int bcrypt_string( const char * st_in, char * st_out, const unsigned int length, const char * init_pattern, const char * key, const unsigned int maxlinesize ) {
	char * buf, * pattern ;
	unsigned char c ;
	unsigned int i, j = 0, linesize = 0, swapnumber = 0 ;
	char init_scramble[256] = "" ;
	
	if( !bcrypt_test_pattern( init_pattern, strlen( init_pattern ) ) )
		{ fprintf( stderr, "Not a valid pattern: %s\n", init_pattern ) ; return 0 ; }
	
	if( ( buf = (char*) malloc( length + 1 ) ) == NULL ) return 0 ;
	memcpy( buf, st_in, length + 1 ) ;
	
	if( ( pattern = (char*) malloc( strlen( init_pattern ) + 1 ) ) == NULL ) 
		{ free( buf ) ; return 0 ; }
	strcpy( pattern, init_pattern ) ;

	j = bcrypt_init_scramble( init_scramble, pattern ) ;
	for( i = 0 ; i < j ; i++ ) st_out[i] = init_scramble[i] ;
	linesize = j ;

	bcrypt_scramble( pattern, strlen( pattern ), init_scramble, strlen( init_scramble ) ) ; 

	for( i = 0 ; i < length ; i++ ) {
		c = buf[i] ;
		while( c >= (int)( strlen( pattern ) - 1 ) ) {
			st_out[j] = pattern[strlen(pattern)-1] ; 
			j++ ;
			c = c - ( strlen(pattern) -1 ) ;
			bcrypt_scramble( pattern, strlen( pattern ), key, strlen( key ) ) ; 
			swapnumber = 0 ;
			linesize++ ;
			if( ( maxlinesize > 0 ) &&( linesize >= maxlinesize ) ) 
				{ st_out[j] = '\n' ; j++ ; linesize = 0 ; }
			}
		st_out[j] = pattern[(int)c] ;
		j++ ;
		swapnumber++ ;
		if( swapnumber >= strlen( pattern ) ) 
			{ bcrypt_scramble( pattern, strlen( pattern ), key, strlen( key ) ) ; swapnumber = 0 ; }
		linesize++ ;
		if( ( maxlinesize > 0 ) &&( linesize >= maxlinesize ) ) 
			{ st_out[j] = '\n' ; j++ ; linesize = 0 ; }
		}
	st_out[j] = '\0' ;

	free( pattern ) ;
	free( buf ) ;
	return j ;
	}

int bcrypt_string_printable( const char * st_in, char * st_out, const unsigned int length, const char * key, const unsigned int maxlinesize ) {
	return bcrypt_string( st_in, st_out, length, bcrypt_pattern_printable, key, maxlinesize ) ;
	}
	
int bcrypt_string_base64( const char * st_in, char * st_out, const unsigned int length, const char * key, const unsigned int maxlinesize ) {
	return bcrypt_string( st_in, st_out, length, bcrypt_pattern_base64, key, maxlinesize ) ;
	}

int bcrypt_string_base64url( const char * st_in, char * st_out, const unsigned int length, const char * key, const unsigned int maxlinesize ) {
	return bcrypt_string( st_in, st_out, length, bcrypt_pattern_base64url, key, maxlinesize ) ;
	}
	
int bcrypt_string_auto( char * st, const unsigned int length, const char * init_pattern, const char * key, const unsigned int maxlinesize ) {
	return bcrypt_string( st, st, length, init_pattern, key, maxlinesize ) ;
	}

int buncrypt_string( const char * st_in, char * st_out, const unsigned int length, const char * init_pattern, const char * key ) {
	char * buf, * pattern, c = 0, c2 ;
	unsigned int i, j = 0, k, swapnumber = 0 ;
	char init_scramble[256] = "" ;

	if( !bcrypt_test_pattern( init_pattern, strlen( init_pattern ) ) )
		{ fprintf( stderr, "Not a valid pattern: %s\n", init_pattern ) ; return 0 ; }
		
	if( ( buf = (char*) malloc( length + 1 ) ) == NULL ) return 0 ;
	memcpy( buf, st_in, length + 1 ) ;
	
	if( ( pattern = (char*) malloc( strlen( init_pattern ) + 1 ) ) == NULL ) 
		{ free( buf ) ; return 0 ; }
	strcpy( pattern, init_pattern ) ;

	for( i = 0 ; i < 5 ; i++ ) init_scramble[i] = st_in[i] ;
	init_scramble[5] = '\0' ;
	bcrypt_scramble( pattern, strlen( pattern ), init_scramble, strlen( init_scramble ) ) ;
		
	c2 = 0 ;
	for( i = 5 ; i < length ; i++ ) {
		if( c != '\n' )	{
		c = buf[i] ;

		while( c == pattern[strlen(pattern)-1] ) {
			c2 = c2 + ( strlen(pattern) -1 ) ;
			bcrypt_scramble( pattern, strlen( pattern ), key, strlen( key ) ) ; 
			swapnumber = 0 ;
			do { i++ ; c = buf[i] ; } while( c == '\n' ) ;
			}
		for( k = 0 ; k < strlen( pattern ) ; k++ ) 
			if( pattern[k] == c ) 
				{ c2 = c2 + k ; k = strlen( pattern ) ; }
		st_out[j] = c2 ;
		j++;
		c2 = 0 ;
		swapnumber++ ;
		if( swapnumber >= strlen( pattern ) ) 
			{ bcrypt_scramble( pattern, strlen( pattern ), key, strlen( key ) ) ; swapnumber = 0 ; }
		}
		}
	st_out[j] = '\0' ;

	free( pattern ) ;
	free( buf ) ;
	return j ;
	}

int buncrypt_string_printable( const char * st_in, char * st_out, const unsigned int length, const char * key ) {
	return buncrypt_string( st_in, st_out, length, bcrypt_pattern_printable, key ) ;
	}

int buncrypt_string_base64( const char * st_in, char * st_out, const unsigned int length, const char * key ) {
	return buncrypt_string( st_in, st_out, length, bcrypt_pattern_base64, key ) ;
	}

int buncrypt_string_base64url( const char * st_in, char * st_out, const unsigned int length, const char * key ) {
	return buncrypt_string( st_in, st_out, length, bcrypt_pattern_base64url, key ) ;
	}

int buncrypt_string_auto( char * st, const unsigned int length, const char * init_pattern, const char * key ) {
	return buncrypt_string( st, st, length, init_pattern, key ) ;
	}

int bcrypt_file( const char * filename_in, const char * filename_out, const char * init_pattern, const char * key, const unsigned int maxlinesize ) {
	FILE * fp, * fpout ;
	unsigned int linesize = 0, swapnumber = 0 ;
	int c ;
	char * pattern, init_scramble[256] = "" ;

	if( !bcrypt_test_pattern( init_pattern, strlen( init_pattern ) ) )
		{ fprintf( stderr, "Not a valid pattern: %s\n", init_pattern ) ; return 0 ; }

	if( !strcmp( filename_in, "-" ) ) { fp = stdin ; }
	else {
#ifdef WIN32
		if( ( fp = fopen( filename_in, "rb" ) ) == NULL )
#else
		if( ( fp = fopen( filename_in, "r" ) ) == NULL )
#endif
			{
			fprintf( stderr, "Unable to open file %s\n", filename_in ) ;
			return 0 ;
			}
		}

	if( !strcmp( filename_out, "-" ) ) { fpout = stdout ; }
	else {
#ifdef WIN32
		if( ( fpout = fopen( filename_out, "wt" ) ) == NULL )
#else
		if( ( fpout = fopen( filename_out, "wt" ) ) == NULL ) 
#endif
			{
			fprintf( stderr, "Unable to open file %s\n", filename_out ) ;
			fclose( fp ) ; 
			return 0 ; 
			}
		}

	if( ( pattern = (char*) malloc( strlen( init_pattern ) + 1 ) ) == NULL ) 
		{ fclose( fp ) ; fclose( fpout ) ; return 0 ; }
	strcpy( pattern, init_pattern ) ;
	
	linesize = bcrypt_init_scramble( init_scramble, pattern ) ;
	fwrite( init_scramble, 1, linesize, fpout ) ;
	
	bcrypt_scramble( pattern, strlen( pattern ), init_scramble, strlen( init_scramble ) ) ; 

	while( ( c = fgetc( fp ) ) != EOF ) {
		while( c >= (int)( strlen( pattern ) - 1 ) ) {
			fprintf( fpout, "%c", pattern[strlen(pattern)-1] ) ;
			c = c - ( strlen(pattern) -1 ) ;
			bcrypt_scramble( pattern, strlen( pattern ), key, strlen( key ) ) ;
			swapnumber = 0 ;
			linesize++ ;
			if( ( maxlinesize > 0 ) &&( linesize >= maxlinesize ) ) 
				{ fprintf( fpout, "\n" ) ; linesize = 0 ; }
			}
		fprintf( fpout, "%c", pattern[c] ) ;
		swapnumber++ ;
		if( swapnumber >= strlen( pattern ) ) 
			{ bcrypt_scramble( pattern, strlen( pattern ), key, strlen( key ) ) ; swapnumber = 0 ; }
		linesize++ ;
		if( ( maxlinesize > 0 ) &&( linesize >= maxlinesize ) ) 
			{ fprintf( fpout, "\n" ) ; linesize = 0 ; }
		}
	
	free( pattern ) ;
	if( fp != stdin ) fclose( fp );
	if( fpout != stdout ) fclose( fpout );
	return 1 ;
	}

int bcrypt_file_printable( const char * filename_in, const char * filename_out, const char * key, const unsigned int maxlinesize ) {
	return bcrypt_file( filename_in, filename_out, bcrypt_pattern_printable, key, maxlinesize ) ;
	}

int bcrypt_file_base64( const char * filename_in, const char * filename_out, const char * key, const unsigned int maxlinesize ) {
	return bcrypt_file( filename_in, filename_out, bcrypt_pattern_base64, key, maxlinesize ) ;
	}

int bcrypt_file_base64url( const char * filename_in, const char * filename_out, const char * key, const unsigned int maxlinesize ) {
	return bcrypt_file( filename_in, filename_out, bcrypt_pattern_base64url, key, maxlinesize ) ;
	}
	
int bcrypt_file_auto( const char * filename, const char * init_pattern, const char * key, const int unsigned maxlinesize ) {
	char * fileout ;
	int res ;

	if( !strcmp( filename, "-" ) ) 
		return bcrypt_file( "-", "-", init_pattern, key, maxlinesize ) ;
	
	fileout = (char*) malloc( strlen( filename ) + 5 ) ;
	sprintf( fileout, "%s.bcr", filename ) ;
	
	res = bcrypt_file( filename, fileout, init_pattern, key, maxlinesize ) ;
	free( fileout ) ;

	return res ;
	}

int buncrypt_file( const char * filename_in, const char * filename_out, const char * init_pattern, const char * key ) {
	FILE * fp, * fpout ;
	unsigned int swapnumber = 0, i ;
	int c, c2 ;
	char * pattern, init_scramble[256] ;

	if( !bcrypt_test_pattern( init_pattern, strlen( init_pattern ) ) )
		{ fprintf( stderr, "Not a valid pattern: %s\n", init_pattern ) ; return 0 ; }

	if( !strcmp( filename_in, "-" ) ) { fp = stdin ; }

	else {
#ifdef WIN32
		if( ( fp = fopen( filename_in, "rt" ) ) == NULL )
#else
		if( ( fp = fopen( filename_in, "r" ) ) == NULL )
#endif
			{
			fprintf( stderr, "Unable to open file %s\n", filename_in ) ;
			return 0 ;
			}
		}

	if( !strcmp( filename_out, "-" ) ) { fpout = stdout ; }
	else {
#ifdef WIN32
		if( ( fpout = fopen( filename_out, "wb" ) ) == NULL ) 
#else
		if( ( fpout = fopen( filename_out, "wb" ) ) == NULL ) 
#endif
			{ 
			fprintf( stderr, "Unable to open file %s\n", filename_out ) ;
			fclose( fp ) ;
			return 0 ; 
			}
		}

	if( ( pattern = (char*) malloc( strlen( init_pattern ) + 1 ) ) == NULL ) 
		{ fclose( fp ) ; fclose( fpout ) ; return 0 ; }
	strcpy( pattern, init_pattern ) ;

	fread( init_scramble, 1, 5, fp ) ; init_scramble[5] = '\0' ;
	bcrypt_scramble( pattern, strlen( pattern ), init_scramble, strlen( init_scramble ) ) ; 
	
	c2 = 0 ;
	while( ( c = fgetc( fp ) ) != EOF ) { 
		if( c != '\n' ) {
		while( c == pattern[strlen(pattern)-1] ) {
			c2 = c2 + ( strlen(pattern) -1 ) ;
			bcrypt_scramble( pattern, strlen( pattern ), key, strlen( key ) ) ; 
			swapnumber = 0 ;
			while( ( c = fgetc( fp ) ) == '\n' ) { }
			}
		for( i = 0 ; i < strlen( pattern ) ; i++ ) 
			if( pattern[i] == c ) 
				{ c2 = c2 + i ; i = strlen( pattern ) ; }
		fprintf( fpout, "%c", c2 ) ;
		swapnumber++ ;
		if( swapnumber >= strlen( pattern ) ) 
			{ bcrypt_scramble( pattern, strlen( pattern ), key, strlen( key ) ) ; swapnumber = 0 ; }
		c2 = 0 ;
		}
		}

	free( pattern ) ;
	if( fp != stdin ) fclose( fp );
	if( fpout != stdout ) fclose( fpout );
	return 1 ;
	}
	
int buncrypt_file_printable( const char * filename_in, const char * filename_out, const char * key ) {
	return buncrypt_file( filename_in, filename_out, bcrypt_pattern_printable, key ) ;
	}

int buncrypt_file_base64( const char * filename_in, const char * filename_out, const char * key ) {
	return buncrypt_file( filename_in, filename_out, bcrypt_pattern_base64, key ) ;
	}

int buncrypt_file_base64url( const char * filename_in, const char * filename_out, const char * key ) {
	return buncrypt_file( filename_in, filename_out, bcrypt_pattern_base64url, key ) ;
	}

int buncrypt_file_auto( const char * filename, const char * init_pattern, const char * key ) {
	char * fileout ;
	int res ;

	if( !strcmp( filename, "-" ) ) 
		return buncrypt_file( "-", "-", init_pattern, key ) ;
	
	fileout = (char*) malloc( strlen( filename ) + 5 ) ;
		
	if( !strcmp( filename+strlen(filename)-4, ".bcr" ) ) {
			strcpy( fileout, filename ) ;
			fileout[strlen(fileout)-4] = '\0' ;
			}
	else
		sprintf( fileout, "%s.ucr", filename ) ;

	res = buncrypt_file( filename, fileout, init_pattern, key ) ;
	free( fileout ) ;

	return res ;
	}


void bcrypt_usage( char * progname ) {
	fprintf( stderr, "Usage: %s [-a] [-b] [-c] [-d] [-h] [-k key] [-l] [-n] [-s size] [-x] filename|string\n", progname ) ;
	fprintf( stderr, "\t-a: A-Z, a-z pattern\n" ) ;
	fprintf( stderr, "\t-b: base64 pattern\n" ) ;
	fprintf( stderr, "\t-d: decrypt\n" ) ;
	fprintf( stderr, "\t-c: string encryption\n" ) ;
	fprintf( stderr, "\t-h: this help message\n" ) ;
	fprintf( stderr, "\t-k key: define a key password\n" ) ;
	fprintf( stderr, "\t-l: A-Z pattern\n" ) ;
	fprintf( stderr, "\t-n: A-Z, a-z, 0-9 pattern\n" ) ;
	fprintf( stderr, "\t-s size: size of output line (0=unlimited)\n" ) ;
	fprintf( stderr, "\t-u: base64URL pattern\n" ) ;
	fprintf( stderr, "\t-x: A-F pattern\n" ) ;
	fprintf( stderr, "\tfilename|string: name of the file to treat (- for stdin), or string (with -c option)\n" ) ;
	}

int bcrypt_main( int argc, char * argv[], char * arge [] ) {
	int return_code = 0, action = 1, maxlinesize = 80 ;
	char pattern[1024], str[4096] ;
	signed char ch ;
	char * key = NULL ;

	if( !strcmp( argv[0]+strlen(argv[0])-12, "buncrypt.exe" ) ) action = action + 1 ;
	
	strcpy( pattern, bcrypt_pattern_printable ) ;
	
	while( ( ch = getopt( argc, argv, "abcdhk:lns:vx" ) ) != -1 ) {
		switch( ch ) {
			case 'a' : strcpy( pattern, bcrypt_pattern_alpha ) ; break ;
			case 'b' : strcpy( pattern, bcrypt_pattern_base64 ) ; break ;
			case 'c' : action = action + 2 ; break ;
			case 'd' : action = action + 1 ; break ;
			case 'l' : strcpy( pattern, bcrypt_pattern_letters ) ; break ;
			case 'n' : strcpy( pattern, bcrypt_pattern_alphanum ) ; break ;
			case 's' : maxlinesize = atoi( optarg ) ; break ;
			case 'x' : strcpy( pattern, bcrypt_pattern_hexa ) ; break ;
			case 'k' : 
				if( ( key = (char*) malloc( strlen( optarg ) + 1 ) ) == NULL ) return -5 ;
				strcpy( key, optarg ) ;
				break ;
			case 'u' : strcpy( pattern, bcrypt_pattern_base64url ) ; break ;
			case 'v' : bcrypt_verbose = 1 ; break ;
			case 'h' :
			default : bcrypt_usage( argv[0] ) ; exit( 1 ) ; break ;
			}
		}

	if( key == NULL ) { key = (char*) malloc( 5 ) ; strcpy( key, "0910" ) ; }

	if( optind == argc ) {
		switch( action ) {
			case 1 : return_code = bcrypt_file_auto( "-", pattern, key, maxlinesize ) ; break ;
			case 2 : return_code = buncrypt_file_auto( "-", pattern, key ) ; break ;
			default: bcrypt_usage( argv[0] ) ; exit( 1 ) ; break ;
			}
		}
	else {
		switch( action ) {
			case 1 : return_code = bcrypt_file_auto( argv[optind], pattern, key, maxlinesize ) ; break ;
			case 2 : return_code = buncrypt_file_auto( argv[optind], pattern, key ) ; break ;
			case 3 : return_code = bcrypt_string( argv[optind], str, strlen( argv[optind] ), pattern, key, maxlinesize ) ; 
				printf( "%s\n", str ) ;
				break ;
			case 4 : return_code = buncrypt_string( argv[optind], str, strlen( argv[optind] ), pattern, key ) ; 
				printf( "%s\n", str ) ;
				break ;
			default: bcrypt_usage( argv[0] ) ; exit( 1 ) ; break ;
			}
		}	
	
	if( return_code == 0 ) {
		fprintf( stderr, "An error occure during de crypting process\n" ) ;
		if( bcrypt_verbose ) printf( "return_code=%d\n", return_code ) ;
		return_code = -1 ;
		}
	if( return_code == 1 ) return_code = 0 ;
	
	if( key != NULL ) free( key ) ;
	return return_code ;
	}

#ifdef MAIN
int main( int argc, char * argv[], char * arge [] ) {
	int return_code = 0 ;
	return_code = bcrypt_main( argc, argv, arge ) ;
	return return_code ;
	}
#endif
