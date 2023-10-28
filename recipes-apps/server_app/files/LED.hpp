#ifndef LED_H
#define LED_H

#pragma once

enum LED_STATUS : uint8_t
{
    OFF=0,
    ON=255
};

class LED
{
private:
    const std::string file_path ;
    LED_STATUS status;
    uint8_t Pin_number;
    std::fstream dev_file_handler;
public:
    LED(LED_STATUS init_status,uint8_t CopY_num);
    ~LED();

    void LED_ON(void);
    void LED_OFF(void);
    void LED_TOG(void);
    LED_STATUS LED_GET_Status(void);
};

#endif