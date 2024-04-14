#include <iostream>
#include <string>
#include <cstring>
#include <vector>


int main(void)   {
#if 1   // a)
    std::string s1("kissaaaaaaaaaaa");
    std::string s2;
    std::cout << "s1 address: " << &s1 << std::endl;
    std::cout << "s2 address: " << &s2 << std::endl;
    std::cout << "s1 capacity: " << s1.capacity() << std::endl;
    std::cout << "s2 capacity: " << s2.capacity() << std::endl;
    std::cout << "size of s1: " << sizeof s1 << ", s2: " << sizeof s2 << std::endl;
   
    s1 = s2; // s1 is copy of s2, they have diffrent data (or they would have if s2 wasn't empty).

    // I also noticed that before copy, s1 seems to have its data inside the string object. 
    // I searched through online and found that "Small String Optimization" is most likely causing this. 
    // On some implementations of STD, string objects have small array inside them so they can store small strings without allocating memory from heap, making programs much faster.
    // Even s2 size is 40 bytes on my machine and its capacity is 15, so that could be 8 bytes for size, 8 for capacity, 8 for pointer to data, and 16 bytes for characters.

    // Actually after a while I figured out how to open memory view in Visual Studio in debugging mode and here is how string object is laid out in memory on my machine: 
    
    // 0x000000894C9CFB98  a0 c0 77 6f b5 01 00 00  ��wo�...        // Dont know what this is? -> UPDATE: It took a while to figure out but I found out from online that MSVC adds these 8 bytes in Debug build
    // 0x000000894C9CFBA0  6b 69 73 73 61 61 61 61  kissaaaa        // Pointer to data OR Internal array for small strings
    // 0x000000894C9CFBA8  61 61 61 61 61 61 00 00  aaaaaa..        // Array continued...
    // 0x000000894C9CFBB0  0e 00 00 00 00 00 00 00  ........        // Size
    // 0x000000894C9CFBB8  0f 00 00 00 00 00 00 00  ........        // Capacity

    // // After assignment, only size and first byte in internal array changed

    // 0x000000894C9CFB98  a0 c0 77 6f b5 01 00 00   �wo�...
    // 0x000000894C9CFBA0  00 69 73 73 61 61 61 61  .issaaaa
    // 0x000000894C9CFBA8  61 61 61 61 61 61 00 00  aaaaaa..
    // 0x000000894C9CFBB0  00 00 00 00 00 00 00 00  ........
    // 0x000000894C9CFBB8  0f 00 00 00 00 00 00 00  ........

    // After assignment, s1 pointer to data is not null, its size is simply set to 0, and internal buffers first byte is set to 0

    std::cout << "end" << std::endl;

#elif 0     // b)
    std::string s1("kissa");
    std::string s2;

    std::cout << "s1 address: " << &s1 << std::endl;
    std::cout << "s2 address: " << &s2 << std::endl;
    
    s1 = std::move(s2);
    // With move operation, pointer to data is set to nullptr (so pointer from s2 is copied to s1), also size is set to 0 since its also copied from s2.
    std::cout << "end" << std::endl;

#else       // c)

    std::vector<std::string> vec;
    std::string s3("koira");
    std::cout << "s3 address: " << &s3 << std::endl;

    // Copy of s3 is created
    vec.push_back(s3);
   

    vec[0].append("hello");
    std::cout << vec[0] << std::endl;
    std::cout << s3 << std::endl;

    // New object in vector now owns content of s3. s3's pointer/internal buffers first byte and size is set to 0
    vec.push_back(std::move(s3));
  

    std::cout << "end" << std::endl;


#endif
 
  
   
 




    return 0;
}