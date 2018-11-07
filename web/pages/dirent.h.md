# dirent.h

Here is the structure defined into ```dirent.h``` header:

```cpp
struct dirent {
    ino_t          d_ino ;       /* inode number */
    off_t          d_off ;       /* offset to the next dirent */
    unsigned short d_reclen ;    /* length of this record */
    unsigned char  d_type ;      /* type of file; not supported by all file system types */
    char           d_name[256] ; /* filename */
} ;
```

And here are the new declared functions:

```cpp
DIR *opendir( char * name ) ;
int closedir( DIR * dirp ) ;
struct dirent * readdir( DIR * dirp ) ;
void rewinddir( DIR * dirp ) ;
long telldir( DIR * dirp ) ;
void seekdir( DIR * dirp, long offset ) ;
char * dirent_getname( struct dirent * dp ) ;
```
