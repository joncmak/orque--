#include "stdafx.h"
#include "orqueServer.h"

#define mDEFAULT_PORT 8080
using namespace std;

void ServerThread(void * pParam);
void PlayerThread(void * pParam);

orqueServer::orqueServer()
{
}


orqueServer::~orqueServer()
{
}

void PlayerThread(void * pParam)
{
	cout << "new player joined" << endl;
}

void ServerThread(void * pParam)
{
	SOCKET server;
	WSADATA wsaData;

	sockaddr_in local;

	int wsaret = WSAStartup(0x101, &wsaData);
	if (wsaret != 0)
	{
		return;
	}

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons((u_short)mDEFAULT_PORT);

	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server == INVALID_SOCKET)
	{
		return;
	}

	if (bind(server, (sockaddr *)&local, sizeof(local)) != 0)
	{
		return;
	}

	if (listen(server, 10) != 0)
	{
		return;
	}

	SOCKET client;
	sockaddr_in clientAddr;
	int addrLen = sizeof(clientAddr);

	char serverIP[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &local.sin_addr, serverIP, INET_ADDRSTRLEN);
	cout << "server started " << serverIP << endl;

	while (true)
	{
		client = accept(server, (struct sockaddr *)&clientAddr, &addrLen);
		_beginthread(PlayerThread, 0, (void *)client);
	}
}

int main()
{
	int nRetCode = 0;

	_beginthread(ServerThread, 0, NULL);
	while (_getch() != 27);

	WSACleanup();

	return nRetCode;
}
