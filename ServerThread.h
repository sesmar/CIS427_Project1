#include <iostream>
#include "ClientThread.h"

using namespace std;

class ServerThread : public Thread
{
	private:
		UserManager _userManager;
		MessageManager _messageManager;

	public:
		ServerThread(MessageManager &messageManager, UserManager &userManager);
		int PORT;
		int PENDING;
		int listener;
		int FD;

	protected:
		virtual void InternalThreadEntry();

};
