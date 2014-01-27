#include <iostream>
#include <fstream>
#include <string.h>
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
	this->file_name.clear();
	this->file_name.append(fileName);
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

void MessageManager::store(const char *message)
{
	ofstream outfile;
	outfile.open(this->file_name.c_str());
	this->messages.push_back(message);

	for(int i = 0; i < this->messages.size(); i++)
	{
		outfile << this->messages[i];
	}

	outfile.close();
}
