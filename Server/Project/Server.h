#pragma once

#include "WSAInitializer.h"
#include <mutex>
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <thread>
#include <condition_variable>

class Server
{
public:
	Server();
	~Server(); 

	
	void serve();

private:
	void bindAndListen();
	void acceptClient();
	void clientHandler(SOCKET client_socket);
	void handleRecievedMessages();

	SOCKET _socket;
	//DataBase _db;
};