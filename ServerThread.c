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

	if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
	{
		perror("setsocketopt");
		exit(1);
	}

	//bind to address:port.
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = INADDR_ANY;
	myAddress.sin_port = htons(PORT);
	memset(&(myAddress.sin_zero), '\0', 8);

	if (bind(listener, (struct sockaddr *)&myAddress, sizeof(myAddress)) < 0)
	{
		perror("bind");
		exit(1);
	}

	FD_SET(listener, ClientThread::Master());
	ClientThread::fdmax = listener;

	//start listening
	if(listen(listener, PENDING) < 0)
	{
		perror("listen");
		exit(1);
	}

	cout << "Server is up, waiting for connections" << endl;

	addrLen = sizeof(remoteAddress);

	//main loop
	for(;;) {
		//handle a new connection
		if ((newfd = accept(listener, (struct sockaddr*)&remoteAddress, &addrLen)) < 0)
		{
			perror("accept");
			exit(1);
		} 
		else
		{
			//Add to master set
			FD_SET(newfd, ClientThread::Master());

			cout << "New connection from " 
				 << inet_ntoa(remoteAddress.sin_addr)
				 << " socket " << newfd << endl;

			//Keep track of the maximum
			if (newfd > ClientThread::fdmax)
			{
				ClientThread::fdmax = newfd;
			}

			ClientThread *clientThread = new ClientThread();
			clientThread->FD = newfd;
			clientThread->ServerFD = listener;
			clientThread->SHUT_DOWN = _thread;
			clientThread->address = new string(inet_ntoa(remoteAddress.sin_addr));

			cout << "Starting Client Thread" << endl;
			clientThread->start();
		}
	}

}
