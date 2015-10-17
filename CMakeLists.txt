cmake_minimum_required(VERSION 2.8)
project(au_git)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

include_directories(src include)

set(SOURCE_FILES
        src/main.cpp
        src/CommitTree.cpp
        src/CommitFile.cpp
        src/Commit.cpp
        src/HashCodeType.cpp
        src/TreeNode.cpp
        src/StageRepository.cpp
)

add_executable(au_git ${SOURCE_FILES})

find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(Boost COMPONENTS serialization REQUIRED)

target_link_libraries(au_git
        ${OPENSSL_LIBRARIES}
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARIES}
        ${Boost_SERIALIZATION_LIBRARY}
)

include_directories(${Boost_INCLUDE_DIRS})