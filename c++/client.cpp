#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int CLIENTS = 10000;

void run_client() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    connect(sock, (sockaddr*)&server, sizeof(server));

    char msg[100] = {1};
    char buf[100];
    send(sock, msg, 100, 0);
    recv(sock, buf, 100, MSG_WAITALL);
    close(sock);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    for (int i = 0; i < CLIENTS; ++i) {
        threads.emplace_back(run_client);
    }
    for (auto& t : threads) t.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    double avg_us = static_cast<double>(duration_us.count()) / CLIENTS;
    
    std::cout << "C++: " << CLIENTS << " clients, total time = " << duration_ms.count()
              << " ms, avg = " << avg_us << " μs\n";
}

