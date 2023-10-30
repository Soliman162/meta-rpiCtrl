#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <threads.h>

#include "seg7_header.hpp"
#include "server.hpp"
#include "LED.hpp"

int main(void)
{
    server pi;
    std::string rec ;
    std::string delayTime;
    seg7_display seg0('0');
    seg7_display seg1('1');


    LED led5(OFF,5);
    LED led6(OFF,6);
    LED led13(OFF,13);
    LED led19(OFF,19);

    // LED *Leds_arr[4] = {&led5,&led6,&led13,&led19};
    
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

        switch (rec.at(0))
        {
            case '1':
            case '2':
                seg_index = rec.at(0) - '1';
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
            case '3':
                std::cout << "send number: \n";
                pi.send_msg(static_cast<std::string>("send LED number (5,6,13,19):\n"));
                /*recive number*/
                rec = pi.recieve_msg();
                if( rec == led5.Get_pinNumber() )
                {
                    led5.LED_ON();
                }else if( rec == led6.Get_pinNumber() )
                {
                    led6.LED_ON();
                }else if( rec == led6.Get_pinNumber() )
                {   
                    led13.LED_ON();
                }else if( rec == led6.Get_pinNumber() )
                {   
                    led19.LED_ON();
                }
                else
                {
                   pi.send_msg(static_cast<std::string>("Invalid LED number\n")); 
                }
                break;
            case '4':
                std::cout << "send number: \n";
                pi.send_msg(static_cast<std::string>("send LED number (5,6,13,19):\n"));
                /*recive number*/
                rec = pi.recieve_msg();
                if( rec == led6.Get_pinNumber() )
                {
                    led5.LED_OFF();
                }else if( rec == led6.Get_pinNumber() )
                {
                    led6.LED_OFF();
                }else if( rec == led6.Get_pinNumber() )
                {   
                    led13.LED_OFF();
                }else if( rec == led6.Get_pinNumber() )
                {   
                    led19.LED_OFF();
                }
                else
                {
                   pi.send_msg(static_cast<std::string>("Invalid LED number\n")); 
                }
                break;
            case '5':
                std::cout << "send number: \n";
                pi.send_msg(static_cast<std::string>("send LED number (5,6,13,19):\n"));
                /*recive number*/
                rec = pi.recieve_msg();
                if( rec == led6.Get_pinNumber() )
                {
                    led5.LED_TOG();
                }else if( rec == led6.Get_pinNumber() )
                {
                    led6.LED_TOG();
                }else if( rec == led6.Get_pinNumber() )
                {   
                    led13.LED_TOG();
                }else if( rec == led6.Get_pinNumber() )
                {   
                    led19.LED_TOG();
                }
                else
                {
                   pi.send_msg(static_cast<std::string>("Invalid LED number\n")); 
                }
                break;
            case '6':
                std::cout << "send number: \n";
                pi.send_msg(static_cast<std::string>("send LED number (5,6,13,19):\n"));
                /*recive number*/
                rec = pi.recieve_msg();
                pi.send_msg(static_cast<std::string>("send on time - off time. ex(10-5):\n"));
                delayTime = pi.recieve_msg();
                OnTime = std::stoi(delayTime.substr(0,delayTime.find('-')));
                OffTime = std::stoi(delayTime.substr(delayTime.find('-') + 1));
                if( rec == led6.Get_pinNumber() )
                {
                    led5.LED_TOG(OnTime,OffTime);
                }else if( rec == led6.Get_pinNumber() )
                {
                    led6.LED_TOG(OnTime,OffTime);
                }else if( rec == led6.Get_pinNumber() )
                {   
                    led13.LED_TOG(OnTime,OffTime);
                }else if( rec == led6.Get_pinNumber() )
                {   
                    led19.LED_TOG(OnTime,OffTime);
                }
                else
                {
                   pi.send_msg(static_cast<std::string>("Invalid LED number\n")); 
                }
                break;
            case '7':
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
