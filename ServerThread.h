#include <iostream>
#include "ClientThread.h"

using namespace std;

class ServerThread : public Thread
{
	public:
		ServerThread() {}
		int PORT;
		int PENDING;
		int listener;
		int FD;

	protected:
		virtual void InternalThreadEntry();

};
