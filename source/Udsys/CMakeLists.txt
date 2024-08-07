project(Udapp-sys)

file(GLOB_RECURSE SOURCES *.c)
file(GLOB_RECURSE HEADERS ${INLCUDE_DIRS}/Udsys/*.h)

add_library(udsys SHARED ${SOURCES} ${HEADERS})