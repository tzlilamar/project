#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>

using namespace std;

enum MessageType
{
	MT_CLIENT_SIGN_IN = 200,
	MT_CLIENT_SIGN_UP = 203,
	MT_CLIENT_SIGN_OUT = 201,
	MT_CLIENT_ROOM_REQUEST = 205,
	MT_CLIENT_USER_ROOM = 207,
	MT_CLIENT_CHANGE_NAME = 300,
	MT_CLIENT_CHANGE_PASS = 301,
	MT_CLIENT_CHANGE_EMAIL = 302
};


class Helper
{
public:
	 static int getMessageTypeCode(SOCKET sc);
	 static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
	 static int getIntPartFromSocket(SOCKET sc, int bytesNum);
	 static string getStringPartFromSocket(SOCKET sc, int bytesNum);
	 static void sendData(SOCKET sc, std::string message);
	 static string getPaddedNumber(int num, int digits);

private:
	static char* Helper::getPartFromSocket(SOCKET sc, int bytesNum);

};