cmake_minimum_required(VERSION 2.8)

project(au_git)

set(SOURCE_EXE ./src/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)
set(CMAKE_BINARY_DIR ./bin/)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./build/)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./build/)

#set(CMAKE_BUILD_FILES_DIRECTORY ./bin/)
#set(CMAKE_BUILD_DIRECTORY ./bin/)

include_directories(include)

add_executable(main ${SOURCE_EXE})

target_link_libraries(main)
