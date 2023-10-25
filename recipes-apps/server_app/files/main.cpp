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
    seg7_display seg0('0');
    seg7_display seg1('1');
    int err_check = -1;
    std::string rec ;

    std::string Help_msg =  "/**********help msg**********/ \n"
                            "/*****choose operation*******/ \n"
                            "1- Set 7 Segment0              \n"
                            "2- Set 7 Segment1              \n";


    err_check = pi.server_listen();
    if(err_check!=0)
    {
        return -1;
    }
    err_check = pi.send_msg(Help_msg);
    if(err_check!=0)
    {
        return -1;
    }

    while(true)
    {
        rec = pi.recieve_msg();

        if( rec.c_str() != NULL )
        {
            std::cout << "send number: \n";
            err_check = pi.send_msg(static_cast<std::string>("send number:"));
            if(err_check!=0)
            {
                return -1;
            }
            rec = pi.recieve_msg();
            if( rec.c_str() != NULL )
            {
                seg0.write_number(rec);
            }
        }
    }    

    return 0;
}
