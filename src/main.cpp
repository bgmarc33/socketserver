#include "SocketListener.h"

int main() {
    SocketListener listener(SOCKET_TYPE::TCP);
    listener.setHostname("10.100.2.8");
    listener.setPort(3001);
    listener.start();
    return 0;
}