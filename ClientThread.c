#include "ClientThread.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <cstring>
#include <cstdlib>
#include <string.h>
#include <unistd.h>

fd_set* ClientThread::master = new fd_set();
bool ClientThread::isMasterSet = false;
int ClientThread::fdmax = 0;

fd_set* ClientThread::Master()
{
	if (!isMasterSet)
	{
		isMasterSet = true;
		FD_ZERO(master);
	}

	return master;
}

ClientThread::ClientThread()
{
	address = new string();
}

void ClientThread::InternalThreadEntry()
{
	cout << "Client Thread Started" << endl;

	char buf[256];
	char returnMessage[256];
    int nbytes;
    int i, j;

	while(1) {
		cout << FD << ": Waiting for input" << endl;
        // handle data from a client
        if ((nbytes = recv(FD, buf, sizeof(buf), 0)) <= 0) 
        {
            // got error or connection closed by client
            if (nbytes == 0) {
                // connection closed
                cout << "ClientThread: socket " << FD <<" hung up" << endl;
            } else {
                perror("recv");
            }
            close(FD); // bye!
            FD_CLR(FD, ClientThread::Master()); // remove from master set
            pthread_exit(0);
        } 
        else 
        {
			//Parse the command.
			CommandKind command = _commandProcessor.parse(buf);
			
			//If valid command set default message to 200 OK
			if (command != UNKNOWN)
			{
				strcpy(returnMessage, "200 OK\n");
			}
			else
			{
				strcpy(returnMessage, "INVALID COMMAND\n");
			}

			switch(command)
			{
				case MSGGET:
					strcat(returnMessage, MessageManager::Current()->getNext());
					break;
				case MSGSTORE:
					//Check if user is logged in
					if (!UserManager::Current()->isLoggedIn(FD))
					{
						//if not logged in
						//Check the last command to set appropriate message
						switch(_commandProcessor.last_command)
						{
							case MSGSTORE:
								strcpy(returnMessage, "401 You are not currently logged in, login first.\n");
								break;
							case UNKNOWN:
								strcpy(returnMessage, "INVALID COMMAND\n");
								break;
						}
					}
					//If is logged in, store the message.
					else if (_commandProcessor.last_command == UNKNOWN)
					{
						MessageManager::Current()->store(buf);
					}
				
					break;
				case LOGIN:
					//Grab the username/password and log the user in.
					if (!UserManager::Current()->login(_commandProcessor.parameters[0].c_str(), _commandProcessor.parameters[1].c_str(), FD, address->c_str()))
					{
						strcpy(returnMessage, "401 Wrong UserID or Password\n");
					}
					break;
				case LOGOUT:
					//If the user is logged in, log them out.
					if (UserManager::Current()->isLoggedIn(FD))
					{
						UserManager::Current()->logout(FD);
					}
					break;
				case SHUTDOWN:
					//Check if the user is logged in.
					if (UserManager::Current()->isLoggedIn(FD))
					{
						User *currentUser = UserManager::Current()->getUser(FD);

						//If the user is logged in, check for root permission.
						if (currentUser->IsInRole("root"))
						{
							///Shutdown the socket and exit program.
							send(FD, returnMessage, strlen(returnMessage) + 1, 0);
						}
					}

					strcpy(returnMessage, "402 User not allowed to execute this command\n");
					break;
				case QUIT:
					//If user is logged in log then out and return 200 OK
					if (UserManager::Current()->isLoggedIn(FD))
					{
						UserManager::Current()->logout(FD);
					}
					break;
				case WHO:
					string *message;

				    message	= new string(returnMessage);
					message->append(UserManager::Current()->getUserList());

					strcpy(returnMessage, message->c_str());
					break;
				default:
					break;
			}

			//Send response to the client.
			send(FD, returnMessage, strlen(returnMessage) + 1, 0);
			cout << FD << ": " << buf;
            // we got some data from a client
            //cout << buf;
            //for(j = 0; j <= fdmax; j++) {
            //    // send to everyone!
            //    if (FD_ISSET(j, &master)) {
            //        // except the listener and ourselves
            //        if (j != listener && j != childSocket) {
            //            if (send(j, buf, nbytes, 0) == -1) {
            //                perror("send");
            //            }
            //        }
            //   }
        }
    }
}
