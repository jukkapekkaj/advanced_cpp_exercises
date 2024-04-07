#include <iostream>
#include "Log_Ptr.h"

void func(Log_Ptr<int> p){
    int k = *p;
}

int main(int arc, char **argv){
    int *n1 = new int(50);;
    int *n2 = new int(1000);
    double *d1 = new double(900000.0);
    double *d2 = new double(1.0);


    {
        std::cout << "scope1 alkaa" << std::endl;
        Log_Ptr n1_ptr(n1);
        Log_Ptr n2_ptr(n2);
        Log_Ptr d1_ptr1(d1);
        Log_Ptr d2_ptr1(d2);

        std::cout << *n1_ptr << std::endl;
        {
            std::cout << "scope2 alkaa" << std::endl;
            Log_Ptr ptr1(n1_ptr);
            Log_Ptr ptr2 = ptr1;
            int k = *ptr1 + *ptr2;
            std::cout << k << std::endl;

            std::cout << "Calling function" << std::endl;
            func(ptr1);
            std::cout << "Function call returned" << std::endl;

            std::cout << "assigning ptr2 = n2_ptr" << std::endl;
            ptr2 = n2_ptr;
            std::cout << *ptr2 << std::endl;

            Log_Ptr d1_ptr2(d1_ptr1);

            std::cout << "assigning d1_ptr2 = d2_ptr1" << std::endl;
            d1_ptr2 = d2_ptr1;

            std::cout << *d1_ptr2 << std::endl;

            std::cout << "scope2 loppuu" << std::endl;
        }
        std::cout << "scope1 loppuu" << std::endl;
    }

    return 0;
}
