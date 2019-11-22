//
// Created by Bryan Giordano on 11/21/19.
//

#include "Home.h"

void Home::handleRequest(int clientSock) {
    char buff[MAX_BYTES];
    recv(clientSock, &buff, MAX_BYTES, 0);
    std::cout << buff << std::endl;

    // parse the request
    std::vector<std::string> requestLines = this->parseRequest(buff);

    char resp[] = "HTTP/1.1 200 OK\nContent-Type: application/javascript\n\n {\"message\":\"hello world\"})";
    // return the response
    send(clientSock, resp, strlen(resp), 0);

    // close the client socket
    close(clientSock);
}

std::vector<std::string> Home::parseRequest(char *) {
    return std::vector<std::string>();
}
