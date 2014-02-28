#include "Thread.h"
#include "CommandProcessor.h"
#include "UserManager.h"
#include "MessageManager.h"

using namespace std;

class ClientThread : public Thread
{
	private:
		CommandProcessor _commandProcessor;
		UserManager _userManager;
		MessageManager _messageManager;

	public:
		ClientThread(UserManager &userManager, MessageManager &messageManager);
		int receiver;
		int FD;

	protected:
		virtual void InternalThreadEntry();
};
