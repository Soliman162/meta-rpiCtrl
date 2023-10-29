#ifndef LED_H
#define LED_H

#pragma once

enum LED_STATUS : uint8_t
{
    OFF=0,
    ON=255
};

/* Timer status */
#define TIMER_ENABLE   1
#define TIMER_DISABLE  0

class LED
{
private:
    const std::string brightness_file_path ;
    const std::string delayON_file_path ;
    const std::string delayOFF_file_path ;
    const std::string Trigger_file_path ;
    LED_STATUS status;
    uint8_t Timer_status;
    uint8_t Pin_number;
    static std::fstream dev_file_handler;
    void Timer_enable(void);
    void Timer_Disable(void);

public:
    LED(LED_STATUS init_status,uint8_t CopY_num);
    ~LED();

    void LED_ON(void);
    void LED_OFF(void);
    void LED_TOG(void);
    void LED_TOG(int ON_time, int OFF_time);

    std::string Get_pinNumber(void);
};

#endif