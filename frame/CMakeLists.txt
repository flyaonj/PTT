cmake_minimum_required(VERSION 2.0.0)

project(frame)

#include_directories( ${POCO_INCLUDE} ${LIBCO_INCLUDE} ${REDIS_INCLUDE} ./include)

SET(SRC_DIR ./source)
SET(SRC_FILES)
SET(EXE_NAME frame)
FILE(GLOB SRC_FILES ${SRC_DIR}/*.cpp)


FILE(GLOB PUB_SRC_FILES)



ADD_DEFINITIONS(
    -DWRITE_TEST
    -Wall -g
)

add_executable(${EXE_NAME} ${SRC_FILES} ${PUB_SRC_FILES})

target_link_libraries(${EXE_NAME} colib PocoFoundation PocoUtil PocoNet hiredis hiredispool log4cpp) 