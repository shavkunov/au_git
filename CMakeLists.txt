cmake_minimum_required(VERSION 2.8)
project(au_git)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11 -g")

include_directories(src include)

set(SOURCE_FILES
        src/main.cpp
        src/CommitTree.cpp
        src/Commit.cpp
        src/HashCodeType.cpp
        src/TreeNode.cpp
        src/StateRepository.cpp
        src/Sha256Converter.cpp
        src/DataStore.cpp
        src/Repository.cpp
        src/Command.cpp
)

set(INCLUDE_FILES
        include/CommitFile.hpp
        include/Commit.hpp
        include/CommitTree.hpp
        include/DataStore.hpp
        include/HashCodeType.hpp
        include/RepositoryException.hpp
        include/Repository.hpp
        include/Sha256Converter.hpp
        include/StateRepository.hpp
        include/TreeNode.hpp
        include/Command.hpp
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
