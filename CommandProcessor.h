enum CommandKind
{
	UNKNOWN = -1,
	MSGGET = 0,
	MSGSTORE = 1,
	LOGIN = 2,
	LOGOUT = 3,
	SHUTDOWN = 4,
	QUIT = 5,
};

class CommandProcessor
{
	public:
		CommandKind last_command;
		CommandProcessor();
		CommandKind parse(const char *command);
};
