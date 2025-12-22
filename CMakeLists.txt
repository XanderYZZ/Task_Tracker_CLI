cmake_minimum_required(VERSION 3.28)

project(Task_Tracker_CLI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(Task_Tracker_CLI
    src/main.cpp
    src/File.cpp
    src/Task.cpp
)

target_include_directories(Task_Tracker_CLI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)