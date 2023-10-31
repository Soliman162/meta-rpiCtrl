#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "LED.hpp"

#define File_Path_string(CopY_num) ("/sys/class/leds/led" + std::to_string(CopY_num) + "/brightness")
#define DELAYON_FILE_PATH(CopY_num) ("/sys/class/leds/led" + std::to_string(CopY_num) + "/delay_on")
#define DELAYOFF_FILE_PATH(CopY_num) ("/sys/class/leds/led" + std::to_string(CopY_num) + "/delay_off")
#define TRIGGER_FILE_PATH(CopY_num) ("/sys/class/leds/led" + std::to_string(CopY_num) + "/trigger")

std::fstream dev_file_handler;

void File_Write(const std::string file_Path, std::string Value )
{
    dev_file_handler.open(file_Path,std::ios::out);
    dev_file_handler.write(Value.c_str(),Value.size());
    dev_file_handler.close();  
    dev_file_handler.clear();
}

LED::LED(LED_STATUS init_status,uint8_t CopY_num):status(init_status),Pin_number(CopY_num)
                                                ,brightness_file_path(File_Path_string(CopY_num))
                                                ,delayON_file_path(DELAYON_FILE_PATH(CopY_num))
                                                ,delayOFF_file_path(DELAYOFF_FILE_PATH(CopY_num))
                                                ,Trigger_file_path(TRIGGER_FILE_PATH(CopY_num))
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
    Timer_Disable();
    LED_OFF();
}

void LED::Timer_enable(void)
{
    File_Write(Trigger_file_path,"timer");
    Timer_status = TIMER_ENABLE;
}
void LED::Timer_Disable(void)
{
    File_Write(Trigger_file_path,"none");
    status = OFF;
    Timer_status = TIMER_DISABLE;
}

void LED::LED_ON(void)
{
    std::string Value = std::to_string(ON);
    Timer_Disable();
    File_Write(brightness_file_path,Value);
    status = ON;
}
void LED::LED_OFF(void)
{
    std::string Value = std::to_string(OFF);
    Timer_Disable();
    File_Write(brightness_file_path,Value); 
    status = OFF;
}
void LED::LED_TOG(int ON_time, int OFF_time)
{
    Timer_enable();
    File_Write(delayON_file_path,std::to_string(ON_time));
    File_Write(delayOFF_file_path,std::to_string(OFF_time));
}

std::string LED::Get_pinNumber(void)
{
    return std::to_string(Pin_number);
}
