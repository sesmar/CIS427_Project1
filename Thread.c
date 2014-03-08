#include "Thread.h"

///
//Starts the new thread
///
bool Thread::start()
{
	return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
}


///
//Forces the calling thread to wait for execution on this thread
///
void Thread::wait()
{
	(void) pthread_join(_thread, NULL);
}
