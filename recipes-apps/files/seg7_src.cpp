#include <iostream>
#include <fstream>
#include <string.h>
#include "seg7_header.hpp"

int seg7_display::dev_num = 0;

seg7_display::seg7_display(/* args */)
{
    dev_num++;
}

seg7_display::~seg7_display()
{
    dev_num--;
}

void seg7_display::write_number(std::string number)
{
    dev_file_handler.open(file_path,std::ios::out);
    dev_file_handler.write(number.c_str(),number.size());
    dev_file_handler.close();
}

