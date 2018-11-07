# socket.h

Here is the structure defined into ```socket.h``` header:

```cpp
/* socket.h prototypes */
typedef int socklen_t ;
typedef unsigned uint32_t ;
typedef unsigned short uint16_t ;

struct sockaddr {
    unsigned short  sa_family ;
    char            sa_data[14] ;
} ;
struct in_addr {
    unsigned long   s_addr ;
} ;
struct sockaddr_in {
    short           sin_family ;
    unsigned short  sin_port ;
    struct in_addr  sin_addr ;
    char            sin_zero[8] ;
} ;
struct hostent {
    char  *h_name ;
    char **h_aliases ;
    int    h_addrtype ;
    int    h_length ;
    char **h_addr_list ;
} ;
```

And here are the new declared functions:

```cpp
int accept( int sockfd, struct sockaddr *addr, socklen_t *addrlen ) ;
int bind( int sockfd, struct sockaddr *addr, socklen_t addrlen ) ;
int connect( int sockfd, struct sockaddr *addr, socklen_t addrlen ) ;
int getpeername( int sockfd, struct sockaddr *addr, socklen_t *addrlen ) ;
int getsockname( int sockfd, struct sockaddr *addr, socklen_t *addrlen ) ;
int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen ) ;
int listen( int sockfd, int backlog ) ;
ssize_t recv( int sockfd, void *buf, size_t len, int flags ) ;
ssize_t recvfrom( int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen ) ;
ssize_t send( int sockfd, void *buf, size_t len, int flags ) ;
ssize_t sendto( int sockfd, void *buf, size_t len, int flags, struct sockaddr *dest_addr, socklen_t addrlen ) ;
int setsockopt( int sockfd, int level, int optname, void *optval, socklen_t optlen ) ;
int shutdown( int sockfd, int how ) ;
int socket( int domain, int type, int protocol ) ;
uint32_t htonl( uint32_t hostlong ) ;
uint16_t htons( uint16_t hostshort ) ;
uint32_t ntohl( uint32_t netlong ) ;
uint16_t ntohs( uint16_t netshort ) ;
struct hostent * gethostbyname( char *name ) ;
struct hostent * gethostbyaddr( void *addr, socklen_t len, int type ) ;
```

Socket example with a ***simple*** TCP server, listening on port 1987, that only response one thing: the current date (very simple):

```cpp
int listenfd = 0, connfd = 0, n=0 ;
struct sockaddr_in serv_addr ; 

char sendBuff[1025] ;
char recvBuff[1025] ;
time_t ticks ;

printf( "Socket creation (socket)\n" ) ;
listenfd = socket( AF_INET, SOCK_STREAM, 0 ) ;
memset( &serv_addr, '0', sizeof( serv_addr ) ) ;
memset( sendBuff, '0', sizeof( sendBuff ) ) ; 

serv_addr.sin_family = AF_INET ;
serv_addr.sin_addr.s_addr = htonl( INADDR_ANY ) ;
serv_addr.sin_port = htons( 1987 ) ; 

printf( "Check port (Bind)\n" ) ;
bind( listenfd, (struct sockaddr*) &serv_addr, sizeof( serv_addr ) ) ; 

printf( "Start server (listen)\n" ) ;
listen( listenfd, 10 ) ; 

while(1) {
    printf ("Accept connection (accept)\n" ) ;
    connfd = accept( listenfd, (struct sockaddr*)NULL, NULL ) ; 
    printf( "Connection accepted\n" ) ;

    recv( connfd, recvBuff, sizeof(recvBuff)-1, 0 );
    printf( "Message received: %s\n", recvBuff ) ;

    ticks = time( NULL ) ;
    snprintf( sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime( &ticks ) ) ;
	
    send( connfd, sendBuff, strlen(sendBuff), 0 ) ;
    printf( "Message sent: %s\n", sendBuff ) ;

    shutdown( connfd, 2 ) ;
    close( connfd ) ;
    sleep( 1 ) ;
}
```


###  How tu use it:

1. Create a file named ```socket.pcc``` with the source code above.
1. Run the command ```pico-c -m socket.pcc```
1. Start your favorite browser on [http://localhost:1987](http://localhost:1987/) tu see the result.
