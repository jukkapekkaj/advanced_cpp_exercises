#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex lock;

void sum(const std::vector<int> &vec, size_t start, size_t end, int &sum){
    int temp_sum = 0;
    for(; start < end; ++start){
        temp_sum += vec[start];
    }
    std::lock_guard<std::mutex> g(lock);
    sum += temp_sum;
}


int main() {

    std::vector<int> vec(556341498, 1);
    std::vector<std::thread> threads;
    int result = 0;

    unsigned int nr_threads_available = std::thread::hardware_concurrency(); // This could return 0!
    if(nr_threads_available == 0){
        nr_threads_available = 1;
    }

    // Start new threads and give each equal amount of tasks to perform
    size_t start = 0;
    size_t end = 0;
    int i = 0;
    for(; i < (nr_threads_available - 1); i++){
        // Calculate how many numbers each thread needs to sum
        int tasks_for_this_thread = vec.size() / nr_threads_available + (i < (vec.size() % nr_threads_available) ? 1 : 0);

        end += tasks_for_this_thread;

        std::cout << "Tasks for this thread: " << tasks_for_this_thread << ", start: " << start << ", end: " << end << std::endl;
        if(tasks_for_this_thread > 0){
            threads.emplace_back(sum, std::ref(vec), start, end, std::ref(result));
        }
        start += tasks_for_this_thread;
    }

    // Main thread sums last numbers
    int tasks_for_this_thread = vec.size() / nr_threads_available + (i < (vec.size() % nr_threads_available) ? 1 : 0);

    if(tasks_for_this_thread > 0){
        std::cout << "Tasks for main thread: " << tasks_for_this_thread << ", start: " << start << ", end: " << vec.size() << std::endl;
        sum(vec, start, vec.size(), std::ref(result));
    }

    for(auto &t : threads){
        t.join();
    }
    std::cout << "Sum: " << result << std::endl;


    return 0;
}
