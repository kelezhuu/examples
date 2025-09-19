//
// Created by gali yu on 25-9-19.
//
#include <bits/stdc++.h>
#include <netinet/in.h>
#include <sys/socket.h>
using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(1234);
    connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr));

    char buffer[40];
    read(sock, buffer, sizeof(buffer)-1);

    close(sock);

    return 0;
}