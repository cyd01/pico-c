#include "../picoc.h"
#include "../interpreter.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

/* mark where to end the program for platforms which require this */
jmp_buf PicocExitBuf;

#ifndef NO_DEBUGGER
#include <signal.h>

Picoc *break_pc = NULL;

static void BreakHandler(int Signal)
{
    PlatformPrintf(stdout, "break\n");
    break_pc->DebugManualBreak = TRUE;
}

void PlatformInit(Picoc *pc) 
{
    /* capture the break signal and pass it to the debugger */
    signal(SIGINT, BreakHandler);
}
#else
void PlatformInit()
{
}
#endif

void PlatformCleanup(Picoc *pc)
{
}

/* get a line of interactive input */
char *PlatformGetLine(char *Buf, int MaxLen, const char *Prompt)
{
#ifdef USE_READLINE
    if (Prompt != NULL)
    {
        /* use GNU readline to read the line */
        char *InLine = readline(Prompt);
        if (InLine == NULL)
            return NULL;
    
        Buf[MaxLen] = '\0';
        strncpy(Buf, InLine, MaxLen-1);
        strncat(Buf, "\n", MaxLen-1);
        
        if (InLine[0] != '\0')
            add_history(InLine);
            
        free(InLine);
        return Buf;
    }
#endif

    if (Prompt != NULL)
        printf("%s", Prompt);
        
    fflush(stdout);
    return fgets(Buf, MaxLen, stdin);
}

/* get a character of interactive input */
int PlatformGetCharacter(void)
{
    fflush(stdout);
    return getchar();
}

/* write a character to the console */
void PlatformPutc(unsigned char OutCh, union OutputStreamInfo *Stream)
{
    putchar(OutCh);
}

/* read a file into memory */
char *PlatformReadFile(const char *FileName)
{
    struct stat FileInfo;
    char *ReadText;
    FILE *InFile;
    int BytesRead;
    
    if (stat(FileName, &FileInfo))
        ProgramFail(NULL, "can't read file %s\n", FileName);
    
    ReadText = malloc(FileInfo.st_size + 1);
    if (ReadText == NULL)
        ProgramFail(NULL, "out of memory\n");
        
    InFile = fopen(FileName, "r");
    if (InFile == NULL)
        ProgramFail(NULL, "can't read file %s\n", FileName);
    
    BytesRead = fread(ReadText, 1, FileInfo.st_size, InFile);
    if (BytesRead == 0)
        ProgramFail(NULL, "can't read file %s\n", FileName);

    ReadText[BytesRead] = '\0';
    fclose(InFile);
    
    return ReadText;    
}

/* read and scan a file for definitions */
void PicocPlatformScanFile(Picoc *pc, const char *FileName)
{
    char *SourceStr = PlatformReadFile(FileName);
    PicocParse(pc, FileName, SourceStr, strlen(SourceStr), TRUE, FALSE, TRUE, TRUE);
	
free(SourceStr); /* correction, pas de free en face du malloc de PlatformReadFile */
}

/* exit the program */
void PlatformExit(Picoc *pc, int RetVal)
{
    pc->PicocExitValue = RetVal;
    longjmp(PicocExitBuf, 1);
}


/*
	FONCTIONS DE REMPLACEMENT DUE A LA PLATE-FORME WINDOWS
*/

#include <time.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#include <sys/types.h>
#include <fcntl.h>
#include <tlhelp32.h>

typedef uint32_t uid_t ;
typedef uint32_t gid_t ;

/* simulates gmtime_r under windows
	The difference is that gmtime_r(3) is a standard POSIX function. The closest
	you can find to gmtime_r() on a windows environment is gmtime_s(), which has
	it's arguments reversed:
	
	    gmtime_r(const time_t*, struct tm*)
	    gmtime_s(struct tm*, const time_t*)
	
	Basically, they both convert a time value to a tm structure. gmtime_r then
	return a pointer to this structure (or NULL if failed), whereas gmtime_s 
	returns 0 if successful, and a errno_t in case of failure.
	The tm structure has the following body, as can be seen from both docs listed above:
	
	struct tm {
	    int tm_sec;         / seconds /
	    int tm_min;         / minutes /
	    int tm_hour;        / hours /
	    int tm_mday;        / day of the month /
	    int tm_mon;         / month /
	    int tm_year;        / year /
	    int tm_wday;        / day of the week /
	    int tm_yday;        / day in the year /
	    int tm_isdst;       / daylight saving time /
	};
*/
/*
struct tm *gmtime_r(const time_t *time, struct tm *result)
{
	errno_t gmtime_error = 0;
	gmtime_error = gmtime_s(result, time);
	
	if (gmtime_error==0)
		return result;
	else
		return NULL;
}
*/


struct tm *gmtime_r( const time_t *time, struct tm *result ) { return gmtime( time ) ; }

char *strtok_s(char *str, const char *delim, char **saveptr) { return strtok(str, delim) ; }

unsigned int alarm(unsigned int seconds) { return 0 ; }

unsigned int sleep( unsigned int seconds ) { Sleep (seconds * 1000) ; return 0 ; }

typedef unsigned long usecs_t;

int usleep(usecs_t usec) { Sleep((int)(usec/1000)) ; return 0 ; }

int truncate( const char *path, off_t length ) {  
  int fd, ret
//	, save
;
  fd = open (path, O_WRONLY);
  if (fd < 0)
    return -1;

  ret = ftruncate (fd, length);
//  save = errno;
  (void) close (fd);

  return ret;
}

char * getlogin( void ) {
  static char user_name[MAX_PATH];
  DWORD  length = sizeof (user_name);

  if (GetUserName (user_name, &length))
    return user_name;
  return NULL;
}

int getlogin_r(char *buf, size_t bufsize) { DWORD nSize = bufsize ; GetUserName( buf, &nSize ) ; return 0 ; }

void sync(void) { _flushall() ; }

int setuid( uid_t uid ) { return 0 ; }

int setgid(gid_t gid) { return 0 ; }

int setpgid(pid_t pid, pid_t pgid) ;
int setpgrp ( void ) { return setpgid (0, 0) ; }

char *win2unixpath(char *FileName) {
	char *s = FileName;
	while (*s) {
		if (*s == '\\') {
			*s = '/';
		}
		*s++;
	}
	return FileName;
}

char *unix2winpath(char *FileName) {
	char *s = FileName;
	while (*s) {
		if (*s == '/') {
			*s = '\\';
		}
		*s++;
	}
	return FileName;
}


long int __fpathconf( int fd,    int name) ;
long int pathconf (const char *path, int name) {
  if (path == NULL)   {     return -1;   }
  return __fpathconf (0, name);
}

uid_t getuid( void ) { return 0 ; }

int getppid ( void )
{
    HANDLE hProcess, thProcess;
    PROCESSENTRY32 ProcessEntry;

    thProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (thProcess == INVALID_HANDLE_VALUE) {
				return -1;
	}
    ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    ProcessEntry.th32ParentProcessID = 0;
    if (!Process32First(thProcess, &ProcessEntry)) {
				return -1;
	}
	CloseHandle(thProcess);
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, ProcessEntry.th32ProcessID);
    if (hProcess == NULL) {
		        return -1;
	}
	CloseHandle(hProcess);
	return ProcessEntry.th32ParentProcessID;
}

pid_t getpgid (pid_t pid) { return pid ; }

gid_t getgid( void ) { return 0 ; }

uid_t geteuid( void ) { return 0 ; }

gid_t getegid( void ) { return 0 ; }

pid_t getpgrp(void) { return getpgid(0) ; }

void WSAErr(const char *Msg) { fprintf(stderr, "%s: Socket error %d\n", Msg, WSAGetLastError()) ; }

void ws_cleanup(void) { if (!WSACleanup()) ; }

static int ws_init_done = 0;
int ws_init( void ) {
	if (!ws_init_done ) {
		int wsaerr;
    	WORD wVersionRequested;
		WSADATA wsaData;

		wVersionRequested = MAKEWORD( 1, 0 );
	    wsaerr = WSAStartup(wVersionRequested, &wsaData);
		if (wsaerr) {
			WSAErr("WSAStartup");
		    return -1;
		}
		atexit(ws_cleanup);
		ws_init_done = 1;
	}
	return 0;
}	

long int gethostid( void ){
	char name [MAX_PATH];
	struct hostent *hostinfo;
	char *ip;
	long int id;
		
	if (ws_init() == -1)
		return -1;
	if (gethostname(name, MAX_PATH) == 0) 
		if ((hostinfo = gethostbyname(name)) != NULL) {
			ip = inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[0]);
			id = inet_addr(ip);
			return id;
		}
	return 0L;
}


/* NOT IMPLEMENTED */

usecs_t ualarm(usecs_t usecs, usecs_t interval) { fprintf( stderr, "Not implemented yet !\n" ) ; return 0 ; }

size_t confstr(int name, char *buf, size_t len){ fprintf( stderr, "Not implemented yet !\n" ) ; return 0 ; }

char *ctermid(char *s) { fprintf( stderr, "Not implemented yet !\n" ) ; return NULL ; }

int fsync(int fildes) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int lockf(int fd, int cmd, off_t len) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int pause(void) { return fgetc(stdin) ; }

pid_t setsid(void) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int ttyname_r(int fd, char *buf, size_t buflen) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

pid_t vfork(void) { fprintf( stderr, "Not implemented yet !\n" ) ;  return -1 ; }

int chroot(const char *path) { fprintf( stderr, "Not implemented yet !\n" ) ; return 0 ; }

int chown(const char *path, uid_t owner, gid_t group) {	fprintf( stderr, "Not implemented yet !\n" ) ; return 0 ; }

int fchown(int fildes, uid_t owner, gid_t group) { fprintf( stderr, "Not implemented yet !\n" ) ; return 0 ; }

int fchdir( int fd ) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int fdatasync( int fd ) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

pid_t fork( void ) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int fpathconf( int i1, int i2 ) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

char * ttyname( int i ) { fprintf( stderr, "Not implemented yet !\n" ) ; return NULL ; }

int tcsetpgrp(int i, pid_t j) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

pid_t tcgetpgrp(int i) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

long sysconf(int i) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int symlink(const char *oldpath, const char *newpath) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int setreuid(uid_t ruid, uid_t euid) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int setregid(gid_t rgid, gid_t egid) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int setpgid(pid_t pid, pid_t pgid) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

void *sbrk(intptr_t increment) { fprintf( stderr, "Not implemented yet !\n" ) ; return  (void *) -1 ; }

long int __fpathconf( int fd, int name) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int nice(int inc) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int link ( const char *from, const char *to ) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

int lchown(const char *path, uid_t owner, gid_t group) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

char *getpass(char * st) { fprintf( stderr, "Not implemented yet !\n" ) ; return NULL ; }

int getdtablesize( void ) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

pid_t wait( int *status ) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }

pid_t waitpid(pid_t pid, int *status, int options) { fprintf( stderr, "Not implemented yet !\n" ) ; return -1 ; }
