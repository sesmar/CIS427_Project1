#include <iostream>
#include <fstream>
#include <string.h>
#include "CommandProcessor.h"

CommandProcessor::CommandProcessor() 
{
	last_command = UNKNOWN;
}

CommandKind CommandProcessor::parse(const char *command)
{
	parameters.clear();

	if (strcmp(command, "MSGGET\n") == 0)
	{
		last_command = MSGGET;
		return MSGGET;
	}
	else if (strcmp(command, "MSGSTORE\n") == 0)
	{
		last_command = MSGSTORE;
		return MSGSTORE;
	}
	else if (strncmp(command, "LOGIN", 5) == 0)
	{
		last_command = LOGIN;
		string c(command);
		//Parse username and password as parameters
		int start = c.find(" ") + 1;
		int end = c.find_last_of(" ");

		//add them to the parameters vector
		parameters.push_back(c.substr(start, (end - start)));
		parameters.push_back(c.substr(end + 1, (c.length() - end) - 2));

		return LOGIN;
	}
	else if (strcmp(command, "LOGOUT\n") == 0)
	{
		last_command = LOGOUT;
		return LOGOUT;
	}
	else if (strcmp(command, "SHUTDOWN\n") == 0)
	{
		last_command = SHUTDOWN;
		return SHUTDOWN;
	}
	else if (strcmp(command, "QUIT\n") == 0)
	{
		last_command = QUIT;
		return QUIT;
	}
	else if (last_command == MSGSTORE)
	{
		last_command = UNKNOWN;
		return MSGSTORE;
	}
	else
	{
		return UNKNOWN;
	}
}
