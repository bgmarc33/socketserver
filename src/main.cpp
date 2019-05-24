#include "SocketListener.h"

int main() {
    SocketListener listener;
    listener.setPath("/tmp/ldap.sock");
    listener.start();
    return 0;
}