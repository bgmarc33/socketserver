//
// Created by Bryan Giordano on 5/23/19.
//

#include "ClientHandler.h"

ClientHandler::ClientHandler(const int& clientSocket, const sockaddr& clientSockAddr)
    : _clientSocket(clientSocket),
      _clientSockAddr(clientSockAddr) {
}

std::vector<std::string> ClientHandler::parseRequest(char* request) {
    return std::vector<std::string>();
}

void ClientHandler::handleRequest() {
    // read in data from the socket
    char buff[MAX_BYTES];
    recv(this->_clientSocket, &buff, MAX_BYTES, 0);
    std::cout << buff << std::endl;

    // parse the request
    std::vector<std::string> requestLines = this->parseRequest(buff);

    // return the response

    // close the client socket
    close(this->_clientSocket);
}