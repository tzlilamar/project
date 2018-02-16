#pragma once

#include "WSAInitializer.h"
#include <mutex>
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <thread>
#include <condition_variable>
#include "Message.h"
#include <queue>

using namespace std;

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
	void Server::addRecievedMessage(Message* msg);
	Message* Server::buildRecieveMessage(SOCKET sock, int msg);

	SOCKET _socket;
	//DataBase _db;
	mutex _mtxRecieveMessages; //For the threads
	queue<Message*> _queRcvMessages; //This is the queue of the users' messages
	condition_variable _msgQueueCondition; //For the threads
};