#include "SocketListener.h"

int main() {
    SocketListener listener;
    listener.setPath("/tmp/listener.sock");
    listener.start();
    return 0;
}