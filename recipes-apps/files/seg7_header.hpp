#ifndef SEG7_HEADER
#define SEG7_HEADER

#pragma once

class seg7_display
{
private:
    /* data */
    static int dev_num;
    int index;
    std::string last_number = "0";
    std::fstream dev_file_handler;
    const std::string file_path = "/dev/7_segDisplay";
public:
    seg7_display(int Copy_index);
    ~seg7_display();
    void write_number(std::string number);
};





#endif