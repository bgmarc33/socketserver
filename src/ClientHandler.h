//
// Created by Bryan Giordano on 5/23/19.
//

#ifndef UNIXSOCKET_CLIENTHANDLER_H
#define UNIXSOCKET_CLIENTHANDLER_H

#define MAX_BYTES 3000

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/un.h>
#include <string>
#include <vector>

class ClientHandler {
private:
    sockaddr_un _clientSockAddr;
    int _clientSocket;
public:
    ClientHandler() = default;
    ClientHandler(const int&, const sockaddr_un&);
    ~ClientHandler() = default;

    void handleRequest();
    std::vector<std::string> parseRequest(char*);
};


#endif //UNIXSOCKET_CLIENTHANDLER_H
