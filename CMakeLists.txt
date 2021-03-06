CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
 
PROJECT(cachetest)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib)

SET(GOOGLETEST_HOME $ENV{GOOGLETEST_HOME})

ADD_COMPILE_OPTIONS(-g3 -Wall -fPIC -O3 -std=c++11)
SET(SRCS
    ./test.cpp
)

INCLUDE_DIRECTORIES(
    ${GOOGLETEST_HOME}/include
)

LINK_DIRECTORIES(
    ${GOOGLETEST_HOME}
)

ADD_EXECUTABLE(lruTest ${SRCS})
TARGET_LINK_LIBRARIES(lruTest
    ${GOOGLETEST_HOME}/libgtest.a
    ${GOOGLETEST_HOME}/libgtest_main.a
    pthread
)

ENABLE_TESTING()
ADD_TEST(NAME lruTest COMMAND lruTest --gtest_output=xml:LRUTest.xml)
