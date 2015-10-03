cmake_minimum_required (VERSION 2.8)

project (au_git)

set (CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories(src include)

set (SOURCE
    src/main.cpp
)

add_executable(au_git ${SOURCE})

# find_package(OpenSSL REQUIRED)
# find_package(Boost COMPONENTS program_options REQUIRED)

target_link_libraries(au_git ${OPENSSL_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY})
include_directories(${Boost_INCLUDE_DIRS})
