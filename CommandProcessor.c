#include <string.h>
#include "CommandProcessor.h"

CommandProcessor::CommandProcessor() 
{
	last_command = UNKNOWN;
}

CommandKind CommandProcessor::parse(const char *command)
{
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
	else if (strcmp(command, "LOGIN\n") == 0)
	{
		last_command = LOGIN;
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
