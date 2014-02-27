#include <iostream>
#include "Thread.h"

using namespace std;

class ServerThread : public Thread
{
	public:
		int listener;

	protected:
		virtual void InternalThreadEntry();

};
