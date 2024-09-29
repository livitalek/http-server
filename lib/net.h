#ifndef __EXTCLIB_NET_H
#define __EXTCLIB_NET_H

#include <stddef.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "logging.h"

typedef enum errorT {
	WINSOCK_ERR = -1,
	SOCKET_ERR  = -2,
	SETOPT_ERR  = -3,
	PARSE_ERR   = -4,
	BIND_ERR    = -5,
	LISTEN_ERR  = -6,
	CONNECT_ERR = -7,
	INCORRECT_ADDR = -8,
} errorT;

extern int listenNet(char *address);
extern int acceptNet(int listener);

extern int connectNet(char *address);
extern int closeNet(int conn);

extern int sendNet(int conn, char *buffer, size_t size);
extern int recvNet(int conn, char *buffer, size_t size);


#endif /* __EXTCLIB_NET_H */
