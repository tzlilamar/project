#include <exception>
#include "Server.h"
#include "Helper.h"

static const unsigned short PORT = 8820;
static const unsigned int IFACE = 0;

Server::Server() /*: _db() */
{
	this->_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_socket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

Server::~Server() 
{
	try
	{
		::closesocket(_socket);
	}
	catch (...) {}
}

void Server::serve()
{
	bindAndListen();

	// create new thread for handling message
	std::thread tr(&Server::handleRecievedMessages, this);
	tr.detach();

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		acceptClient();
	}
}

void Server::bindAndListen()
//This function binds and starts to listen 
//In case of the bind failing exception is thrown 
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
}

void Server::acceptClient()
//This function accepts the new client and creates a thread 
{
	SOCKET client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__);
	}
	// create new thread for client	and detach from it
	std::thread tr(&Server::clientHandler, this, client_socket);
	tr.detach();
}

void Server::clientHandler(SOCKET client_socket)
{
	Message* currRcvMsg = nullptr;
	
	// get the first message code
	int msgCode = Helper::getMessageTypeCode(client_socket);

	while (msgCode != 0)
	{
		currRcvMsg = buildRecieveMessage(client_socket, msgCode);
		addRecievedMessage(currRcvMsg);

		msgCode = Helper::getMessageTypeCode(client_socket);
	}
	/*if (/*the client sends signout message)
	
		{
			currRcvMsg = buildRecieveMessage(client_socket, 0); //In case of the client quitting (299)
			addRecievedMessage(currRcvMsg);
		}
	*/
	closesocket(client_socket); //Closing the socket
}

void Server::handleRecievedMessages()
{
	//std::cout << "he" << std::endl;
}

void Server::addRecievedMessage(Message* msg)
//This function lockes the mutex for the message queue and puts messages in queue 
{
	unique_lock<mutex> lck(this->_mtxRecieveMessages);

	this->_queRcvMessages.push(msg); //Put new messages in queue 
	lck.unlock();
	this->_msgQueueCondition.notify_all(); //wakes up the thread of handling messsages
}

Message* Server::buildRecieveMessage(SOCKET sock, int msg)
//This function creates a message according to the message code of the user. If there is any extra data, the function enters it to a vector.
//In case of success - the function returns the message of the user
//In case of failure - the function returns nullptr
{
	//bulid the mesasge with the message class and call each handaling functions 
}