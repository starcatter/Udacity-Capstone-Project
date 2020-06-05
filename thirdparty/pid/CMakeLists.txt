project("PID")

add_library(pid)
target_sources(pid PUBLIC pid.h PRIVATE pid.cpp)
