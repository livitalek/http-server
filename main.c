#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib/logging.h"
#include "lib/net.h"
#include "lib/setting_server.h"
#include "lib/methods/methods.h"
#include "lib/methods/router.h"

#define  BUFSIZE  1024
#define  LOGNAMESIZE 64

void daemonize();

int main(void) {

	//daemonize();
	initRouter(100);
	settingServer();
	pid_t pid = getpid();
	char serverLog[LOGNAMESIZE];
	sprintf(serverLog, "%s", "server.log");
    logMessage(logFile, serverLog, INFO, "%s", "Logfile created");
	logMessage(logFile, serverLog, INFO, "%s", "Demonization was successful");

	int listener = listenNet("127.0.0.1:8087");

	if (listener < 0) {

		logMessage(logFile, serverLog, ERR, "%s: Error %d", "Error when trying to switch the server state to listener mode", listener);

		return 1;

	}else {
	    logMessage(logFile, serverLog, INFO, "%s", "The server has successfully entered listener mode");
	}

	while(1) {

		int conn = acceptNet(listener);

		if (conn < 0)    continue;

		logMessage(logFile, serverLog, INFO, "%s", "Client connect");

		if (fork() == 0) {

            closeNet(listener);

           	while(1) {

          		char buffer[BUFSIZE] = {0};
				char bufferSend[100000] = {0};

          		int n = recvNet(conn, buffer, BUFSIZE);

				int connect = methods(bufferSend,buffer);
				sendNet(conn,bufferSend,100000);

          		logMessage(logFile, serverLog, INFO, "%s: %s", "Client send: ", bufferSend);

          		if (n < 0) break;

          		if (n != BUFSIZE) {
          		    logMessage(logFile, serverLog, INFO, "%s: %s", "Client recv: ", buffer);
         			break;
          		}else {
          		    logMessage(logFile, serverLog, INFO, "%s: %s", "Client recv: ", buffer, "to be continued...");
          		}

				if(connect == 0) break;
           	}

            closeNet(conn);
            break;
		}

		closeNet(conn);
		logMessage(logFile, serverLog, INFO, "%s", "Connection interrupted");
	}

	closeNet(listener);
	logMessage(logFile, serverLog, INFO, "%s", "The demon is banished");
	closeLogger(logFile);

	freeRouter();
	return 0;
}


void daemonize(){

    pid_t pid;

    pid = fork();

    if (pid < 0)exit(EXIT_FAILURE);

    if (pid > 0)exit(EXIT_SUCCESS);

    if (setsid() < 0)exit(EXIT_FAILURE);

    signal(SIGHUP, SIG_IGN);
    pid = fork();

    if (pid < 0)    exit(EXIT_FAILURE);

    if (pid > 0)    exit(EXIT_SUCCESS);

    if (chdir("/") < 0)    exit(EXIT_FAILURE);

    for (int i = 0; i < 3; i++)    close(i);

    open("/dev/null", O_RDWR); // stdin
    open("/dev/null", O_RDWR); // stdout
    open("/dev/null", O_RDWR); // stderr

}
