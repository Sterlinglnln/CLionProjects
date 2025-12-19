cmake_minimum_required(VERSION 4.0)
project(test)

set(CMAKE_CXX_STANDARD 20)

find_package(lz4 CONFIG REQUIRED)
find_package(realsense2 CONFIG REQUIRED)

add_executable(test main.cpp)

target_link_libraries(test PRIVATE
        realsense2::realsense2
        lz4::lz4
)
