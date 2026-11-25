#define NOMINMAX

#include <winport.h>

int main() {
    WSADATA wsa_data{};

    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        std::cout << "Failed to initialize Winsock.\n";
        return 1;
    }

    std::string server_input;
    std::string ip_result;
    int port_input{};

    while (true) {
        std::cout << "Enter domain/IP address: ";

        if (!(std::cin >> server_input)) {
            WSACleanup();
            return 1;
        }

        std::cout << "Enter port number: ";

        if (!(std::cin >> port_input)) {
            if (std::cin.eof()) {
                WSACleanup();
                return 1;
            }

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "Invalid input.\n";
            continue;
        }

        if (port_input < 1 || port_input > 65535) {
            std::cout << "Invalid port number.\n";
            continue;
        }

        in_addr address{};

        int result_IPcheck = inet_pton(
            AF_INET,
            server_input.c_str(),
            &address
        );

        if (result_IPcheck == 1) {
            std::cout << "Valid IPv4 address.\n";
            ip_result = server_input;
            break;

        } else if (result_IPcheck == 0) {
            std::cout << "Attempting domain resolution...\n";

            ip_result = domaintoip(server_input);

            if (ip_result.empty()) {
                std::cout << "Resolution failed. Try again.\n";
                continue;
            }

            break;

        } else {
            std::cout << "An error occurred.\n";
            WSACleanup();
            return 1;
        }
    }

    std::cout << "\nResolved IP: " << ip_result << '\n';
    std::cout << "Selected port: " << port_input << '\n';
    std::cout << "Are you sure you want to proceed? (y/n): ";

    char confirm;
    std::cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        std::cout << "Operation cancelled.\n";
        WSACleanup();
        return 0;
    }
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET) {
    std::cout << "Socket creation failed.\n";
    WSACleanup();
    return 1;
    }
    sockaddr_in target{};

    target.sin_family = AF_INET;
    target.sin_port = htons(port_input);

    inet_pton(AF_INET, ip_result.c_str(), &target.sin_addr);

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
    std::cout << "Press Backspace to exit...";
    while (true) {
        if (_getch() == 8) {
            break;
        }
    }
    
    closesocket(sock);
    WSACleanup();
    return 0;
}