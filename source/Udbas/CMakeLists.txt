project(udapp-bas)

file(GLOB_RECURSE SOURCES *.cpp)

add_library(udbas SHARED ${SOURCES})