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

using namespace std;

#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 256

int parseCommand(char *command);
const char* getMessage(vector<const char*>*);
vector<const char*> loadMessages(const char*);

int main(int argc, char **argv) {

    struct sockaddr_in sin;
    socklen_t addrlen;
    char buf[MAX_LINE];
    char returnMessage[MAX_LINE];
    int len;
    int s;
    int new_s;
    vector<const char*> messages = loadMessages("messages.txt");

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

		//send (new_s, "200 OK\n", 8, 0);
		cout << "new connection from " << inet_ntoa(sin.sin_addr) << endl;
	
		while (len = recv(new_s, buf, sizeof(buf), 0)) {
			int command = parseCommand(buf);
			
			if (command >= 0)
			{
				strcpy(returnMessage, "200 OK\n");
			}
			else
			{
				strcpy(returnMessage, "INVALID COMMAND\n");
			}

			switch(command)
			{
				case 0:
					strcat(returnMessage, getMessage(&messages));
					break;
				case 1:
					break;
				case 2:
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

int parseCommand(char *command){
	if (strcmp(command, "MSGGET\n") == 0){
		return 0;
	}
	else if (strcmp(command, "MSGSTORE\n") == 0){
		return 1;
	}
	else if (strcmp(command, "LOGIN\n") == 0){
		return 2;
	}
	else if (strcmp(command, "LOGOUT\n") == 0){
		return 3;
	}
	else if (strcmp(command, "SHUTDOWN\n") == 0){
		return 4;
	}
	else if (strcmp(command, "QUIT\n") == 0){
		return 5;
	}

	return -1;
}

const char* getMessage(vector<const char*> *messages)
{
	const char* message = messages->data()[1];
	cout << "Displaying Message " << messages->size() << message << endl;
	return message;
}

vector<const char*> loadMessages(const char *fileName)
{
	string line;
	const char* lineCopy;

	vector<const char*> messages;
	ifstream myFile(fileName);

	if (myFile.is_open())
	{
		while(getline(myFile, line))
		{
			messages.push_back(line.c_str());
		}

		myFile.close();
	}
	else
	{
		cout << "Error Loading Messages!" << endl;
	}

	return messages;
}
