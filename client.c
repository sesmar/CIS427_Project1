/*
 * client.c
 */

#include <stdio.h>
#include <iostream>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace std;

#define SERVER_PORT 34352
#define MAX_LINE 256

int main(int argc, char * argv[]) {

    struct sockaddr_in sin;
    char buf[MAX_LINE];
    char rbuf[MAX_LINE];
    int len;
    int s;

    if (argc < 2) {
		cout << "Usage: client <Server IP Address>" << endl;
		exit(1);
    }

    /* active open */
    if ((s = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
    }

    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr  = inet_addr(argv[1]);
    sin.sin_port = htons (SERVER_PORT);

    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("connect");
		close(s);
		exit(1);
    }

    cout << "c: ";

    /* main loop; get and send lines of text */
    while (fgets(buf, sizeof(buf), stdin)) {
		buf[MAX_LINE -1] = '\0';
		len = strlen(buf) + 1;
		send (s, buf, len, 0);
		recv (s, rbuf, sizeof(rbuf), 0);

		cout << "s: " << rbuf;

		string command(buf);
		string output(rbuf);

		//if the command was SHUTDOWN or QUIT
		//and Response was 200 OK then exit program.
		if ((command == "SHUTDOWN\n"
			|| command == "QUIT\n")
			&& output == "200 OK\n")
		{
			close(s);
			return 0;
		}


		cout << "c: ";
    }

    close(s);
} 
