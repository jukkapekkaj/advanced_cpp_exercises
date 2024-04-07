
#ifndef TEHTAVAT_LOG_PTR_H
#define TEHTAVAT_LOG_PTR_H

#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cstdio>
#include <sstream>

template <typename T>
class Log_Ptr {
public:
    explicit Log_Ptr(T *t) : ptr(t), ref(new int(1)){
        log("omistajuus siirretty");
    }

    Log_Ptr(const Log_Ptr &t) : ptr(t.ptr), ref(t.ref){
        *ref += 1;
        log("omistajuus kopioitu (konstruktori)");
    };

    Log_Ptr& operator=(Log_Ptr other) {
        this->swap(other);;
        log("omistajuus kopioitu (sijoitus)");
        return *this;

    }

    ~Log_Ptr(){
        *ref -= 1;
        if(*ref == 0){
            delete ptr;
            delete ref;
            log("DESTRUCTOR: olio tuhottu");
        }
        else {
            std::ostringstream oss;
            oss << "DESTRUCTOR: ref vahennetty: " << *ref + 1 << " -> " << *ref << " ";
            log(oss.str());
        }

    }

    T* operator->(){
        log("operator->");
        return ptr;
    }

    T& operator*() {
        log("operator*");
        return *ptr;
    }

private:
    T *ptr;
    int *ref;
    long get_time_stamp() const{
        auto time = std::chrono::system_clock::now(); // get the current time
        auto since_epoch = time.time_since_epoch(); // get the duration since epoch
        auto micros = std::chrono::duration_cast<std::chrono::microseconds>(since_epoch);
        return micros.count();
    }

    void log(const std::string &msg) const {
        std::printf("\t%li\t%-50s%p\n", get_time_stamp(), msg.c_str(), ptr);
    }

    void swap(Log_Ptr &other){
        std::swap(this->ptr, other.ptr);
        std::swap(this->ref, other.ref);
    }

};




#endif //TEHTAVAT_LOG_PTR_H
