cmake_minimum_required(VERSION 3.16)
project(webserver)
set(CMAKE_CXX_STANDARD 17) #

set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(unofficial-http-parser REQUIRED)
find_package(fmt REQUIRED)
find_package(restinio CONFIG REQUIRED)

find_package(Catch2 REQUIRED)

set(Server_Libraries  Catch2::Catch2 fmt::fmt restinio::restinio)

find_package(Boost 1.72.0 COMPONENTS system timer REQUIRED)


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

if(UNIX)
    set(PQXX /usr/local/include/pqxx)
    find_library(PQXX_LIB pqxx REQUIRED)
    find_library(PQ_LIB pq REQUIRED)
    set(Server_Libraries ${Server_Libraries} libpqxx libpq)

elseif(WIN32)
    find_path(LIBPQXX_INCLUDE_DIR pqxx)
    find_library(LIBPQXX_LIBRARY liblibpqxx_static.a)
    include_directories(${LIBPQXX_INCLUDE_DIR})
endif()

add_executable(webserver main.cpp backend/databasehandler.cpp backend/databasehandler.h)

target_link_libraries(webserver ${Server_Libraries} ${Boost_LIBRARIES})