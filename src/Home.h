//
// Created by Bryan Giordano on 11/21/19.
//

#ifndef UNIXSOCKET_HOME_H
#define UNIXSOCKET_HOME_H

#include "Server/ClientHandler.h"

class Home : public ClientHandler {
public:
    void handleRequest(int);
    std::vector<std::string> parseRequest(char*);
};


#endif //UNIXSOCKET_HOME_H
