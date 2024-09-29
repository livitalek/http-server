#include "net.h"

static int8_t _parseAddress(char *address, char *ipv4, char *port);

int listenNet(char *address) {

	int listener = socket(AF_INET, SOCK_STREAM, 0);

	if (listener < 0)  return SOCKET_ERR;

	if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) return SETOPT_ERR;

	char ipv4[16];
	char port[6];

	if (_parseAddress(address, ipv4, port) != 0) return PARSE_ERR;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port));
	addr.sin_addr.s_addr = inet_addr(ipv4);

	if (bind(listener, (struct sockaddr*)&addr, sizeof(addr)) != 0)    return BIND_ERR;

	if (listen(listener, SOMAXCONN) != 0)  return LISTEN_ERR;

	return listener;

}

int acceptNet(int listener) {

	return accept(listener, NULL, NULL);

}

int connectNet(char *address) {

	int conn = socket(AF_INET, SOCK_STREAM, 0);

	if (conn < 0) return SOCKET_ERR;

	char ipv4[16];
	char port[6];

	if (_parseAddress(address, ipv4, port) != 0)   return PARSE_ERR;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port));
	addr.sin_addr.s_addr = inet_addr(ipv4);

	if (connect(conn, (struct sockaddr*)&addr, sizeof(addr)) != 0) return CONNECT_ERR;

	return conn;

}

int closeNet(int conn) {

	return close(conn);

}

int sendNet(int conn, char *buffer, size_t size) {

	return send(conn, buffer, (int)size, 0);

}

int recvNet(int conn, char *buffer, size_t size) {

	return recv(conn, buffer, (int)size, 0);

}

static int8_t _parseAddress(char *address, char *ipv4, char *port) {

	size_t i = 0, j = 0;

	for (; address[i] != ':'; ++i) {
	    if (address[i] == '\0')   return INCORRECT_ADDR;
		if (i >= 15)    return INCORRECT_ADDR;
		ipv4[i] = address[i];
	}

	ipv4[i] = '\0';

	for (i += 1; address[i] != '\0'; ++i, ++j) {
		if (j >= 5)   return INCORRECT_ADDR;
		port[j] = address[i];
	}

	port[j] = '\0';

	return 0;

}
