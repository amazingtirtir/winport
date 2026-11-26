#include <ajar.h>

std::string domaintoip(std::string domain) {
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo* result = nullptr;

    int res = getaddrinfo(
        domain.c_str(), nullptr, &hints, &result
    );

    if (res != 0) {
        std::cerr << "Domain resolution failed.\n";
        return "";
    }

    sockaddr_in* sockaddr_ipv4 =
        reinterpret_cast<sockaddr_in*>(result->ai_addr);

    char ip_str[INET_ADDRSTRLEN]{};

    std::string resolved_ip;

    if (inet_ntop(
        AF_INET,
        &sockaddr_ipv4->sin_addr,
        ip_str,
        sizeof(ip_str)
    ) != nullptr) {
        resolved_ip = ip_str;
    }

    freeaddrinfo(result);

    return resolved_ip;
}