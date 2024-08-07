project(Udapp-lib)

file(GLOB_RECURSE SOURCES *.cpp)

add_library(udlib SHARED ${SOURCES})