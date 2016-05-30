cmake_minimum_required(VERSION 2.8)
project(au_git)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11 -g -DLOG_ALL=1")

include_directories(src include)

set(SOURCE_FILES
        src/Command.cpp
        src/Commit.cpp
        src/CommitTree.cpp
        src/DataStore.cpp
        src/FileManager.cpp
        src/HashCodeType.cpp
        src/Repository.cpp
        src/Sha256Converter.cpp
        src/StateRepository.cpp
        src/TreeNode.cpp
        src/main.cpp
)

set(INCLUDE_FILES
        include/Command.hpp
        include/Commit.hpp
        include/CommitFile.hpp
        include/CommitTree.hpp
        include/DataStore.hpp
        include/FileManager.hpp
        include/HashCodeType.hpp
        include/Log.hpp
        include/Repository.hpp
        include/RepositoryException.hpp
        include/Sha256Converter.hpp
        include/StateRepository.hpp
        include/TreeNode.hpp
)

add_executable(au_git ${SOURCE_FILES} ${INCLUDE_FILES})

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
