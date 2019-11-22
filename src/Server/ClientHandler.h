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
public:
    ClientHandler() = default;
    ~ClientHandler() = default;

    virtual void handleRequest(int)  = 0;
    virtual std::vector<std::string> parseRequest(char*) = 0;
};


#endif //UNIXSOCKET_CLIENTHANDLER_H
