#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "MessageManager.h"

MessageManager::MessageManager()
{
	this->currentIndex = 0;
}

const char* MessageManager::getNext()
{
	if (messages.size() > currentIndex && messages.size() > 0)
	{
		return messages[currentIndex++].c_str();
	}
	else if (messages.size() > 0)
	{
		this->currentIndex = 0;
		this->getNext();
	}
}

void MessageManager::load(const char* fileName)
{
	string line;
	ifstream infile(fileName);


	if (infile.is_open())
	{
		messages.empty();

		while(getline(infile, line))
		{
			messages.push_back((line + "\n"));
		}

		infile.close();
	}
	else
	{
		cout << "Error loading messages from file!" << endl;
	}
}
