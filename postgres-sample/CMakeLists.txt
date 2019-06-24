cmake_minimum_required(VERSION 2.8)
project(uma_dummy_race CXX)

set(CMAKE_CXX_STANDARD, 14)
set(CMAKE_CXX_FLAGS "-Wextra -Wall")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_executable(pqxx_sample pqxx_sample.cpp)

target_link_libraries(pqxx_sample ${PQXX_LIB} ${PQ_LIB})
