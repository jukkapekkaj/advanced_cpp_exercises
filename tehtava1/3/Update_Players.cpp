#include "Update_Players.h"
#include <iostream>

void Update_Players::perform() {
    int sum = 0;
    for(size_t i = 0; i < 1000000000; ++i){
        if(i % 2 == 0){
            sum += 10;
        }
        else {
            sum += -1;
        }
    }

    std::cout << "Update_Players done" << std::endl;
}
