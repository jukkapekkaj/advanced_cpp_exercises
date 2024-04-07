#include <iostream>
#include "Log_Ptr.h"

void func(Log_Ptr<int> p){
    int k = *p;
}

int main(int arc, char **argv){
    int *n1 = new int(50);;
    int *n2 = new int(1000);


    {
        std::cout << "scope1 alkaa" << std::endl;
        Log_Ptr n1_ptr1(n1);
        Log_Ptr n2_ptr1(n2);

        std::cout << *n1_ptr1 << std::endl;
        {
            std::cout << "scope2 alkaa" << std::endl;
            Log_Ptr n1_ptr2(n1_ptr1);
            Log_Ptr n1_ptr3 = n1_ptr2;
            std::cout << *n1_ptr2 + *n1_ptr3 << std::endl;
            std::cout << "Calling function" << std::endl;
            func(n1_ptr2);
            std::cout << "Function call returned" << std::endl;

            std::cout << "assigning n1_ptr2 = n2_ptr1" << std::endl;
            n1_ptr2 = n2_ptr1;

            std::cout << "scope2 loppuu" << std::endl;
        }

        std::cout << "scope1 loppuu" << std::endl;
    }


    return 0;
}
