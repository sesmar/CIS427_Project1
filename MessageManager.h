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
		MessageManager();
		int currentIndex;
		vector<string> messages;
		string file_name;
		static MessageManager* _messageManager;

	public:
		//MessageManager();
		void load(const char *fileName);
		const char* getNext();
		void store(const char *message);
		static MessageManager* Current();
};
