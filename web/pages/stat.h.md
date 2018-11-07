# stat.h

Here is the structure defined into ```stat.h``` header:

```cpp
struct stat {
    dev_t	st_dev ;
    ino_t	st_ino ;
    mode_t	st_mode ;
    short	st_nlink ;
    short	st_uid ;
    short	st_gid ;
    dev_t	st_rdev ;
    off_t	st_size ;
    time_t	st_atime ;
    time_t	st_mtime ;
    time_t	st_ctime ;
} ;
```

And here are the new declared functions:

```cpp
int stat( char * file_name, struct stat * buf ) ;
int fstat( int filedes, struct stat * buf ) ;
```
