#include <iostream>
#include "Thread.h"

using namespace std;

class ClientThread : public Thread
{
	public:
		int receiver;
		int FD;

	protected:
		virtual void InternalThreadEntry();
}
