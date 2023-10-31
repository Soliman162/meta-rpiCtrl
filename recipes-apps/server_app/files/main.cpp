#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "seg7_header.hpp"
#include "server.hpp"
#include "LED.hpp"

#define OP_SET_SEGMENT0         '1'
#define OP_SET_SEGMENT1         '2'
#define OP_LED_ON               '3'
#define OP_LED_OFF              '4'
#define OP_LED_TOG              '5'
#define OP_LED_FLASH            '6'
#define OP_TURN_OFF_CONNECTION  '7'        

LED led5(OFF,5);
LED led6(OFF,6);
LED led13(OFF,13);
LED led19(OFF,19);

LED* GET_LED(std::string pin_number);

int main(void)
{

    std::string rec ;
    std::string delayTime;

    server pi;
    LED *temp_LED;
    char OP_number;
    seg7_display seg0('0');
    seg7_display seg1('1');
    
    int OnTime{0};
    int OffTime{0};
    int seg_index{0};
    std::string commands_msg =  "/*****choose operation*******/ \n"
                                "1- Set 7 Segment0              \n"
                                "2- Set 7 Segment1              \n"
                                "3- Turn LED ON                 \n"
                                "4- Turn LED OFF                \n"
                                "5- Toggle LED                  \n"
                                "6- Flash LED                   \n"
                                "7- Turn off connection         \n";

    if(pi.server_listen() < 0){return -1;}
    while(true)
    {
        if(pi.send_msg(commands_msg) < 0){return -1;}
        if(pi.send_msg(static_cast<std::string>("send operation number\n"))<0){return -1;}
        /*recive command*/
        rec = pi.recieve_msg();
        OP_number = rec.at(0);
        switch (OP_number)
        {
            case OP_SET_SEGMENT0:
            case OP_SET_SEGMENT1:
                seg_index = OP_number - '1';
                std::cout << "send number: \n";
                pi.send_msg(static_cast<std::string>("send number (0:9):\n"));
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
            case OP_LED_ON:
            case OP_LED_OFF:
                std::cout << "send number: \n";
                pi.send_msg(static_cast<std::string>("send LED number (5,6,13,19):\n"));
                /*recive number*/
                rec = pi.recieve_msg();
                temp_LED = GET_LED(rec);
                if( temp_LED != NULL)
                {
                    OP_number == OP_LED_ON ? temp_LED->LED_ON() : temp_LED->LED_OFF();
                }
                else
                {
                    pi.send_msg(static_cast<std::string>("Invalid LED number\n"));
                }
                break;
            case OP_LED_FLASH:
                std::cout << "send number: \n";
                pi.send_msg(static_cast<std::string>("send LED number (5,6,13,19):\n"));
                /*recive number*/
                rec = pi.recieve_msg();
                temp_LED = GET_LED(rec);
                if( temp_LED != NULL )
                {
                    pi.send_msg(static_cast<std::string>("send on time - off time. ex(1000-500):\n"));
                    delayTime = pi.recieve_msg();
                    OnTime = std::stoi(delayTime.substr(0,delayTime.find('-')));
                    OffTime = std::stoi(delayTime.substr(delayTime.find('-') + 1));
                    temp_LED->LED_TOG(OnTime,OffTime);
                }
                else
                {
                   pi.send_msg(static_cast<std::string>("Invalid LED number\n")); 
                }
                break;
            case OP_TURN_OFF_CONNECTION:
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

LED* GET_LED(std::string pin_number)
{
    if( pin_number == led5.Get_pinNumber() )
    {
        return &led5;
    }else if( pin_number == led6.Get_pinNumber() )
    {
        return &led6;
    }else if( pin_number == led13.Get_pinNumber() )
    {   
        return &led13;
    }else if( pin_number == led19.Get_pinNumber() )
    {   
        return &led19;   
    }
    return NULL;
}
