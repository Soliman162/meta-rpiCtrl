#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include<iterator>  
#include<vector> 

#include "seg7_header.hpp"
#include "server.hpp"
#include "LED.hpp"

#define OP_SET_SEGMENT0         '1'
#define OP_SET_SEGMENT1         '2'
#define OP_LED_ON               '3'
#define OP_LED_OFF              '4'
#define OP_LED_FLASH            '5'
#define OP_TURN_OFF_CONNECTION  '6'   

#define LED_NUMBER_5        5
#define LED_NUMBER_6        6
#define LED_NUMBER_13       13
#define LED_NUMBER_19       19

int main(void)
{
    char OP_number;
    int pin_number {0};

    server pi;
    std::string rec(pi.Get_bufferSize(),'\0');
    std::string delayTime(pi.Get_bufferSize(),'\0');

    LED led5(OFF,LED_NUMBER_5);
    LED led6(OFF,LED_NUMBER_6);
    LED led13(OFF,LED_NUMBER_13);
    LED led19(OFF,LED_NUMBER_19);
      
    seg7_display seg0('0');
    seg7_display seg1('1');

    std::vector<LED> Vled = {led5,led6,led13,led19};
    std::vector<LED>::iterator ptr;
    
    int OnTime{0};
    int OffTime{0};
    int seg_index{0};
    const std::string commands_msg =    "/*****choose operation*******/ \n"
                                        "1- Set 7 Segment0              \n"
                                        "2- Set 7 Segment1              \n"
                                        "3- Turn LED ON                 \n"
                                        "4- Turn LED OFF                \n"
                                        "5- Flash LED                   \n"
                                        "6- Turn off connection         \n";

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
                }
                else
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
                pin_number = std::stoi(rec);
                for(ptr=Vled.begin();ptr<Vled.end();ptr++)
                {
                    if( pin_number == ptr->Get_pinNumber() )
                    {
                        if( OP_number == OP_LED_ON )
                        {
                            ptr->LED_ON();
                        } 
                        else
                        {
                            ptr->LED_OFF();
                        }
                        break;
                    }
                }
                if(ptr==Vled.end())
                {
                    pi.send_msg(static_cast<std::string>("Invalid LED number\n"));
                }
                break;
            case OP_LED_FLASH:
                std::cout << "send number: \n";
                pi.send_msg(static_cast<std::string>("send LED number (5,6,13,19):\n"));
                /*recive number*/
                rec = pi.recieve_msg();
                pin_number = std::stoi(rec);
                for(ptr=Vled.begin();ptr<Vled.end();ptr++)
                {
                    if( pin_number == ptr->Get_pinNumber() )
                    {
                        pi.send_msg(static_cast<std::string>("send on time - off time. ex(1000-500):\n"));
                        delayTime = pi.recieve_msg();
                        OnTime = std::stoi(delayTime.substr(0,delayTime.find('-')));
                        OffTime = std::stoi(delayTime.substr(delayTime.find('-') + 1));
                        ptr->LED_TOG(OnTime,OffTime);
                        break;
                    }
                }
                if(ptr==Vled.end())
                {
                    pi.send_msg(static_cast<std::string>("Invalid LED number\n"));
                }
                break;
            case OP_TURN_OFF_CONNECTION:
                pi.send_msg(static_cast<std::string>("Turn off connection\n"));
                for(ptr=Vled.begin();ptr<Vled.end();ptr++)
                {
                    ptr->~LED();
                }
                seg0.~seg7_display();
                seg1.~seg7_display();
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
