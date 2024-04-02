
#ifndef TEHTAVAT_TASKQUEUE_H
#define TEHTAVAT_TASKQUEUE_H

#include "Game_Task.h"
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

class TaskQueue{
public:
    TaskQueue(int nof_threads);
    ~TaskQueue();
    void addJob(Game_Task* task);

private:
    std::vector<std::thread> threads;
    std::queue<Game_Task*> tasks;

    std::mutex mtx;
    //std::mutex queue_mtx;
    std::condition_variable cv;

    void process_job();

    bool run_threads = true;
};

#endif //TEHTAVAT_TASKQUEUE_H
