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
#include "MessageManager.h"
#include "CommandProcessor.h"
#include "UserManager.h"

using namespace std;

#define SERVER_PORT 34352
#define MAX_PENDING 5
#define MAX_LINE 256

int main(int argc, char **argv) {

    struct sockaddr_in sin;
    socklen_t addrlen;
    char buf[MAX_LINE];
    char returnMessage[MAX_LINE];
    int len;
    int s;
    int new_s;
    MessageManager messageManager;
    CommandProcessor commandProcessor;
    UserManager userManager;

    messageManager.load("messages.txt");

    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons (SERVER_PORT);

    /* setup passive open */
    if (( s = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
    }

    if ((bind(s, (struct sockaddr *) &sin, sizeof(sin))) < 0) {
		perror("bind");
		exit(1);
    }

    listen (s, MAX_PENDING);

    addrlen = sizeof(sin);
    cout << "The server is up, waiting for connection" << endl;

    /* wait for connection, then receive and print text */
    while (1) {
		if ((new_s = accept(s, (struct sockaddr *)&sin, &addrlen)) < 0) {
			perror("accept");
			exit(1);
		}

		cout << "new connection from " << inet_ntoa(sin.sin_addr) << endl;
	
		while (len = recv(new_s, buf, sizeof(buf), 0)) {
			CommandKind command = commandProcessor.parse(buf);
			
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
					strcat(returnMessage, messageManager.getNext());
					break;
				case MSGSTORE:
					if (!userManager.loggedIn())
					{
					switch(commandProcessor.last_command)
						{
							case MSGSTORE:
								strcpy(returnMessage, "401 You are not currently logged in, login first.\n");
								break;
							case UNKNOWN:
								strcpy(returnMessage, "INVALID COMMAND\n");
								break;
						}
					}
					else if (commandProcessor.last_command == UNKNOWN)
					{
						messageManager.store(buf);
					}
				
					break;
				case LOGIN:
					if (!userManager.login(commandProcessor.parameters[0].c_str(), commandProcessor.parameters[1].c_str()))
					{
						strcpy(returnMessage, "401 Wrong UserID or Password\n");
					}
					break;
				case LOGOUT:
					if (userManager.loggedIn())
					{
						userManager.logout(userManager.getUser()->UserName->c_str());
					}
					break;
				case SHUTDOWN:
					if (userManager.loggedIn())
					{
						User *currentUser = userManager.getUser();

						if (currentUser->IsInRole("root"))
						{
							send(new_s, returnMessage, strlen(returnMessage) + 1, 0);
							cout << buf;
							close(new_s);
							return 0;
						}
					}

					strcat(returnMessage, "402 User not allowed to execute this command\n");
					break;
				case QUIT:
					if (userManager.loggedIn())
					{
						userManager.logout(userManager.getUser()->UserName->c_str());
					}
					break;
				default:
					break;
			}

			send(new_s, returnMessage, strlen(returnMessage) + 1, 0);
			cout << buf;
		}

		close(new_s);
    }
} 
