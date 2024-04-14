#include <iostream>
#include "Big_Data.h"


int main(void)   {
    std::cout << "hello" << std::endl;

    Big_Data a(Big_Data(1024));
    Big_Data b(1024);
    b = Big_Data(1024);
    Big_Data c(std::move(a));

    std::cout << "end" << std::endl;

    return 0;
}