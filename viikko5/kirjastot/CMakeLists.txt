add_executable(kirjastot main.cpp)

include_directories(C:/Users/jpj1/Opiskelu/3_vuosi/advanced_cpp/box2d/include/box2d)
target_link_libraries(kirjastot C:/Users/jpj1/Opiskelu/3_vuosi/advanced_cpp/box2d/build/bin/Debug/box2d.lib)

include_directories(C:/Users/jpj1/Opiskelu/3_vuosi/advanced_cpp/SDL2/SDL/include)
target_link_libraries(kirjastot C:/Users/jpj1/Opiskelu/3_vuosi/advanced_cpp/SDL2/SDL/build/Debug/SDL3.lib)