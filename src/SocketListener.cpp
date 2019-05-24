//
// Created by Bryan Giordano on 5/23/19.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include "SocketListener.h"
#include "ClientHandler.h"

SocketListener::SocketListener(const SOCKET_TYPE& type)
    : _type(type),
      _path(""),
      _hostname(""),
      _port(-1),
      _initialized(false) {
}

SocketListener::~SocketListener() {
    for (auto &t: this->_threads) {
        t.join();
    }

    shutdown(this->_serverSocket, 0);
    close(this->_serverSocket);
}

void SocketListener::init() {
    // determine the type of socket
    sockaddr* socketAddr;
    switch (this->_type) {
        case SOCKET_TYPE::UNIX: {
            if (this->_path.empty()) {
                std::cout << "No path provided for socket" << std::endl;
                return;
            }

            sockaddr_un unixSocket{};
            unixSocket.sun_family = AF_UNIX;
            strcpy(unixSocket.sun_path, this->_path.c_str());

            this->_serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
            if (this->_serverSocket < 0) {
                perror("Error creating socket");
                return;
            }

            const int one = 1;
            setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

            unlink(this->_path.c_str());
            if (bind(this->_serverSocket, (struct sockaddr*) &unixSocket, sizeof(unixSocket)) < 0) {
                perror("Failed to connect socket");
                return;
            }

            break;
        }

        case SOCKET_TYPE::TCP: {
            if (this->_hostname.empty()) {
                std::cout << "No hostname provided for socket" << std::endl;
                return;
            }

            if (this->_port == -1) {
                std::cout << "No port provided for socket" << std::endl;
                return;
            }

            sockaddr_in tcpSocket{};
            tcpSocket.sin_family = AF_INET;
            tcpSocket.sin_addr.s_addr = inet_addr(this->_hostname.c_str());
            tcpSocket.sin_port = htons(this->_port);

            this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (this->_serverSocket < 0) {
                perror("Error creating socket");
                return;
            }

            if (bind(this->_serverSocket, (struct sockaddr*) &tcpSocket, sizeof(tcpSocket)) < 0) {
                perror("Failed to connect socket");
                return;
            }

            break;
        }

        default: {
            std::cout << "Invalid socket type" << std::endl;
            return;
        }
    }

    this->_initialized = true;
}

void SocketListener::start() {
    if (!this->_initialized) {
        this->init();
        if (!this->_initialized) {
            std::cout << "Failed to initialize socket\n";
            return;
        }
    }

    if (listen(this->_serverSocket, 100) < 0) {
        perror("Failed to start listening on socket");
        return;
    }

    switch (this->_type) {
        case SOCKET_TYPE::TCP: {
            std::cout << "Listening on " << this->_hostname << ":" << this->_port << std::endl;
            break;
        }

        case SOCKET_TYPE::UNIX: {
            std::cout << "Listening on " << this->_path << std::endl;
            break;
        }
    }

    while (true) {
        sockaddr_un clientAddr{};
        memset(&clientAddr, 0, sizeof(sockaddr_un));
        unsigned int clientAddrSize = sizeof(clientAddr);
        int clientSock = accept(this->_serverSocket, (struct sockaddr *) &clientAddr, &clientAddrSize);
        if (clientSock < 0) {
            perror("Failed to accept client");
            continue;
        }

        // accepting client connection
        std::cout << "Accepted client connection" << std::endl;

        // create client handler
        ClientHandler handler(clientSock, clientAddr);

        // create thread
        this->_threads.emplace_back(&ClientHandler::handleRequest, handler);
    }
}

void SocketListener::setPath(const std::string& path) {
    this->_path = path;
}

void SocketListener::setHostname(const std::string& hostname) {
    this->_hostname = hostname;
}

void SocketListener::setPort(const int &port) {
    this->_port = port;
}

const std::string& SocketListener::getPath() const {
    return this->_path;
}

const std::string& SocketListener::getHostname() const {
    return this->_hostname;
}

const int SocketListener::getPort() const {
    return this->_port;
}

