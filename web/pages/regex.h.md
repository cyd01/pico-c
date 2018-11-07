# regex.h

Here are the structures and type defined into ```regex.h``` header:

```cpp
typedef int regoff_t ;
typedef struct __REGEXtruct regex_t ;
typedef struct __REGMATCHtruct regmatch_t ;
```

Here are the DEFINE macros:

```cpp
REG_EXTENDED
REG_ICASE
REG_NOSUB
REG_NEWLINE
REG_NOTBOL
REG_NOTEOL
REG_NOMATCH
REG_BADPAT
REG_ECOLLATE
REG_ECTYPE
REG_EESCAPE
REG_ESUBREG
REG_EBRACK
REG_EPAREN
REG_EBRACE
REG_BADBR
REG_ERANGE
REG_ESPACE
REG_BADRPT
```

And here are the new declared functions:

```cpp
int regcomp( regex_t *, char *, int ) ;
int regexec( regex_t *, char *, size_t, regmatch_t *, int ) ;
size_t regerror( int, regex_t *, char *, size_t ) ;
void regfree( regex_t * ) ;
```
