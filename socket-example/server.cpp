//
// Created by gali yu on 25-9-19.
//
#include <bits/stdc++.h>
#include <netinet/in.h>
#include <sys/socket.h>
using namespace std;

#define PORT 1234
#define BUF_SIZE 1024

int main() {
    signal(SIGCHLD, SIG_IGN);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket error");
        exit(1);
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    // 允许链接处于 TIME_WAIT 状态的端口
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind error");
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen error");
        close(server_fd);
        exit(1);
    }

    cout << "Server listening on port " << PORT << endl;

    auto gowork =[&](int fd) -> void {
        char buf[BUF_SIZE];
        cerr << "client working" << endl;

        ssize_t n;
        while ((n = read(fd, buf, BUF_SIZE)) > 0) {
            write(fd, buf, n);
        }
        close(fd);

        cerr << "a client done" << endl;

        return;
    };

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            cerr << "a client connect error" << endl;
            continue;
        }
        cerr << "a client connected" << endl;

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork error");
            close(client_fd);
            continue;
        } else if (pid == 0) {
            close(server_fd);
            gowork(client_fd);
            exit(0);
        } else {
            close(client_fd);
        }
    }

    close(server_fd);

    return 0;
}