cmake_minimum_required(VERSION 3.17)
project(webserver)
set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

add_subdirectory(fmt REQUIRED)
add_subdirectory(restinio/dev REDUIRED)

find_package(Catch2 REQUIRED)

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

find_package(Boost 1.72.0 COMPONENTS system timer REQUIRED)


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()



add_executable(webserver main.cpp)

target_link_libraries(webserver ${Boost_LIBRARIES} restinio::restinio pthread Catch2::Catch2 pqxx pq)