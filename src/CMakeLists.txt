SET(HEADER_LIST ${PROJECT_SOURCE_DIR}/include/sys_prog.h)
SET(SOURCE_LIST ${PROJECT_SOURCE_DIR}/src/sys_prog.cpp)
add_library(systems_lib ${SOURCE_LIST} ${HEADER_LIST})