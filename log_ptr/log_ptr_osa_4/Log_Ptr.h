
#ifndef TEHTAVAT_LOG_PTR_H
#define TEHTAVAT_LOG_PTR_H

#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cstdio>
#include <sstream>
#include <mutex>

template <typename T>
class Log_Ptr {
public:
    explicit Log_Ptr(T *t) : ptr(t), ref(new int(1)){
        ref_mtx = new std::mutex;
        log("omistajuus siirretty");
    }

    Log_Ptr(const Log_Ptr &t) : ptr(t.ptr), ref(t.ref), ref_mtx(t.ref_mtx){
        std::lock_guard<std::mutex> lock(*ref_mtx);
        *ref += 1;;
        log("omistajuus kopioitu (konstruktori)");
    }

    Log_Ptr& operator=(Log_Ptr other) {
        // Destructor cleans up resources that *this managed after scope ends and 'Log_Ptr other' is destroyed
        this->swap(other);
        log("omistajuus kopioitu (sijoitus)");
        return *this;
    }

    ~Log_Ptr(){
        std::unique_lock<std::mutex> lock(*ref_mtx);
        *ref -= 1;
        if(*ref == 0){
            delete ptr;
            delete ref;
            // Reference count is 0, so it's safe to release lock. Mutex has to be released before its destructor is called
            lock.unlock();
            delete ref_mtx;
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
    std::mutex *ref_mtx;
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
        std::swap(this->ref_mtx, other.ref_mtx);
    }

};

#endif //TEHTAVAT_LOG_PTR_H
