
#ifndef TEHTAVAT_LOG_PTR_H
#define TEHTAVAT_LOG_PTR_H

#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cstdio>

template <typename T>
class Log_Ptr {
public:
    explicit Log_Ptr(T *t) : ptr(t){
        log("omistajuus siirretty");
    }

    Log_Ptr(const Log_Ptr &t) = delete;
    Log_Ptr& operator=(const Log_Ptr& t) = delete;

    ~Log_Ptr(){
        delete ptr;
        log("olio tuhottu");
    }

private:
    T *ptr;
    long get_time_stamp() const{
        auto time = std::chrono::system_clock::now(); // get the current time
        auto since_epoch = time.time_since_epoch(); // get the duration since epoch
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
        return millis.count();
    }

    void log(const std::string &msg) const {
        std::cout << get_time_stamp() << " " << msg << " " << ptr << std::endl;
    }

};




#endif //TEHTAVAT_LOG_PTR_H
