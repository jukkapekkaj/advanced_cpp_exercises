#include <iostream>
#include "Big_Data.h"


int main(void)   {
    std::cout << "hello" << std::endl;

    Big_Data a(1024);
    Big_Data b(1024);
    a = a;
    a = b;
    Big_Data c(a);

    std::cout << "end" << std::endl;

    return 0;
}