#include "Draw_Map.h"
#include <iostream>


void Draw_Map::perform() {
    int sum = 0;
    for(size_t i = 0; i < 1000500000; ++i){
        if(i % 2 == 0){
            sum += -10;
        }
        else {
            sum += 5;
        }
    }
}
