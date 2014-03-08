#include <iostream>
#include <fstream>
#include <string.h>
#include "CommandProcessor.h"

///
//Constructor for CommandProcessor
///
CommandProcessor::CommandProcessor() 
{
	last_command = UNKNOWN;
}

///
//Parses the given command
///
//Parameter: command, the inputed command.
//Output: CommandKind, enumeration for the allowable commands.
///
CommandKind CommandProcessor::parse(const char *command)
{
	if (last_command != SEND)
	{
		//clear the parameters from prior command
		parameters.clear();
	}


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
	else if (strcmp(command, "WHO\n") == 0)
	{
		last_command = WHO;
		return WHO;
	}
	else if (strncmp(command, "SEND", 4) == 0)
	{
		last_command = SEND;
		string c(command);

		int start = c.find(" ") + 1;
		parameters.push_back(c.substr(start, (c.length() - start) - 1));


		return SEND;
	}
	else if (last_command == MSGSTORE)
	{
		//if last command was MSGSTORE and new command is not 
		//one of the eight known commands, assume this is the
		//message to be stored, set last command to UNKNOWN
		//and return MSGSTORE
		last_command = UNKNOWN;
		return MSGSTORE;
	}
	else if (last_command == SEND)
	{
		//if last command was SEND and new command is not
		//one of the eight known commands, assume this is the
		//message to be sent, set last command to UNKNOWN
		//and return SEND
		last_command = UNKNOWN;
		return SEND;
	}
	else
	{
		//No known command, return UNKNOWN
		return UNKNOWN;
	}
}
