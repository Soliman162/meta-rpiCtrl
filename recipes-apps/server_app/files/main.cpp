#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "seg7_header.hpp"
#include "server.hpp"

int main(void)
{
    server pi;
    std::string rec ;
    seg7_display seg0('0');
    seg7_display seg1('1');

    int seg_index = 0;
    int err_check = -1;
    std::string Help_msg =  "/*****choose operation*******/ \n"
                            "1- Set 7 Segment0              \n"
                            "2- Set 7 Segment1              \n"
                            "3- Turn off connection         \n";

    err_check = pi.server_listen();
    if(err_check!=0)
    {
        return -1;
    }

    while(true)
    {
        pi.send_msg(Help_msg);
        pi.send_msg(static_cast<std::string>("send operation number\n"));
        /*recive command*/
        rec = pi.recieve_msg();

        switch (rec.at(0))
        {
            case '1':
            case '2':
                seg_index = rec.at(0) - '1';
                /* code */
                std::cout << "send number: \n";
                pi.send_msg(static_cast<std::string>("send number:\n"));
                /*recive number*/
                rec = pi.recieve_msg();
                if( seg_index == 0 )
                {
                    seg0.write_number(rec);
                }else if(seg_index == 1 )
                {
                    seg1.write_number(rec);
                }
                break;  
            case '3':
                pi.send_msg(static_cast<std::string>("Turn off connection\n"));
                pi.~server();
                exit (0);
                break;          
            default:
                pi.send_msg(static_cast<std::string>("command not available\n"));
                break;
        }
    }    

    return 0;
}
