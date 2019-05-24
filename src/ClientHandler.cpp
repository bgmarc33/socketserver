//
// Created by Bryan Giordano on 5/23/19.
//

#include "ClientHandler.h"

ClientHandler::ClientHandler(const int& clientSocket, const sockaddr_un& clientSockAddr)
    : _clientSocket(clientSocket),
      _clientSockAddr(clientSockAddr) {
}

std::vector<std::string> split(std::string str, const std::string& token){
    std::vector<std::string> result;
    while (!str.empty()) {
        int index = str.find(token);
        if (index != std::string::npos){
            result.push_back(str.substr(0, index));
            str = str.substr(index+token.size());
            if (str.empty()) {
                result.push_back(str);
            }
        } else {
            result.push_back(str);
            str = "";
        }
    }

    return result;
}

std::vector<std::string> ClientHandler::parseRequest(char* request) {
    // break the request into lines
    return split(request, "\n");
}

void ClientHandler::handleRequest() {
    // read in data from the socket
    char buff[3000];
    recv(this->_clientSocket, &buff, sizeof(buff), 0);

    // parse the request
    std::vector<std::string> requestLines = this->parseRequest(buff);

    // operation is the first line
    std::cout << "Operation: " << requestLines[0] << std::endl;

    // return the response
    send(this->_clientSocket, "hello world\n", 20, 0);

    // close the client socket
    close(this->_clientSocket);
}