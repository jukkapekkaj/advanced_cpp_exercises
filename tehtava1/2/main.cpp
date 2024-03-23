#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex lock;

void deposit(int amount, size_t count, int &sum){
    for(size_t i = 0; i < count; ++i){
        std::lock_guard<std::mutex> g(lock);
        sum += amount;
    }
}

void withdraw(int amount, size_t count, int &sum){
    for(size_t i = 0; i < count; ++i){
        std::lock_guard<std::mutex> g(lock);
        sum -= amount;
    }
}


int main() {
    int result = 0;

    int deposit_amount = 2;
    int deposit_count = 4534603;

    int withdraw_amount = 1;
    int withdraw_count = 203805;

    std::thread t1(deposit, deposit_amount, deposit_count, std::ref(result));
    std::thread t2(withdraw, withdraw_amount, withdraw_count, std::ref(result));


    t1.join();
    t2.join();

    std::cout << "Result: " << result << std::endl;
    std::cout << "Should be: " << (deposit_amount * deposit_count) - (withdraw_amount * withdraw_count) << std::endl;



    return 0;
}
