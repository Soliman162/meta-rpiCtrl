#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "LED.hpp"

#define File_Path_string(CopY_num) ("/sys/class/leds/led" + std::to_string(CopY_num) + "/brightness")

LED::LED(LED_STATUS init_status,uint8_t CopY_num):status(init_status),Pin_number(CopY_num),file_path(File_Path_string(CopY_num))
{
    if( status == ON )
    {
        LED_ON();
    }
    else
    {
        LED_OFF();
    }
}

LED::~LED()
{
    LED_OFF();
}

void LED::LED_ON(void)
{
    std::string Value = std::to_string(ON);
    dev_file_handler.open(file_path,std::ios::out);
    dev_file_handler.write(Value.c_str(),Value.size());
    dev_file_handler.close();   
    status = ON;
}
void LED::LED_OFF(void)
{
    std::string Value = std::to_string(OFF);
    dev_file_handler.open(file_path,std::ios::out);
    dev_file_handler.write(Value.c_str(),Value.size());
    dev_file_handler.close();   
    status = OFF;
}

void LED::LED_TOG(void)
{
    std::string Value = std::to_string(~status);
    dev_file_handler.open(file_path,std::ios::out);
    dev_file_handler.write(Value.c_str(),Value.size());
    dev_file_handler.close();   
    status = static_cast<LED_STATUS>(~status); 
}

LED_STATUS LED::LED_GET_Status(void)
{
    return status;
}
