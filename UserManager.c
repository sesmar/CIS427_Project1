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
User::User(const char* user_name, const char* permission_string, int fd, const char* address_string)
{
    
    this->permissions = new string(permission_string);
	this->UserName = new string(user_name);
    this->FD = fd;
	this->address = new string(address_string);
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

}

///
//Attempts to login the user.
///
//Parameter: userName, the username to check for.
//Parameter: password, the password to check against the userName
///
//Output: true is successful; otherwise, false.
///
bool UserManager::login(const char* userName, const char* password, int fd, const char* address)
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
					User *user = new User(userName, permissions, fd, address);
					users.insert(make_pair(fd, user));	
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
	User *userToLogout;
	bool found = false;

	for (map<int, User*>::iterator ii=users.begin(); ii!=users.end(); ++ii){
		if (strcmp(ii->second->UserName->c_str(), userName) == 0)
		{
			userToLogout = ii->second;
			found = true;
			break;
		}
	}

	if (found)
	{
		users.erase(userToLogout->FD);
		delete userToLogout;
	}
}

void UserManager::logout(int fd)
{
	User *userToLogout = users[fd];
	users.erase(fd);
	delete userToLogout;
}

///
//Get the currently logged in user.
///
//Output: Reference to the currently logged in User
///
User* UserManager::getUser(int fd)
{
	return this->users[fd];
}

User* UserManager::getUser(const char* userName)
{
	User *user;
	
	for(map<int, User*>::iterator ii=users.begin(); ii!=users.end(); ++ii)
	{
		if (strcmp(ii->second->UserName->c_str(), userName) == 0)
		{
			user = ii->second;
			break;
		}
	}

	return user;
}

///
//Checks if a user is currently logged in.
///
//Output: true if a user is currently logged in; otherwise, false.
///
bool UserManager::isLoggedIn(const char* userName)
{
	for(map<int, User*>::iterator ii=users.begin(); ii!=users.end(); ++ii)
	{
		if (strcmp(ii->second->UserName->c_str(), userName) == 0)
		{
			return true;
		}
	}

	return false;
}

bool UserManager::isLoggedIn(int fd)
{
	return (users.count(fd) > 0);
}

const char* UserManager::getUserList()
{
	string *userList = new string("");

	for(map<int, User*>::iterator ii=users.begin(); ii!=users.end(); ++ii)
	{
		userList->append(ii->second->UserName->c_str());
		userList->append(" ");
		userList->append(ii->second->address->c_str());
		userList->append("\n");
	}

	return userList->c_str();
}
