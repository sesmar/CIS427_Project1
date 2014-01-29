#include <string.h>
#include <fstream>
#include <iostream>
#include "UserManager.h"

User::User() {}

User::User(const char* user_name, const char* permission_string)
{
    this->UserName = new string(user_name);
    this->permissions = new string(permission_string);
    this->socket_number = -1;
}

User::~User()
{
	delete UserName;
	delete permissions;
}

bool User::IsInRole(const char* role)
{
    if (strstr(this->permissions->c_str(), role) != NULL)
    {
	return true;
    }

	return false;
}

UserManager::UserManager() 
{
    this->current_user = new User("", "");
    this->logged_in = false;
}

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

void UserManager::logout(const char*)
{
	delete this->current_user;
	this->logged_in = false;
}

User* UserManager::getUser()
{
	return this->current_user;
}

bool UserManager::loggedIn()
{
	return this->logged_in;
}
