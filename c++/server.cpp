#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

void handle_client(int client_fd) {
    char buffer[1024];
    while (true) {
        ssize_t n = recv(client_fd, buffer, sizeof(buffer), 0);
        if (n <= 0) break;
        send(client_fd, buffer, n, 0);
    }
    close(client_fd);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{AF_INET, htons(8080), INADDR_ANY};
    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 10000);

    std::cout << "C++ server listening on port 8080\n";

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        std::thread(handle_client, client_fd).detach();
    }
}

