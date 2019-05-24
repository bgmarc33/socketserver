//
// Created by Bryan Giordano on 5/23/19.
//

#ifndef UNIXSOCKET_SOCKETLISTENER_H
#define UNIXSOCKET_SOCKETLISTENER_H

#include <string>
#include <thread>
#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include <unistd.h>
#include <vector>

class SocketListener {
private:
    int _serverSocket;
    sockaddr_un _socketAddr;
    std::string _path;
    bool _initialized;
    std::vector<std::thread> _threads;

public:
    SocketListener() = default;
    SocketListener(const std::string&);
    ~SocketListener();

    // mutators
    void setPath(const std::string&);

    // accessors
    const std::string& getPath() const;

    void init();
    void start();
};


#endif //UNIXSOCKET_SOCKETLISTENER_H
