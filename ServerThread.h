#include <iostream>
#include "Thread.h"

using namespace std;

class ServerThread : public Thread
{
	public:
		int PORT;
		int PENDING;
		int listener;
		int FD

	protected:
		virtual void InternalThreadEntry();

};
