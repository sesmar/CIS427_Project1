#include <string.h>
#include <fstream>
#include <iostream>
#include "UserManager.h"

///
//Constructor, default
///
User::User() {}

///
//Constructor
//Parameter: user_name, the user name of the user.
//Parameter: permission_string, the users permissions.
///
User::User(const char* user_name, const char* permission_string)
{
    
    this->permissions = new string(permission_string);
	this->UserName = new string(user_name);
    this->socket_number = -1;
}

///
//Deconstructor for User.
///
User::~User()
{
	delete UserName;
	delete permissions;
}

///
//Checks if a User has the given permission.
///
//Parameter: role, the role to check the user for.
///
//Output:  true if the user is in the given role; otherwise, false.
///
bool User::IsInRole(const char* role)
{
    if (strstr(this->permissions->c_str(), role) != NULL)
    {
		return true;
    }

	return false;
}

UserManager* UserManager::_userManager = NULL;

UserManager* UserManager::Current()
{
	if (_userManager == NULL)
	{
		_userManager = new UserManager();
	}

	return _userManager;
}

///
//Constructor for User manager
///
UserManager::UserManager() 
{
    this->current_user = new User("", "");
    this->logged_in = false;
}

///
//Attempts to login the user.
///
//Parameter: userName, the username to check for.
//Parameter: password, the password to check against the userName
///
//Output: true is successful; otherwise, false.
///
bool UserManager::login(const char* userName, const char* password)
{
    string line;
    ifstream user_file("users.txt");

    if (user_file.is_open())
    {
		while (getline(user_file, line))
		{
			if (line.find(userName) != -1)
			{
				int start = line.find(" ") + 1;
				int end = line.find_last_of(" ");

				string linePassword(line.substr(start, end-start));

				if (linePassword == password)
				{
					const char* permissions = line.substr(line.find_last_of(" ") + 1, string::npos).c_str(); 
					this->current_user =  new User(userName, permissions);
					this->logged_in = true;
					return true;
				}
			}
		}
	}
	else
	{
		cout << "Error reading the user file!" << endl;
	}

	return false;
}

///
//Logs the userout.
///
//Parameter: userName, not used at this time.
///
void UserManager::logout(const char* userName)
{
	delete this->current_user;
	this->logged_in = false;
}

///
//Get the currently logged in user.
///
//Output: Reference to the currently logged in User
///
User* UserManager::getUser()
{
	return this->current_user;
}

///
//Checks if a user is currently logged in.
///
//Output: true if a user is currently logged in; otherwise, false.
///
bool UserManager::loggedIn()
{
	return this->logged_in;
}
