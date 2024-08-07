project(Udapp)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib")

add_subdirectory(Udsys)
add_subdirectory(Udbas)
add_subdirectory(Udlib)
add_subdirectory(Udext)

add_subdirectory(Udapp)

target_link_libraries(udbas PRIVATE udsys)
target_link_libraries(udlib INTERFACE udbas)
target_link_libraries(udapp PUBLIC udlib udext)
