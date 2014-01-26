#include <string.h>
#include "CommandProcessor.h"

CommandProcessor::CommandProcessor() {}

CommandKind CommandProcessor::parse(const char *command)
{
	if (strcmp(command, "MSGGET\n") == 0)
	{
		return MSGGET;
	}
	else if (strcmp(command, "MSGSTORE\n") == 0)
	{
		return MSGSTORE;
	}
	else if (strcmp(command, "LOGIN\n") == 0)
	{
		return LOGIN;
	}
	else if (strcmp(command, "LOGOUT\n") == 0)
	{
		return LOGOUT;
	}
	else if (strcmp(command, "SHUTDOWN\n") == 0)
	{
		return SHUTDOWN;
	}
	else if (strcmp(command, "QUIT\n") == 0)
	{
		return QUIT;
	}
	else
	{
		return UNKNOWN;
	}
}
