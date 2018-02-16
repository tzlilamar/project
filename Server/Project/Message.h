#pragma once

#include <string>
#include <vector>
#include <WinSock2.h>
#include <Windows.h>

using namespace std;

class Message
{
public:
	Message(SOCKET sock, int messageCode);

	Message(SOCKET sock, int messageCode, vector<string> values);

	SOCKET getSock();
	int getMessageCode();

	vector<string>& getValues();

private:
	SOCKET _sock;
	int _messageCode;
	vector<string> _values; 
};

