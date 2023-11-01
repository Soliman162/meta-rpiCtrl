#ifndef SERVER_HPP
#define SERVER_HPP

class server
{
private:
    /* data */
    
    const int PORT;
    std::string rec_buffer;
    int bytesRead;
    int serverSocket;
    int clientSocket;
    sockaddr_in serverAddress{};
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength;
    int bind_server(void);
    int accept_msg(void);

public:
    server();
    ~server();

    std::string recieve_msg(void);
    int server_listen(void);
    int send_msg(std::string msg);

    int Get_bufferSize(void);
};

#endif