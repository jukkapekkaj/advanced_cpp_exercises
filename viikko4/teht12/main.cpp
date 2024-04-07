#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

class SortNumbers{
public:
    void operator()(int &n){
        if(n > 100){
            n -= 100;
        }
        else {
            n = 0;
        }
    }
};

void func(int &n){
    if(n > 100){
        n -= 100;
    }
    else {
        n = 0;
    }
}

void print_numbers(const std::vector<int> &v){
    for(int n : v){
        std::cout << n << " ";
    }
    std::cout << std::endl;;
}

int main(void){

    // Create vectors and fill them with random numbers
    std::vector<int> vec_a;
    std::vector<int> vec_b;
    std::vector<int> vec_c;
    std::vector<int> vec_d;

    srand (time(NULL));
    for(int i = 0; i < 10000; i++){
        int n = rand() % 500 + 1;;
        vec_a.push_back(n);
        vec_b.push_back(n);
        vec_c.push_back(n);
        vec_d.push_back(n);
    }


    // Modify values in vectors with different styles
    std::for_each(vec_a.begin(), vec_a.end(), func);              // A
    std::for_each(vec_b.begin(), vec_b.end(), SortNumbers());     // B
    std::for_each(vec_c.begin(), vec_c.end(), [] (int &n) {       // C
        if(n > 100){
            n -= 100;
        }
        else {
            n = 0;
        }
    });

    auto reduce_health = [] (int &n) {
        if(n > 100){
            n -= 100;
        }
        else {
            n = 0;
        }
    };
    std::for_each(vec_d.begin(), vec_d.end(), reduce_health);     // D

    // Sort and print results
    std::sort(vec_a.begin(), vec_a.end(), [](int n1, int n2) {return n1 > n2;});
    std::sort(vec_b.begin(), vec_b.end(), [](int n1, int n2) {return n1 > n2;});
    std::sort(vec_c.begin(), vec_c.end(), [](int n1, int n2) {return n1 > n2;});
    std::sort(vec_d.begin(), vec_d.end(), [](int n1, int n2) {return n1 > n2;});

    print_numbers(vec_a);
    print_numbers(vec_b);
    print_numbers(vec_c);
    print_numbers(vec_d);

    return 0;
}
