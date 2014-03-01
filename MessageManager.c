#include <iostream>
#include <fstream>
#include <string.h>
#include "MessageManager.h"

MessageManager* MessageManager::_messageManager = NULL;

MessageManager* MessageManager::Current()
{
	if (_messageManager == NULL)
	{
		_messageManager = new MessageManager();
	}

	return _messageManager;
}

///
//Constructor
///
MessageManager::MessageManager()
{
	this->currentIndex = 0;
}

///
//Gets the next message in the list
///
//Output: Return a const char* reference to the next message
//in the queue.
///
const char* MessageManager::getNext()
{
	//if the current index is less than the size of the vector
	//and the vector has message return the message at the
	//current index.
	if (messages.size() > currentIndex && messages.size() > 0)
	{
		return messages[currentIndex++].c_str();
	}
	//if the vector has messages, than the current index
	//is greater than the number of messages, loop back
	//to the beginning.
	else if (messages.size() > 0)
	{
		this->currentIndex = 0;
		this->getNext();
	}
}

///
//Load message from the given file
///
//Parameter: the file name to load messages from
///
void MessageManager::load(const char* fileName)
{
	//set the filename for the message file.
	this->file_name.clear();
	this->file_name.append(fileName);
	string line;
	//Open the file.
	ifstream infile(fileName);


	if (infile.is_open())
	{
		//clear out the message list
		messages.clear();

		//loop through each line in the file.
		while(getline(infile, line))
		{
			//add the message with \n to the vector.
			messages.push_back((line + "\n"));
		}

		//close the message file
		infile.close();
	}
	else
	{
		cout << "Error loading messages from file!" << endl;
	}
}

///
//Save the given message to the current file
///
//Parameter: new message to be stored
///
void MessageManager::store(const char *message)
{
	ofstream outfile;
	//Open the current file.
	outfile.open(this->file_name.c_str());
	//Add the message to the vector
	this->messages.push_back(message);

	//Write all of the message to the file.
	for(int i = 0; i < this->messages.size(); i++)
	{
		outfile << this->messages[i];
	}

	outfile.close();
}
