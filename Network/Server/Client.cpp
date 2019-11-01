#include "Client.h"
#include <WinSock2.h>
#include <thread>
Client::Client(SOCKET& sock, std::thread& l) : socket(sock), listener(l) {}
