#include <string.h>
#include <fstream>
#include <iostream>
#include "UserManager.h"

User::User() {}

User::User(const char* user_name, const char* permission_string)
{
    this->UserName.clear();
    this->UserName.append(user_name);
    this->permissions.clear();
    this->permissions.append(permission_string);
    this->socket_number = -1;
}

bool User::IsInRole(const char* role)
{
    if (strstr(this->permissions.c_str(), role) != NULL)
    {
	return true;
    }

    return false;
}

UserManager::UserManager() 
{
    User user("", "");
    this->current_user = user;
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
				if (line.find(password) != -1)
				{
					const char* permissions = line.substr(line.find_last_of(" ") + 1, string::npos).c_str(); 
					User user(userName, permissions);
					this->current_user = user;
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
	User user("", "");
	this->current_user = user;
	this->logged_in = false;
}

User UserManager::getUser()
{
	return this->current_user;
}

bool UserManager::loggedIn()
{
	return this->logged_in;
}
