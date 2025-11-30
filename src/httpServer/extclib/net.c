#if defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
#elif defined(_WIN32) || defined(WIN32)
    #include <winsock2.h>
#else
    #warning "Platform not supported"
#endif

#if defined(__linux__) || defined(_WIN32) || defined(WIN32) || defined(__APPLE__)

typedef enum error_t {
    WINSOCK_ERR = -1,
    SOCKET_ERR = -2,
    SETOPT_ERR = -3,
    PARSE_ERR = -4,
    BIND_ERR = -5,
    LISTEN_ERR = -6,
} error_t;

#include "net.h"

extern int listen_net(char *address){
#ifdef _WIN32 || WIN32
    WSDATA wsa;
    if (WSAStartuo(MAKEWORD(2, 2), &wsa) != 0) {
        return WINSOCK_ERR;
    }
#endif
    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        return SOCKET_ERR;
    }
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        return SETOPT_ERR;
    }
    char ipv4[16];
    char port[6];
    if (_parse_address(address, ipv4, port) != 0) {
        return PARSE_ERR;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ipv4);
    if (bind(listener, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        return BIND_ERR;
    }
    if (listen(listener, SOMAXCONN) != 0) {
        return LISTEN_ERR;
    }
    return listener;
}

extern int accept_net(int listener){
    return accept(listener, NULL, NULL);
}

extern int connect_net(char *address){
}

extern int close_net(int conn){
}

extern int send_net(int conn, char *buffer, size_t size){
}
extern int recv_net(int conn, char *buffer, size_t size){
}

#endif