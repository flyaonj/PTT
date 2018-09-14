PROJECT(COMM)

cmake_minimum_required(VERSION 2.0.0)

set(LIBCO_INCLUDE libco)
set(REDIS_INCLUDE hiredispool hiredispool/hiredis)
set(POCO_INCLUDE Poco/Foundation/include Poco/Net/include Poco/Util/include) 
set(LOG4CPP_INCLUDE log4cpp/include)
set(FRAME_INCLUDE frame/include)
set(PUB_INCLUDE pub/include)


SET(BUILD_BASE_DIR ${COMM_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH  ${COMM_SOURCE_DIR}/deploy/bin)
SET(LIBRARY_OUTPUT_PATH   ${COMM_SOURCE_DIR}/deploy/lib)

include_directories(${POCO_INCLUDE} ${FRAME_INCLUDE} ${PUB_INCLUDE} ${LIBCO_INCLUDE} ${REDIS_INCLUDE})

link_directories(/usr/local/lib ${LIBRARY_OUTPUT_PATH} ../lib ./lib)


MESSAGE(STATUS "DIR=" ${COMM_SOURCE_DIR})

subdirs(frame
)