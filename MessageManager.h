///
//Message Manager
///

#include <cstring>
#include <vector>

using namespace std;

class MessageManager
{
	private:
		int currentIndex;
		vector<string> messages;

	public:
		MessageManager();
		void load(const char *fileName);
		const char* getNext();
		void store(const char *message);
};
