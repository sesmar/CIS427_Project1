#include "Thread.h"
#include "CommandProcessor.h"
#include "UserManager.h"
#include "MessageManager.h"
#include <sys/types.h>

using namespace std;

class ClientThread : public Thread
{
	private:
		CommandProcessor _commandProcessor;
		static fd_set* master;
		static bool isMasterSet;

	public:
		ClientThread();
		int receiver;
		int FD;
		int ServerFD;
		string *address;
		static fd_set* Master();
		static int fdmax;
		static pthread_t SHUT_DOWN;

	protected:
		virtual void InternalThreadEntry();
};
