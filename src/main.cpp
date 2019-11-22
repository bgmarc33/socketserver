#include "Server/SocketListener.h"
#include "Home.h"

int main() {
    Home* h = new Home();

    SocketListener listener(SOCKET_TYPE::TCP);
    listener.setHostname("192.168.1.11");
    listener.setPort(3001);
    listener.setClientHandler(h);
    listener.start();
    return 0;
}