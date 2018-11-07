/* Platform_win32 specific includes */

#ifndef PLATFORM_WIN32_H
#define PLATFORM_WIN32_H

/*#   define HEAP_SIZE C_HEAPSIZE */
/*#   define NO_FP */
/*#   define NO_CTYPE */
/*#   define NO_HASH_INCLUDE */
/*#   define NO_MODULUS */

# define USE_MALLOC_STACK                   /* stack is allocated using malloc() */
# define USE_MALLOC_HEAP                    /* heap is allocated using malloc() */
/*#    define HEAP_SIZE (128*1024)  */              /* space for the heap and the stack */
/*#    define NO_FP */
/*#    define BUILTIN_MINI_STDLIB */
/*#  define USE_READLINE */

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <assert.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
/*# include <unistd.h> */
# include <stdarg.h>
# include <setjmp.h>
# ifndef NO_FP
#  include <math.h>
#  define PICOC_MATH_LIBRARY
#  undef BIG_ENDIAN
#  if defined(__powerpc__) || defined(__hppa__) || defined(__sparc__)
#   define BIG_ENDIAN
#  endif
# endif

/* secure versions have a slightly different name */
#define strtok_r strtok_s
#define snprintf _snprintf
#define index strchr
#define rindex strrchr
#define timegm mktime
/* #define gmtime_r gmtime_s */
struct tm *gmtime_r(const time_t *time, struct tm *result);

extern jmp_buf ExitBuf;
#endif /* PLATFORM_WIN32_H */
