#include "Update_Items.h"
#include <iostream>

void Update_Items::perform() {
    int sum = 0;
    for(size_t i = 0; i < 1000000000; ++i){
        if(i % 2 == 0){
            sum += 5;
        }
        else {
            sum += 1;
        }
    }

    std::cout << "Update items finished" << std::endl;
}
