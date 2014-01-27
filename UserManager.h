using namespace std;

class User
{
	private:
		string permissions;
	public:
		User();
		User(const char* user_name, const char* permissions);
		string UserName;
		int socket_number;
		bool IsInRole(const char* role);
};

class UserManager
{
	private:
		User current_user;
		bool logged_in;
	public:
		UserManager();
		bool login(const char* userName, const char* password);
		void logout(const char* userName);
		User getUser();
		bool loggedIn();
};
