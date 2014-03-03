#include <map>
#include <string>

using namespace std;

///
//User class for storing user information
///
class User
{
	private:
		string *permissions;
	public:
		User();
		~User();
		User(const char* user_name, const char* permissions, int fd, const char* address_string);
		string *UserName;
		int FD;
		string *address;
		bool IsInRole(const char* role);
};

///
//Manages user login and logout.
///
class UserManager
{
	private:
		UserManager();
		static UserManager* _userManager;
		map<int, User*> users;
	public:
		bool login(const char* userName, const char* password, int fd, const char* addres);
		void logout(const char* userName);
		void logout(int fd);
		User* getUser(const char* userName);
		User* getUser(int fd);
		bool isLoggedIn(const char* userName);
		bool isLoggedIn(int fd);
		static UserManager* Current();
};
