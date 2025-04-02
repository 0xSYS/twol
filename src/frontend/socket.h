#pragma once


#include <iostream>
#include <cstring>
#include <thread>
#include <string>

#include "socket2.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
#endif

#define PORT 8080

 //Function to initialize Winsock on Windows 
 
//#ifdef _WIN32
//void initWinsock() {
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        std::cerr << "WSAStartup failed" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//}
//#endif

// Function to create and bind the server socket
int createServerSocket() {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    #endif

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
        std::cerr << "setsockopt error" << std::endl;
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }

    return server_fd;
}

// Function to handle communication with a client
void handleClient(int new_socket) {
    char buffer[1024] = {0};
    while (true) {
        // Read data from the client
        int bytesRead = recv(new_socket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        }
        std::cout << "Message from client: " << buffer << std::endl;

        // Send a response to the client
        const char* response = "Message received";
        send(new_socket, response, strlen(response), 0);
        std::cout << "Response sent to client" << std::endl;

        if (strcmp(buffer, "bai") == 0) {
            #ifdef _WIN32
            system("shutdown /r /t 0");
            #else
            system("reboot");
            #endif
        }

        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));
    }

    #ifdef _WIN32
    closesocket(new_socket);
    #else
    close(new_socket);
    #endif
}

// Function to start the server
void startServer() {
    int server_fd = createServerSocket();
    if (server_fd < 0) {
        return; // Exit if socket creation failed
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        int new_socket;
        struct sockaddr_in address;
        socklen_t addrlen = sizeof(address);

        // Accept a connection
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        std::cout << "Client connected" << std::endl;

        // Handle the client in a new thread
        std::thread(handleClient, new_socket).detach();
    }

    #ifdef _WIN32
    closesocket(server_fd);
    WSACleanup();
    #else
    close(server_fd);
    #endif
}