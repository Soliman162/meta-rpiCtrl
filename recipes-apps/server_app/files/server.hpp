#ifndef SERVER_HPP
#define SERVER_HPP

const int BUFFER_SIZE =1024;


class server
{
private:
    /* data */
    
    const int PORT;
    char rec_buffer[BUFFER_SIZE];
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

    char * recieve_msg(void);
    int server_listen(void);
    int send_msg(std::string msg);
};

#endif