#include "Message.h"

Message::Message(SOCKET sock, int messageCode)
{ 
	this->_sock = sock;
	this->_messageCode = messageCode;
	
}

Message::Message(SOCKET sock, int messageCode, vector<string> values) : Message(sock, messageCode)
{
	this->_values = values;
}

SOCKET Message::getSock()
{
	return this->_sock;
}

int Message::getMessageCode()
{
	return this->_messageCode;
}

vector<string>& Message::getValues()
{
	return this->_values;
}