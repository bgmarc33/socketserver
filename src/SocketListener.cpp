//
// Created by Bryan Giordano on 5/23/19.
//

#include "SocketListener.h"
#include "ClientHandler.h"

SocketListener::SocketListener(const std::string& path)
    : _path(path),
      _initialized(false) {
}

SocketListener::~SocketListener() {
    for (auto &t: this->_threads) {
        t.join();
    }

    close(this->_serverSocket);
}

void SocketListener::init() {
    if (this->_path.empty()) {
        std::cout << "No path provided for socket\n" << std::endl;
        return;
    }

    // create socket addr struct
    this->_socketAddr.sun_family = AF_UNIX;
    strcpy(this->_socketAddr.sun_path, this->_path.c_str());

    // create socket handler
    this->_serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (this->_serverSocket < 0) {
        perror("Error creating socket");
        return;
    }

    unlink(this->_path.c_str());
    if (bind(this->_serverSocket, (struct sockaddr*) &this->_socketAddr, sizeof(this->_socketAddr)) < 0) {
        perror("Failed to bind socket");
        return;
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

    std::cout << "Listening on " << this->_path << std::endl;
    while (true) {
        sockaddr_un clientAddr;
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

const std::string& SocketListener::getPath() const {
    return this->_path;
}