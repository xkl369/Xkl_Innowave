#include "logger.cpp"
#include <iostream>

int main()
{
    std::cout << "Current MIN_LOG_LEVEL is: " << MIN_LOG_LEVEL << std::endl;
    LOG(INFO,"**** System_Check ****",123);
    std::cout << "Before LOG" << std::endl;
    LOG(INFO,"**** System_Check ****");
    std::cout << "After LOG" << std::endl;
}
