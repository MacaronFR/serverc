cmake_minimum_required(VERSION 3.17)
project(serverc C)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/include/libxml2)
include_directories(include)

add_executable(serverc src/main.c src/merge.c src/utils.c)

target_link_libraries(serverc -lxml2)