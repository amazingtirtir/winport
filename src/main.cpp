#define NOMINMAX

#include <ajar.h>

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

        if (confirm == 'n' || confirm == 'N') {
            std::cout << "Operation cancelled.\n";
            std::cout << "Do you want to check another port? (y/n): ";
            char check_another;
            std::cin >> check_another;
            if (check_another == 'y' || check_another == 'Y') {
                continue;
            } else if (check_another == 'n' || check_another == 'N') {
                std::cout << "Exiting program.\n";
                wait(2);
                break;
            } else {
                std::cout << "Invalid input. Exiting program.\n";
                wait(2);
                break;
            }
            
        }else if (confirm != 'y' && confirm != 'Y') {
            std::cout << "Invalid input. Exiting program.\n";
            wait(2);
            WSACleanup();
            return 1;
        }
        check_port(ip_result, port_input);
        std::cout << "do you want to check another port? (y/n): ";
        char check_another;
        std::cin >> check_another;
        if (check_another == 'y' || check_another == 'Y') {
            //continue
        } else if (check_another == 'n' || check_another == 'N') {
            std::cout << "Exiting program.\n";
            wait(2);
            break;
        }else {
            std::cout << "Invalid input. Exiting program.\n";
            wait(2);
            break;
        }
    }

    WSACleanup();
    return 0;
}

void wait(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}