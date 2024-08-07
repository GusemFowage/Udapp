cmake_minimum_required(VERSION 3.28)

project(Udapp)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall)

set(INLCUDE_DIRS "./include")
include_directories(${INLCUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../app)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../app)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../app)

add_subdirectory(source)
add_subdirectory(demo)

target_link_libraries(demo PUBLIC udapp udbas)