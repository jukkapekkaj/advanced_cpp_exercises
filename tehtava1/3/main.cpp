#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "Game_Task.h"
#include "Update_Items.h"
#include "Update_Players.h"
#include "Draw_Map.h"

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

    std::vector<std::thread> threads;

    unsigned int nr_threads_available = std::thread::hardware_concurrency(); // This could return 0!
    if(nr_threads_available == 0){
        nr_threads_available = 1;
    }

#if 0 // Test performace with one thread only
    nr_threads_available = 1;
#endif

    // Start new threads and give each equal amount of tasks to perform
    size_t start = 0;
    size_t end = 0;
    int i = 0;
    for(; i < (nr_threads_available - 1); i++){
        // Calculate how many tasks each thread needs to perform
        int tasks_for_this_thread = tasks.size() / nr_threads_available + (i < (tasks.size() % nr_threads_available) ? 1 : 0);

        end += tasks_for_this_thread;

        std::cout << "Tasks for this thread: " << tasks_for_this_thread << ", start: " << start << ", end: " << end << std::endl;
        if(tasks_for_this_thread > 0){
            threads.emplace_back(process, std::ref(tasks), start, end);
        }
        start += tasks_for_this_thread;
    }

    // Main thread performs last tasks
    int tasks_for_this_thread = tasks.size() / nr_threads_available + (i < (tasks.size() % nr_threads_available) ? 1 : 0);

    if(tasks_for_this_thread > 0){
        std::cout << "Tasks for main thread: " << tasks_for_this_thread << ", start: " << start << ", end: " << tasks.size() << std::endl;
        process(tasks, start, tasks.size());
    }


    for(auto &t : threads){
        t.join();
    }

    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << ms_int.count() / 1000 << " seconds"<< std::endl;

}
