#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>

using namespace std;

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