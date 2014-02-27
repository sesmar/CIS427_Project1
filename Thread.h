#include <pthread.h>

using namespace std;

class Thread
{
	public:
			Thread() {}
			virtual ~Thread() {}
			bool start(int port, int maxPending);
			void wait();

	protected:
			virtual void InternalThreadEntry() = 0;
			int _port;
			int _maxPending;

	private:
			static void* InternalThreadEntryFunc(void *This) { ((Thread*)This)->InternalThreadEntry(); return NULL; }
			pthread_t _thread;
};
