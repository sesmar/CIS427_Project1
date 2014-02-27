#include "Thread.h"

bool Thread::start(int port, int maxPending)
{
	_port = port;
	_maxPending = maxPending;
	return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
}

void Thread::wait()
{
	(void) pthread_join(_thread, NULL);
}
