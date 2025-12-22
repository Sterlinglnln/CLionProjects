cmake_minimum_required(VERSION 4.0)
project(hello_realsense)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# realsense2
find_package(realsense2 CONFIG REQUIRED)
find_package(lz4 CONFIG REQUIRED)

add_executable(hello_realsense main.cpp)

target_link_libraries(hello_realsense PRIVATE
        realsense2::realsense2
        lz4::lz4
)
