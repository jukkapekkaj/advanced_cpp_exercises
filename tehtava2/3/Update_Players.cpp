#include "Update_Players.h"
#include <iostream>

void Update_Players::perform() {
    int sum = 0;
    for(size_t i = 0; i < 800000000; ++i){
        if(i % 2 == 0){
            sum += 10;
        }
        else {
            sum += -1;
        }
    }
}
