cmake_minimum_required(VERSION 3.16)
project(opencv_cpp_basic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(01_helloWorld part1/01_helloWorld.cpp)
target_link_libraries(01_helloWorld PRIVATE ${OpenCV_LIBS})

add_executable(02_basicOp part1/02_basicOp.cpp)
target_link_libraries(02_basicOp PRIVATE ${OpenCV_LIBS})

add_executable(03_MatOP part1/03_MatOP.cpp)
target_link_libraries(03_MatOP PRIVATE ${OpenCV_LIBS})

add_executable(04_inputArray part1/04_inputArray.cpp)
target_link_libraries(04_inputArray PRIVATE ${OpenCV_LIBS})

add_executable(05_MatOp2 part1/05_MatOp2.cpp)
target_link_libraries(05_MatOp2 PRIVATE ${OpenCV_LIBS})

add_executable(06_video part1/06_video.cpp)
target_link_libraries(06_video PRIVATE ${OpenCV_LIBS})

add_subdirectory(part2)

add_subdirectory(part3)

add_subdirectory(part4)
