/*
 * server.c
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include "ServerThread.h"

using namespace std;

#define SERVER_PORT 34352
#define MAX_PENDING 10
#define MAX_LINE 256

//Master file descriptor
fd_set master;

int main(int argc, char **argv) {
	//load the message from file.
	MessageManager::Current()->load("messages.txt");

	ServerThread serverThread;
	
	serverThread.PORT = SERVER_PORT;
	serverThread.PENDING = MAX_PENDING;

	serverThread.start();
	serverThread.wait();
}
