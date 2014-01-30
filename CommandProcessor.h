#include <vector>

using namespace std;

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

///
//CommandProcessor class, used to parse user commands.
///
class CommandProcessor
{
	public:
		CommandKind last_command;
		CommandProcessor();
		CommandKind parse(const char *command);
		vector<string> parameters;
};
