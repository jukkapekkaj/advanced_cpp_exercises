#include "TaskQueue.h"
#include <iostream>

TaskQueue::TaskQueue(int nof_threads){
    for(int i = 0; i < nof_threads; ++i){
        threads.emplace_back(&TaskQueue::process_job, this);
    }
}

TaskQueue::~TaskQueue(){
    std::unique_lock<std::mutex> lock(mtx);
    while(!tasks.empty()){
        tasks.pop();
    }
    run_threads = false;
    cv.notify_all();
    lock.unlock();

    for(auto &t : threads){
        t.join();
    }

}

void TaskQueue::addJob(Game_Task* task){
    std::unique_lock<std::mutex> lock(mtx);
    if(run_threads){
        tasks.push(task);
        cv.notify_one();
    }
}

void TaskQueue::process_job(){
    while(true){
        std::unique_lock<std::mutex> lock(mtx);
        while(tasks.empty() && run_threads){
            cv.wait(lock);
        }

        if(!run_threads){
            break; // Stop thread
        }
        Game_Task *t = tasks.front();
        tasks.pop();
        // Unlock before starting to perform task so other threads can take tasks from queue/ new tasks can be added to queue
        lock.unlock();
        t->perform();
    }

}
