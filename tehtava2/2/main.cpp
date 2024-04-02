#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <numeric>
#include <algorithm>
#include <execution>



int main() {

    std::vector<int> vec(300'000'000);

    std::iota(vec.begin(), vec.end(), 0);

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

//    std::for_each(std::execution::seq, vec.begin(), vec.end(), [](int &n) {++n;});
//    std::for_each(std::execution::par, vec.begin(), vec.end(), [](int &n) {++n;});
    std::for_each(std::execution::par, vec.begin(), vec.end(), [](int &n) {++n;});

    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << ms_int.count() << " ms"<< std::endl;


    return 0;
}
