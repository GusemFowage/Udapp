project(Udapp-extra)

file(GLOB_RECURSE SOURCES *.cpp)

add_library(udext SHARED ${SOURCES})