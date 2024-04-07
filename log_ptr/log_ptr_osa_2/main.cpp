#include <iostream>
#include "Log_Ptr.h"

int main(int arc, char **argv){
    int *test = new int(50);

    std::cout << "scope alkaa" << std::endl;
    {
        Log_Ptr ptr(test);

        std::cout << *ptr << std::endl;
    }
   std::cout << "scope loppui" << std::endl;


    return 0;
}
