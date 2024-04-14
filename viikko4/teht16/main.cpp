#include <iostream>
#include <exception>



int main(void)   {
    std::cout << "hello" << std::endl;
    const size_t nr_elements = 10000;

    size_t counter = 0;
    try {
        // On my machine it takes around 23GB untill allocation fails
        while (true) {
            int* n = new int[nr_elements];
            counter += nr_elements;
        }
    }
    catch (std::bad_alloc& e) { // If new fails, it throws std::bad_alloc
        std::cout << e.what() << std::endl;
        std::cout << "allocated " << counter * sizeof(int) << " bytes";
    }
    return 0;
}