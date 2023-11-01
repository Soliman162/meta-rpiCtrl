#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <functional>

#include "server.hpp"

server::server():PORT(8080),rec_buffer(50, '\0')
{
    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < -1) {
        std::cerr << "Failed to create socket.\n";
    }
}

server::~server()
{
    // Close the client and server sockets
    close(clientSocket);
    close(serverSocket);
}

 int server::bind_server(void)
 {
    // Bind the socket to an address and port
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) 
    {
        
        return -1;
    }
    return 0;
 }

int server::server_listen(void)
{
    if(bind_server()<0)
    {
        std::cerr << "Failed to bind socket.\n";
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 3) < 0) 
    {
        std::cerr << "Failed to listen.\n";
        return -1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    if(accept_msg()<0)
    {
        std::cerr << "Failed to accept connection.\n";
        return -1;
    }
    return 0;
}

int server::accept_msg(void)
{
    // Accept a client connection
    clientAddressLength = sizeof(clientAddress);

    if ((clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddress, &clientAddressLength)) < 0) {
        
        return -1;
    }
    return 0;
}

std::string server::recieve_msg(void)
{
    // Receive and print client message
    bytesRead = read(clientSocket, &rec_buffer[0] , rec_buffer.size());
    if (bytesRead < 0) {
        std::cerr << "Failed to read from socket.\n";
        return "";
    }
    // rec_buffer.resize(bytesRead);
    std::cout << "Received message from client: " << rec_buffer << std::endl;
    return rec_buffer;
}

int server::send_msg(std::string msg)
{
    if (send(clientSocket, msg.c_str(), msg.length(), 0) < 0) 
    {
        std::cerr << "Failed to send response.\n";
        return -1;
    }
    return 0;
}
int server::Get_bufferSize(void)
{
    return rec_buffer.size();
}
