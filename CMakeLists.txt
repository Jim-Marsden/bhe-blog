#CmakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(webserver LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ./cmake_modules )


set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(unofficial-http-parser REQUIRED)
find_package(fmt REQUIRED)
find_package(restinio CONFIG REQUIRED)


find_package(pqxx REQUIRED)



find_package(Catch2 REQUIRED)

set(Server_Libraries  Catch2::Catch2 fmt::fmt restinio::restinio)

find_package(Boost 1.72.0 COMPONENTS system timer REQUIRED)


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

if(UNIX)


elseif(WIN32)

endif()

add_executable(webserver main.cpp backend/database_handler.cpp backend/database_handler.hpp)

target_link_libraries(webserver ${Server_Libraries} ${Boost_LIBRARIES} ${PQXX_LIBRIARIES})