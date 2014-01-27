///
//Message Manager
///

#include <vector>

using namespace std;

class MessageManager
{
	private:
		int currentIndex;
		vector<string> messages;
		string file_name;

	public:
		MessageManager();
		void load(const char *fileName);
		const char* getNext();
		void store(const char *message);
};
