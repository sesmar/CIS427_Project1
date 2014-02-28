#include <pthread.h>

using namespace std;

class Thread
{
	public:
			Thread() {}
			//virtual ~Thread() {}
			bool start();
			void wait();

	protected:
			virtual void InternalThreadEntry() = 0;

	private:
			static void* InternalThreadEntryFunc(void *This) { ((Thread*)This)->InternalThreadEntry(); return NULL; }
			pthread_t _thread;
};
