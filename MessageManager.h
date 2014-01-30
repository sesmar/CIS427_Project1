///
//Message Manager
///

#include <vector>

using namespace std;

///
//MessageManager manages loading message from file
//and saving new messages to file.
///
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
