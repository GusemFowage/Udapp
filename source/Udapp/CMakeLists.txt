project(Udapp)

file(GLOB_RECURSE SOURCES *.cpp)

add_library(udapp SHARED ${SOURCES})

# add_library(udapp_entry STATIC udentry.c)
# target_link_libraries(udapp PUBLIC udapp_entry)