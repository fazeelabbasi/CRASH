#undef UNICODE

#include "Server.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#include "Client.h"

void Server::start() {
	std::cout << "Launching server" << std::endl;
	int iResult;
	// Initialize Winsock
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		throw 1;
	}


	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo* result = NULL;
	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		throw 1;
	}



	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		throw 1;
	}


	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		throw 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		throw 1;
	}
}

SOCKET Server::waitForClient() {
	SOCKET ClientSocket = INVALID_SOCKET;

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		return ClientSocket;
		//closesocket(ListenSocket);
		//WSACleanup();
		//throw 1;
	}
	printf("New client connected.\n");
	
	return ClientSocket;

	//c = new Client(&ClientSocket, listener);
	//clients.push_back(c);

}

void Server::listenToClient(SOCKET& sock) {
	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	// Receive until the peer shuts down the connection
	do {
		iResult = recv(sock, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			//sendToClient(c, std::string(recvbuf, iResult));
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			return;
			//closesocket(ClientSocket);
			//WSACleanup();
			//throw 1;
		}

	} while (iResult > 0);
	// cleanup
	printf("Connection closed.\n");
	closesocket(sock);
}

void Server::closeClient(SOCKET& sock) {
	int iResult;
	// shutdown the connection since we're done
	iResult = shutdown(sock, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(sock);
		return;
		//WSACleanup();
		//throw 1;
	}
}

void Server::sendToClient(SOCKET& sock, std::string message) {
	//if (*c->socket == INVALID_SOCKET) {
	//	printf("Failed sending to client, invalid socket.\n");
	//	closesocket(*c->socket);
	//	return;
	//}
	int iSendResult;
	// Echo the buffer back to the sender
	iSendResult = send(sock, message.c_str(), message.length(), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(sock);
		return;
		//WSACleanup();
		//throw 1;
	}
	printf("Bytes sent: %d\n", iSendResult);
}

void Server::stop() {
	closesocket(ListenSocket);
	WSACleanup();
}
