#include "../interpreter.h"

#ifdef WIN32
#include <winsock.h>
#include <unistd.h>
#ifndef T_SOCKLEN_T
#define T_SOCKLEN_T
typedef int socklen_t;
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <sys/time.h>
#include <arpa/inet.h>
#endif

/* Equivalent des #define NAME VALUE */
#ifdef WIN32
static int SD_RECEIVEValue = SD_RECEIVE ;
static int SD_SENDValue = SD_SEND ;
static int SD_BOTHValue = SD_BOTH ;
static int IOCPARM_MASKValue = IOCPARM_MASK ;
static int IOC_VOIDValue = IOC_VOID ;
static int IOC_OUTValue = IOC_OUT ;
static int IOC_INValue = IOC_IN ;
static int IPPROTO_GGPValue = IPPROTO_GGP ;
static int IPPROTO_NDValue = IPPROTO_ND ;
static int IMPLINK_IPValue = IMPLINK_IP ;
static int FD_READValue = FD_READ ;
static int FD_WRITEValue = FD_WRITE ;
static int FD_OOBValue = FD_OOB ;
static int FD_ACCEPTValue = FD_ACCEPT ;
static int FD_CONNECTValue = FD_CONNECT ;
static int FD_CLOSEValue = FD_CLOSE ;
static int MSG_MAXIOVLENValue = MSG_MAXIOVLEN ;
static int MSG_PARTIALValue = MSG_PARTIAL ;
static int MAXGETHOSTSTRUCTValue = MAXGETHOSTSTRUCT ;
static int WSABASEERRValue = WSABASEERR ;
static int WSANO_ADDRESSValue = WSANO_ADDRESS ;
static int PF_VOICEVIEWValue = PF_VOICEVIEW ;
static int PF_FIREFOXValue = PF_FIREFOX ;
static int PF_UNKNOWN1Value = PF_UNKNOWN1 ;
static int PF_BANValue = PF_BAN ;
static int PF_ATMValue = PF_ATM ;
static int PF_LATValue = PF_LAT ;
static int PF_HYLINKValue = PF_HYLINK ;
static int PF_ISOValue = PF_ISO ;
static int PF_OSIValue = PF_OSI ;
static int PF_ECMAValue = PF_ECMA ;
static int PF_DATAKITValue = PF_DATAKIT ;
static int PF_CCITTValue = PF_CCITT ;
static int PF_DLIValue = PF_DLI ;
static int PF_PUPValue = PF_PUP ;
static int PF_CHAOSValue = PF_CHAOS ;
static int PF_NSValue = PF_NS ;
static int AF_DLIValue = AF_DLI ;
static int AF_LATValue = AF_LAT ;
static int AF_HYLINKValue = AF_HYLINK ;
static int AF_NETBIOSValue = AF_NETBIOS ;
static int AF_VOICEVIEWValue = AF_VOICEVIEW ;
static int AF_ATMValue = AF_ATM ;
static int PF_IMPLINKValue = PF_IMPLINK ;
static int AF_DATAKITValue = AF_DATAKIT ;
static int AF_CCITTValue = AF_CCITT ;
static int AF_IMPLINKValue = AF_IMPLINK ;
static int AF_PUPValue = AF_PUP ;
static int AF_CHAOSValue = AF_CHAOS ;
static int AF_NSValue = AF_NS ;
static int AF_ISOValue = AF_ISO ;
static int AF_OSIValue = AF_OSI ;
static int AF_ECMAValue = AF_ECMA ;
static int IMPLINK_LOWEXPERValue = IMPLINK_LOWEXPER ;
static int IMPLINK_HIGHEXPERValue = IMPLINK_HIGHEXPER ;
static int WSADESCRIPTION_LENValue = WSADESCRIPTION_LEN ;
static int WSASYS_STATUS_LENValue = WSASYS_STATUS_LEN ;
static int SO_USELOOPBACKValue = SO_USELOOPBACK ;
#endif
#ifndef AIX_HOST
static int IPPORT_ECHOValue = IPPORT_ECHO ;
static int IPPORT_DISCARDValue = IPPORT_DISCARD ;
static int IPPORT_SYSTATValue = IPPORT_SYSTAT ;
static int IPPORT_DAYTIMEValue = IPPORT_DAYTIME ;
static int IPPORT_NETSTATValue = IPPORT_NETSTAT ;
static int IPPORT_FTPValue = IPPORT_FTP ;
static int IPPORT_TELNETValue = IPPORT_TELNET ;
static int IPPORT_SMTPValue = IPPORT_SMTP ;
static int IPPORT_NAMESERVERValue = IPPORT_NAMESERVER ;
static int IPPORT_WHOISValue = IPPORT_WHOIS ;
static int IPPORT_MTPValue = IPPORT_MTP ;
static int IPPORT_TFTPValue = IPPORT_TFTP ;
static int IPPORT_RJEValue = IPPORT_RJE ;
static int IPPORT_FINGERValue = IPPORT_FINGER ;
static int IPPORT_TTYLINKValue = IPPORT_TTYLINK ;
static int IPPORT_SUPDUPValue = IPPORT_SUPDUP ;
static int IPPORT_EXECSERVERValue = IPPORT_EXECSERVER ;
static int IPPORT_LOGINSERVERValue = IPPORT_LOGINSERVER ;
static int IPPORT_CMDSERVERValue = IPPORT_CMDSERVER ;
static int IPPORT_EFSSERVERValue = IPPORT_EFSSERVER ;
static int IPPORT_BIFFUDPValue = IPPORT_BIFFUDP ;
static int IPPORT_WHOSERVERValue = IPPORT_WHOSERVER ;
static int IPPORT_ROUTESERVERValue = IPPORT_ROUTESERVER ;
static int IP_MAX_MEMBERSHIPSValue = IP_MAX_MEMBERSHIPS ;
static int AF_IPXValue = AF_IPX ;
static int PF_IPXValue = PF_IPX ;
#endif
static int FD_SETSIZEValue = FD_SETSIZE ;
static int IPPROTO_IPValue = IPPROTO_IP ;
static int IPPROTO_ICMPValue = IPPROTO_ICMP ;
static int IPPROTO_IGMPValue = IPPROTO_IGMP ;
static int IPPROTO_TCPValue = IPPROTO_TCP ;
static int IPPROTO_PUPValue = IPPROTO_PUP ;
static int IPPROTO_UDPValue = IPPROTO_UDP ;
static int IPPROTO_IDPValue = IPPROTO_IDP ;
static int IPPROTO_RAWValue = IPPROTO_RAW ;
static int IPPROTO_MAXValue = IPPROTO_MAX ;
static int IPPORT_TIMESERVERValue = IPPORT_TIMESERVER ;
static int IPPORT_RESERVEDValue = IPPORT_RESERVED ;
static int IN_CLASSA_NETValue = IN_CLASSA_NET ;
static int IN_CLASSA_NSHIFTValue = IN_CLASSA_NSHIFT ;
static int IN_CLASSA_HOSTValue = IN_CLASSA_HOST ;
static int IN_CLASSA_MAXValue = IN_CLASSA_MAX ;
static int IN_CLASSB_NETValue = IN_CLASSB_NET ;
static int IN_CLASSB_NSHIFTValue = IN_CLASSB_NSHIFT ;
static int IN_CLASSB_HOSTValue = IN_CLASSB_HOST ;
static int IN_CLASSB_MAXValue = IN_CLASSB_MAX ;
static int IN_CLASSC_NETValue = IN_CLASSC_NET ;
static int IN_CLASSC_NSHIFTValue = IN_CLASSC_NSHIFT ;
static int IN_CLASSC_HOSTValue = IN_CLASSC_HOST ;
static int INADDR_ANYValue = INADDR_ANY ;
static int INADDR_LOOPBACKValue = INADDR_LOOPBACK ;
static int INADDR_NONEValue = INADDR_NONE ;
static int IP_OPTIONSValue = IP_OPTIONS ;
static int SO_DEBUGValue = SO_DEBUG ;
static int SO_ACCEPTCONNValue = SO_ACCEPTCONN ;
static int SO_REUSEADDRValue = SO_REUSEADDR ;
static int SO_KEEPALIVEValue = SO_KEEPALIVE ;
static int SO_DONTROUTEValue = SO_DONTROUTE ;
static int SO_BROADCASTValue = SO_BROADCAST ;
static int SO_LINGERValue = SO_LINGER ;
static int SO_OOBINLINEValue = SO_OOBINLINE ;
static int SO_SNDBUFValue = SO_SNDBUF ;
static int SO_RCVBUFValue = SO_RCVBUF ;
static int SO_SNDLOWATValue = SO_SNDLOWAT ;
static int SO_RCVLOWATValue = SO_RCVLOWAT ;
static int SO_SNDTIMEOValue = SO_SNDTIMEO ;
static int SO_RCVTIMEOValue = SO_RCVTIMEO ;
static int SO_ERRORValue = SO_ERROR ;
static int SO_TYPEValue = SO_TYPE ;
static int IP_MULTICAST_IFValue = IP_MULTICAST_IF ;
static int IP_MULTICAST_TTLValue = IP_MULTICAST_TTL ;
static int IP_MULTICAST_LOOPValue = IP_MULTICAST_LOOP ;
static int IP_ADD_MEMBERSHIPValue = IP_ADD_MEMBERSHIP ;
static int IP_DROP_MEMBERSHIPValue = IP_DROP_MEMBERSHIP ;
static int IP_DEFAULT_MULTICAST_TTLValue = IP_DEFAULT_MULTICAST_TTL ;
static int IP_DEFAULT_MULTICAST_LOOPValue = IP_DEFAULT_MULTICAST_LOOP ;
static int SOCK_STREAMValue = SOCK_STREAM ;
static int SOCK_DGRAMValue = SOCK_DGRAM ;
static int SOCK_RAWValue = SOCK_RAW ;
static int SOCK_RDMValue = SOCK_RDM ;
static int SOCK_SEQPACKETValue = SOCK_SEQPACKET ;
static int TCP_NODELAYValue = TCP_NODELAY ;
static int AF_UNSPECValue = AF_UNSPEC ;
static int AF_UNIXValue = AF_UNIX ;
static int AF_INETValue = AF_INET ;
static int AF_SNAValue = AF_SNA ;
static int AF_DECnetValue = AF_DECnet ;
static int AF_APPLETALKValue = AF_APPLETALK ;
static int AF_INET6Value = AF_INET6 ;
static int AF_MAXValue = AF_MAX ;
static int PF_UNSPECValue = PF_UNSPEC ;
static int PF_UNIXValue = PF_UNIX ;
static int PF_INETValue = PF_INET ;
static int PF_SNAValue = PF_SNA ;
static int PF_DECnetValue = PF_DECnet ;
static int PF_APPLETALKValue = PF_APPLETALK ;
static int PF_INET6Value = PF_INET6 ;
static int PF_MAXValue = PF_MAX ;
static int SOL_SOCKETValue = SOL_SOCKET ;
static int SOMAXCONNValue = SOMAXCONN ;
static int MSG_OOBValue = MSG_OOB ;
static int MSG_PEEKValue = MSG_PEEK ;
static int MSG_DONTROUTEValue = MSG_DONTROUTE ;
static int HOST_NOT_FOUNDValue = HOST_NOT_FOUND ;
static int TRY_AGAINValue = TRY_AGAIN ;
static int NO_RECOVERYValue = NO_RECOVERY ;
static int NO_DATAValue = NO_DATA ;
static int NO_ADDRESSValue = NO_ADDRESS ;
static int SHUT_RDValue = 0 ;
static int SHUT_WRValue = 1 ;
static int SHUT_RDWRValue = 2 ;

void SocketAccept(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = accept( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Pointer );
}

void SocketBind(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = bind( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer );
}

void SocketConnect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = connect( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer );
}

void SocketGetpeername(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = getpeername( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Pointer );
}

void SocketGetsockname(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = getsockname( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Pointer );
}

void SocketGetsockopt(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = getsockopt( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Pointer, Param[4]->Val->Pointer );
}

void SocketListen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = listen( Param[0]->Val->Integer, Param[1]->Val->Integer );
}

void SocketRecv(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = recv( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Integer );
}

void SocketRecvfrom(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = recvfrom( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Integer, Param[4]->Val->Pointer, Param[5]->Val->Pointer );
}

/*
void SocketRead(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = read( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer );
}
*/

void SocketSend(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = send( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Integer );
}

void SocketSendto(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = sendto( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer, Param[3]->Val->Integer, Param[4]->Val->Pointer, Param[5]->Val->Integer );
}

void SocketSetsockopt(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = setsockopt( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Pointer, Param[4]->Val->Integer );
}

void SocketShutdown(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = shutdown( Param[0]->Val->Integer, Param[1]->Val->Integer );
}

void SocketSocket(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = socket( Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer );
}

/*
void SocketWrite(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = write( Param[0]->Val->Integer, Param[1]->Val->Pointer, Param[2]->Val->Integer );
}
*/

void SocketHtonl(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = htonl( Param[0]->Val->Integer ) ;
}

void SocketHtons(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = htons( Param[0]->Val->Integer ) ;
}

void SocketNtohl(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = ntohl( Param[0]->Val->Integer ) ;
}

void SocketNtohs(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = ntohs( Param[0]->Val->Integer ) ;
}

void SocketGethostbyname(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = gethostbyname( Param[0]->Val->Pointer ) ;
}

void SocketGethostbyaddr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = gethostbyaddr( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer ) ;
}

/*
void SocketInet_addr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = inet_addr( Param[0]->Val->Pointer ) ;
}

void SocketInet_aton(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = inet_aton( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}

void SocketInet_network(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = inet_network( Param[0]->Val->Pointer ) ;
}
void SocketInet_ntoa(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = inet_ntoa( Param[0]->Val->Pointer ) ;
}

void SocketInet_makeaddr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = inet_makeaddr( Param[0]->Val->Integer, Param[1]->Val->Integer ) ;
}
*/

/* handy structure definitions */
const char SocketDefs[] = "\
typedef int socklen_t;\n\
typedef unsigned uint32_t;\n\
typedef unsigned short uint16_t;\n\
struct sockaddr {\n\
	unsigned short	sa_family;\n\
	char		sa_data[14];\n\
};\n\
struct in_addr {\n\
	unsigned long	s_addr;\n\
};\n\
struct sockaddr_in {\n\
	short		sin_family;\n\
	unsigned short	sin_port;\n\
	struct in_addr	sin_addr;\n\
	char		sin_zero[8];\n\
};\n\
struct hostent {\n\
	char  *h_name;\n\
	char **h_aliases;\n\
	int    h_addrtype;\n\
	int    h_length;\n\
	char **h_addr_list;\n\
};\n\
";

/* all various.h functions */
struct LibraryFunction SocketFunctions[] =
{
    { SocketAccept,    	    "int accept( int sockfd, struct sockaddr *addr, socklen_t *addrlen ) ;" },
    { SocketBind,    	    "int bind( int sockfd, struct sockaddr *addr, socklen_t addrlen ) ;" },
    { SocketConnect,        "int connect( int sockfd, struct sockaddr *addr, socklen_t addrlen ) ;" },
    { SocketGetpeername,    "int getpeername( int sockfd, struct sockaddr *addr, socklen_t *addrlen ) ;" },
    { SocketGetsockname,    "int getsockname( int sockfd, struct sockaddr *addr, socklen_t *addrlen ) ;" },
    { SocketGetsockopt,     "int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen ) ;" },
    { SocketListen,         "int listen( int sockfd, int backlog ) ; " },
    { SocketRecv,           "ssize_t recv( int sockfd, void *buf, size_t len, int flags ) ;" },
    { SocketRecvfrom,       "ssize_t recvfrom( int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen ) ;" },
/*    { SocketRead,           "ssize_t read( int fd, void *buf, size_t count ) ;" },   DEFINI DANS cstdlib/unistd.c */
    { SocketSend,           "ssize_t send( int sockfd, void *buf, size_t len, int flags ) ;" },
    { SocketSendto,         "ssize_t sendto( int sockfd, void *buf, size_t len, int flags, struct sockaddr *dest_addr, socklen_t addrlen ) ;" },
    { SocketSetsockopt,     "int setsockopt( int sockfd, int level, int optname, void *optval, socklen_t optlen ) ;" },
    { SocketShutdown,       "int shutdown( int sockfd, int how ) ;" },
    { SocketSocket,         "int socket( int domain, int type, int protocol ) ;" },
/*    {SocketWrite,           "ssize_t write( int fd, void *buf, size_t count ) ;" },   DEFINI DANS cstdlib/unistd.c */
    { SocketHtonl,          "uint32_t htonl( uint32_t hostlong ) ;" },
    { SocketHtons,          "uint16_t htons( uint16_t hostshort ) ;" },
    { SocketNtohl,          "uint32_t ntohl( uint32_t netlong ) ;" },
    { SocketNtohs,          "uint16_t ntohs( uint16_t netshort ) ;" },
    { SocketGethostbyname,  "struct hostent * gethostbyname( char *name ) ;" },
    { SocketGethostbyaddr,  "struct hostent * gethostbyaddr( void *addr, socklen_t len, int type ) ;" },
    { NULL,                 NULL }
};

/* POUR INFORMATION
tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
raw_socket = socket(AF_INET, SOCK_RAW, protocol);
*/

/* NON IMPLEMENTEE */
/*
#include <fcntl.h>
int fcntl(int fd, int cmd, ... ) ;

#include <sys/ioctl.h>
int ioctl(int fd, unsigned long request, ...) ;

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

int socketpair( int domain, int type, int protocol, int sv[2] ) ;

#include <netdb.h>
struct protoent *getprotoent(void);
struct protoent *getprotobyname(const char *name);
struct protoent *getprotobynumber(int proto);
void setprotoent(int stayopen);
void endprotoent(void);

{ SocketInet_addr,      "unsigned long int inet_addr( char *cp ) ;" },
{ SocketInet_aton,      "int inet_aton( char *cp, struct in_addr *inp ) ;" },
{ SocketInet_network,   "unsigned long int inet_network( char *cp ) ;" },
char *inet_ntoa (struct in_addr in);
struct in_addr inet_makeaddr (int net, int host);
unsigned long int inet_lnaof (struct in_addr in);
unsigned long int inet_netof (struct in_addr in);
*/

/* creates various system-dependent definitions */
void SocketSetupFunc(Picoc *pc)
{
#ifdef WIN32
	WSADATA WSAData;
	if( WSAStartup( MAKEWORD( 2, 2 ), &WSAData ) ) { 
		fprintf( stderr, "unable to start winsock !\n" ) ;
	}
#endif
	
	/* define definitions */

#ifdef WIN32
VariableDefinePlatformVar(pc, NULL, "SD_RECEIVE", &pc->IntType, (union AnyValue *)&SD_RECEIVEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SD_SEND", &pc->IntType, (union AnyValue *)&SD_SENDValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SD_BOTH", &pc->IntType, (union AnyValue *)&SD_BOTHValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IOCPARM_MASK", &pc->IntType, (union AnyValue *)&IOCPARM_MASKValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IOC_VOID", &pc->IntType, (union AnyValue *)&IOC_VOIDValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IOC_OUT", &pc->IntType, (union AnyValue *)&IOC_OUTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IOC_IN", &pc->IntType, (union AnyValue *)&IOC_INValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_GGP", &pc->IntType, (union AnyValue *)&IPPROTO_GGPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_ND", &pc->IntType, (union AnyValue *)&IPPROTO_NDValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IMPLINK_IP", &pc->IntType, (union AnyValue *)&IMPLINK_IPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "FD_READ", &pc->IntType, (union AnyValue *)&FD_READValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "FD_WRITE", &pc->IntType, (union AnyValue *)&FD_WRITEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "FD_OOB", &pc->IntType, (union AnyValue *)&FD_OOBValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "FD_ACCEPT", &pc->IntType, (union AnyValue *)&FD_ACCEPTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "FD_CONNECT", &pc->IntType, (union AnyValue *)&FD_CONNECTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "FD_CLOSE", &pc->IntType, (union AnyValue *)&FD_CLOSEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "MSG_MAXIOVLEN", &pc->IntType, (union AnyValue *)&MSG_MAXIOVLENValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "MSG_PARTIAL", &pc->IntType, (union AnyValue *)&MSG_PARTIALValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "MAXGETHOSTSTRUCT", &pc->IntType, (union AnyValue *)&MAXGETHOSTSTRUCTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "WSABASEERR", &pc->IntType, (union AnyValue *)&WSABASEERRValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "WSANO_ADDRESS", &pc->IntType, (union AnyValue *)&WSANO_ADDRESSValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_VOICEVIEW", &pc->IntType, (union AnyValue *)&PF_VOICEVIEWValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_FIREFOX", &pc->IntType, (union AnyValue *)&PF_FIREFOXValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_UNKNOWN1", &pc->IntType, (union AnyValue *)&PF_UNKNOWN1Value, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_BAN", &pc->IntType, (union AnyValue *)&PF_BANValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_ATM", &pc->IntType, (union AnyValue *)&PF_ATMValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_LAT", &pc->IntType, (union AnyValue *)&PF_LATValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_HYLINK", &pc->IntType, (union AnyValue *)&PF_HYLINKValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_ISO", &pc->IntType, (union AnyValue *)&PF_ISOValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_OSI", &pc->IntType, (union AnyValue *)&PF_OSIValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_ECMA", &pc->IntType, (union AnyValue *)&PF_ECMAValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_DATAKIT", &pc->IntType, (union AnyValue *)&PF_DATAKITValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_CCITT", &pc->IntType, (union AnyValue *)&PF_CCITTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_DLI", &pc->IntType, (union AnyValue *)&PF_DLIValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_PUP", &pc->IntType, (union AnyValue *)&PF_PUPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_CHAOS", &pc->IntType, (union AnyValue *)&PF_CHAOSValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_NS", &pc->IntType, (union AnyValue *)&PF_NSValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_DLI", &pc->IntType, (union AnyValue *)&AF_DLIValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_LAT", &pc->IntType, (union AnyValue *)&AF_LATValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_HYLINK", &pc->IntType, (union AnyValue *)&AF_HYLINKValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_NETBIOS", &pc->IntType, (union AnyValue *)&AF_NETBIOSValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_VOICEVIEW", &pc->IntType, (union AnyValue *)&AF_VOICEVIEWValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_ATM", &pc->IntType, (union AnyValue *)&AF_ATMValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_IMPLINK", &pc->IntType, (union AnyValue *)&PF_IMPLINKValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_DATAKIT", &pc->IntType, (union AnyValue *)&AF_DATAKITValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_CCITT", &pc->IntType, (union AnyValue *)&AF_CCITTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_IMPLINK", &pc->IntType, (union AnyValue *)&AF_IMPLINKValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_PUP", &pc->IntType, (union AnyValue *)&AF_PUPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_CHAOS", &pc->IntType, (union AnyValue *)&AF_CHAOSValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_NS", &pc->IntType, (union AnyValue *)&AF_NSValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_ISO", &pc->IntType, (union AnyValue *)&AF_ISOValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_OSI", &pc->IntType, (union AnyValue *)&AF_OSIValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_ECMA", &pc->IntType, (union AnyValue *)&AF_ECMAValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IMPLINK_LOWEXPER", &pc->IntType, (union AnyValue *)&IMPLINK_LOWEXPERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IMPLINK_HIGHEXPER", &pc->IntType, (union AnyValue *)&IMPLINK_HIGHEXPERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "WSADESCRIPTION_LEN", &pc->IntType, (union AnyValue *)&WSADESCRIPTION_LENValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "WSASYS_STATUS_LEN", &pc->IntType, (union AnyValue *)&WSASYS_STATUS_LENValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_USELOOPBACK", &pc->IntType, (union AnyValue *)&SO_USELOOPBACKValue,FALSE) ;
#endif	
#ifndef AIX_HOST
VariableDefinePlatformVar(pc, NULL, "IPPORT_DISCARD", &pc->IntType, (union AnyValue *)&IPPORT_DISCARDValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_SYSTAT", &pc->IntType, (union AnyValue *)&IPPORT_SYSTATValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_DAYTIME", &pc->IntType, (union AnyValue *)&IPPORT_DAYTIMEValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_NETSTAT", &pc->IntType, (union AnyValue *)&IPPORT_NETSTATValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_FTP", &pc->IntType, (union AnyValue *)&IPPORT_FTPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_TELNET", &pc->IntType, (union AnyValue *)&IPPORT_TELNETValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_SMTP", &pc->IntType, (union AnyValue *)&IPPORT_SMTPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_NAMESERVER", &pc->IntType, (union AnyValue *)&IPPORT_NAMESERVERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_WHOIS", &pc->IntType, (union AnyValue *)&IPPORT_WHOISValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_MTP", &pc->IntType, (union AnyValue *)&IPPORT_MTPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_TFTP", &pc->IntType, (union AnyValue *)&IPPORT_TFTPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_RJE", &pc->IntType, (union AnyValue *)&IPPORT_RJEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_FINGER", &pc->IntType, (union AnyValue *)&IPPORT_FINGERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_TTYLINK", &pc->IntType, (union AnyValue *)&IPPORT_TTYLINKValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_SUPDUP", &pc->IntType, (union AnyValue *)&IPPORT_SUPDUPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_EXECSERVER", &pc->IntType, (union AnyValue *)&IPPORT_EXECSERVERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_LOGINSERVER", &pc->IntType, (union AnyValue *)&IPPORT_LOGINSERVERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_CMDSERVER", &pc->IntType, (union AnyValue *)&IPPORT_CMDSERVERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_EFSSERVER", &pc->IntType, (union AnyValue *)&IPPORT_EFSSERVERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_BIFFUDP", &pc->IntType, (union AnyValue *)&IPPORT_BIFFUDPValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_WHOSERVER", &pc->IntType, (union AnyValue *)&IPPORT_WHOSERVERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_ECHO", &pc->IntType, (union AnyValue *)&IPPORT_ECHOValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_ROUTESERVER", &pc->IntType, (union AnyValue *)&IPPORT_ROUTESERVERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IP_MAX_MEMBERSHIPS", &pc->IntType, (union AnyValue *)&IP_MAX_MEMBERSHIPSValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_IPX", &pc->IntType, (union AnyValue *)&AF_IPXValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_IPX", &pc->IntType, (union AnyValue *)&PF_IPXValue, FALSE) ;
#endif
VariableDefinePlatformVar(pc, NULL, "FD_SETSIZE", &pc->IntType, (union AnyValue *)&FD_SETSIZEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_IP", &pc->IntType, (union AnyValue *)&IPPROTO_IPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_ICMP", &pc->IntType, (union AnyValue *)&IPPROTO_ICMPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_IGMP", &pc->IntType, (union AnyValue *)&IPPROTO_IGMPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_TCP", &pc->IntType, (union AnyValue *)&IPPROTO_TCPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_PUP", &pc->IntType, (union AnyValue *)&IPPROTO_PUPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_UDP", &pc->IntType, (union AnyValue *)&IPPROTO_UDPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_IDP", &pc->IntType, (union AnyValue *)&IPPROTO_IDPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_RAW", &pc->IntType, (union AnyValue *)&IPPROTO_RAWValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPROTO_MAX", &pc->IntType, (union AnyValue *)&IPPROTO_MAXValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_TIMESERVER", &pc->IntType, (union AnyValue *)&IPPORT_TIMESERVERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IPPORT_RESERVED", &pc->IntType, (union AnyValue *)&IPPORT_RESERVEDValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSA_NET", &pc->IntType, (union AnyValue *)&IN_CLASSA_NETValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSA_NSHIFT", &pc->IntType, (union AnyValue *)&IN_CLASSA_NSHIFTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSA_HOST", &pc->IntType, (union AnyValue *)&IN_CLASSA_HOSTValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSA_MAX", &pc->IntType, (union AnyValue *)&IN_CLASSA_MAXValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSB_NET", &pc->IntType, (union AnyValue *)&IN_CLASSB_NETValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSB_NSHIFT", &pc->IntType, (union AnyValue *)&IN_CLASSB_NSHIFTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSB_HOST", &pc->IntType, (union AnyValue *)&IN_CLASSB_HOSTValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSB_MAX", &pc->IntType, (union AnyValue *)&IN_CLASSB_MAXValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSC_NET", &pc->IntType, (union AnyValue *)&IN_CLASSC_NETValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSC_NSHIFT", &pc->IntType, (union AnyValue *)&IN_CLASSC_NSHIFTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IN_CLASSC_HOST", &pc->IntType, (union AnyValue *)&IN_CLASSC_HOSTValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "INADDR_ANY", &pc->IntType, (union AnyValue *)&INADDR_ANYValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "INADDR_LOOPBACK", &pc->IntType, (union AnyValue *)&INADDR_LOOPBACKValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "INADDR_NONE", &pc->IntType, (union AnyValue *)&INADDR_NONEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IP_OPTIONS", &pc->IntType, (union AnyValue *)&IP_OPTIONSValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_DEBUG", &pc->IntType, (union AnyValue *)&SO_DEBUGValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_ACCEPTCONN", &pc->IntType, (union AnyValue *)&SO_ACCEPTCONNValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_REUSEADDR", &pc->IntType, (union AnyValue *)&SO_REUSEADDRValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_KEEPALIVE", &pc->IntType, (union AnyValue *)&SO_KEEPALIVEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_DONTROUTE", &pc->IntType, (union AnyValue *)&SO_DONTROUTEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_BROADCAST", &pc->IntType, (union AnyValue *)&SO_BROADCASTValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_LINGER", &pc->IntType, (union AnyValue *)&SO_LINGERValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_OOBINLINE", &pc->IntType, (union AnyValue *)&SO_OOBINLINEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_SNDBUF", &pc->IntType, (union AnyValue *)&SO_SNDBUFValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_RCVBUF", &pc->IntType, (union AnyValue *)&SO_RCVBUFValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_SNDLOWAT", &pc->IntType, (union AnyValue *)&SO_SNDLOWATValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_RCVLOWAT", &pc->IntType, (union AnyValue *)&SO_RCVLOWATValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_SNDTIMEO", &pc->IntType, (union AnyValue *)&SO_SNDTIMEOValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_RCVTIMEO", &pc->IntType, (union AnyValue *)&SO_RCVTIMEOValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_ERROR", &pc->IntType, (union AnyValue *)&SO_ERRORValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SO_TYPE", &pc->IntType, (union AnyValue *)&SO_TYPEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IP_MULTICAST_IF", &pc->IntType, (union AnyValue *)&IP_MULTICAST_IFValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IP_MULTICAST_TTL", &pc->IntType, (union AnyValue *)&IP_MULTICAST_TTLValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IP_MULTICAST_LOOP", &pc->IntType, (union AnyValue *)&IP_MULTICAST_LOOPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IP_ADD_MEMBERSHIP", &pc->IntType, (union AnyValue *)&IP_ADD_MEMBERSHIPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IP_DROP_MEMBERSHIP", &pc->IntType, (union AnyValue *)&IP_DROP_MEMBERSHIPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IP_DEFAULT_MULTICAST_TTL", &pc->IntType, (union AnyValue *)&IP_DEFAULT_MULTICAST_TTLValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "IP_DEFAULT_MULTICAST_LOOP", &pc->IntType, (union AnyValue *)&IP_DEFAULT_MULTICAST_LOOPValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SOCK_STREAM", &pc->IntType, (union AnyValue *)&SOCK_STREAMValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SOCK_DGRAM", &pc->IntType, (union AnyValue *)&SOCK_DGRAMValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SOCK_RAW", &pc->IntType, (union AnyValue *)&SOCK_RAWValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SOCK_RDM", &pc->IntType, (union AnyValue *)&SOCK_RDMValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SOCK_SEQPACKET", &pc->IntType, (union AnyValue *)&SOCK_SEQPACKETValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "TCP_NODELAY", &pc->IntType, (union AnyValue *)&TCP_NODELAYValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_UNSPEC", &pc->IntType, (union AnyValue *)&AF_UNSPECValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_UNIX", &pc->IntType, (union AnyValue *)&AF_UNIXValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_INET", &pc->IntType, (union AnyValue *)&AF_INETValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_SNA", &pc->IntType, (union AnyValue *)&AF_SNAValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_DECnet", &pc->IntType, (union AnyValue *)&AF_DECnetValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_APPLETALK", &pc->IntType, (union AnyValue *)&AF_APPLETALKValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_INET6", &pc->IntType, (union AnyValue *)&AF_INET6Value, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "AF_MAX", &pc->IntType, (union AnyValue *)&AF_MAXValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_UNSPEC", &pc->IntType, (union AnyValue *)&PF_UNSPECValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_UNIX", &pc->IntType, (union AnyValue *)&PF_UNIXValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_INET", &pc->IntType, (union AnyValue *)&PF_INETValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_SNA", &pc->IntType, (union AnyValue *)&PF_SNAValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_DECnet", &pc->IntType, (union AnyValue *)&PF_DECnetValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_APPLETALK", &pc->IntType, (union AnyValue *)&PF_APPLETALKValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_INET6", &pc->IntType, (union AnyValue *)&PF_INET6Value, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "PF_MAX", &pc->IntType, (union AnyValue *)&PF_MAXValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SOL_SOCKET", &pc->IntType, (union AnyValue *)&SOL_SOCKETValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SOMAXCONN", &pc->IntType, (union AnyValue *)&SOMAXCONNValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "MSG_OOB", &pc->IntType, (union AnyValue *)&MSG_OOBValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "MSG_PEEK", &pc->IntType, (union AnyValue *)&MSG_PEEKValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "MSG_DONTROUTE", &pc->IntType, (union AnyValue *)&MSG_DONTROUTEValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "HOST_NOT_FOUND", &pc->IntType, (union AnyValue *)&HOST_NOT_FOUNDValue,FALSE) ;
VariableDefinePlatformVar(pc, NULL, "TRY_AGAIN", &pc->IntType, (union AnyValue *)&TRY_AGAINValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "NO_RECOVERY", &pc->IntType, (union AnyValue *)&NO_RECOVERYValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "NO_DATA", &pc->IntType, (union AnyValue *)&NO_DATAValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "NO_ADDRESS", &pc->IntType, (union AnyValue *)&NO_ADDRESSValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SHUT_RD", &pc->IntType, (union AnyValue *)&SHUT_RDValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SHUT_WR", &pc->IntType, (union AnyValue *)&SHUT_WRValue, FALSE) ;
VariableDefinePlatformVar(pc, NULL, "SHUT_RDWR", &pc->IntType, (union AnyValue *)&SHUT_RDWRValue, FALSE) ;
}
