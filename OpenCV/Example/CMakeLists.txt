cmake_minimum_required(VERSION 3.16)
project(opencv_cpp_basic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(01_helloWorld part1/01.helloWorld.cpp)
target_link_libraries(01_helloWorld PRIVATE ${OpenCV_LIBS})

add_executable(02_basicOp part1/02.basicOp.cpp)
target_link_libraries(02_basicOp PRIVATE ${OpenCV_LIBS})


add_executable(03_MatOP part1/03.MatOP.cpp)
target_link_libraries(03_MatOP PRIVATE ${OpenCV_LIBS})