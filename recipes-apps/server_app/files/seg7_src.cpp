#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "seg7_header.hpp"

int seg7_display::dev_num = 0;
std::fstream seg7_display::dev_file_handler;

seg7_display::seg7_display(char Copy_index):index(Copy_index),last_number('0')
{
    if( dev_num < 2 )
    {
        dev_num++;
    }
    else
    {
        std::cerr << "can't create more than 2\n";
        throw(dev_num);
    }
}

seg7_display::~seg7_display()
{
    dev_num--;
}

void seg7_display::write_number(std::string number)
{
    if( last_number != number.at(0) )
    {
        number.resize(2);
        number.insert(number.begin(),index);
        dev_file_handler.open(file_path,std::ios::out);
        dev_file_handler.write(number.c_str(),number.size());
        dev_file_handler.close();
        last_number = number.at(1);
    }
}
