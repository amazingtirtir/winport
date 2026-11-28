#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <iostream>
#include <string>
#include <limits>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>
#include <chrono>
#include <thread>

std::string domaintoip(std::string domain);
void wait(int seconds);
void check_port(const std::string& ip, int port);

