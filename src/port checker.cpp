#include <ajar.h>

void check_port(const std::string& ip, int port) {
    auto start_time = std::chrono::high_resolution_clock::now();

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cout << "Socket creation failed.\n";
        return;
    }

    sockaddr_in target{};
    target.sin_family = AF_INET;
    target.sin_port = htons(static_cast<u_short>(port));

    if (inet_pton(AF_INET, ip.c_str(), &target.sin_addr) != 1) {
        std::cout << "Invalid IPv4 address.\n";
        closesocket(sock);
        return;
    }

    int connection_result = connect(
        sock,
        reinterpret_cast<sockaddr*>(&target),
        sizeof(target)
    );

    if (connection_result == 0) {
        std::cout << "Port is open.\n";
    } else {
        std::cout << "Connection failed.\n";
    }

    closesocket(sock);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time
    );

    std::cout << "Time elapsed for tcp check: "
              << duration.count() << " ms\n";
}