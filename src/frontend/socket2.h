#pragma once


#include <iostream>
#include <cstring>
#include <thread>
#include <string>

#include "socket.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <arpa/inet.h>
#endif

#define PORT 8080

// Function to initialize Winsock on Windows
//#ifdef _WIN32
//void initWinsock() {
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        std::cerr << "WSAStartup failed" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//}
//#endif

// Function to create and connect the client socket
int createClientSocket(const char* server_ip) {
    int sock = 0;
    struct sockaddr_in serv_addr;

    #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    #endif

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    return sock;
}

// Function to receive messages from the server
void receiveMessages(int sock) {
    char buffer[1024] = {0};
    while (true) {
        int bytesRead = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cout << "Server disconnected" << std::endl;
            break;
        }
        std::cout << "Message from server: " << buffer << std::endl;
        memset(buffer, 0, sizeof(buffer));
    }
}

// Function to start the client
void startClient(const char* server_ip) {
    int sock = createClientSocket(server_ip);
    if (sock < 0) {
        return; // Exit if socket creation or connection failed
    }

    // Start a thread to receive messages from the server
    std::thread(receiveMessages, sock).detach();

    // Main loop to send messages to the server
    while (true) {
        std::string message;
        std::cout << "Enter message to send to server (type 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit") {
            break; // Exit the loop if the user types 'exit'
        }

        // Send message to the server
        send(sock, message.c_str(), message.length(), 0);
        std::cout << "Message sent to server: " << message << std::endl;
    }

    // Close the socket
    #ifdef _WIN32
    closesocket(sock);
    WSACleanup();
    #else
    close(sock);
    #endif
}