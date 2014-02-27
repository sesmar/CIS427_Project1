#include "ServerThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void ServerThread::InternalThreadEntry()
{
	//Server Address
	struct sockaddr_in myAddress;
	//Remote Address
	struct sockaddr_in remoteAddress;

	int newfd;
	int yes=1;
	socklen_t addrLen;

	//get listener
	if ((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	//bind to address:port.
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = INADDR_ANY;
	myAddress.sin_port = htons(_port);
	memset(&(myAddress.sin_zero), '\0', 8);

	if (bind(listener, (struct sockaddr *)&myAddress, sizeof(myAddress)) < 0)
	{
		perror("bind");
		exit(1);
	}

	//start listening
	if(listen(listener, _maxPending) < 0)
	{
		perror("listen");
		exit(1);
	}
}
