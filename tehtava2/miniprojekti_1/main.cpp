#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <future>
#include "Game_Task.h"
#include "Update_Items.h"
#include "Update_Players.h"
#include "Draw_Map.h"
#include "TaskQueue.h"

void process(const std::vector<Game_Task*> &vec, size_t start, size_t end){
    for(; start < end; ++start){
        vec[start]->perform();
    }
}

int main() {

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    std::vector<Game_Task*> tasks;

    {
        TaskQueue q(3);
        tasks.push_back(new Update_Items);
        tasks.push_back(new Update_Players);
        tasks.push_back(new Update_Players);
        tasks.push_back(new Draw_Map);
        tasks.push_back(new Update_Players);
        tasks.push_back(new Update_Players);
        tasks.push_back(new Update_Items);
        tasks.push_back(new Update_Players);
        tasks.push_back(new Update_Items);
        tasks.push_back(new Update_Players);
        tasks.push_back(new Draw_Map);
        tasks.push_back(new Update_Players);
        tasks.push_back(new Update_Items);
        tasks.push_back(new Update_Items);
        tasks.push_back(new Draw_Map);

        std::cout << "\nFirst round of tasks" << std::endl;
        for(int i = 0; i < 7; i++){
            q.addJob(tasks[i]);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        std::cout << "\nSecond round of tasks" << std::endl;

        for(int i = 7; i < tasks.size(); i++){
            q.addJob(tasks[i]);
        }



        std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    }



    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << ms_int.count() / 1000 << " seconds"<< std::endl;

}
