#include <iostream>
#include <initializer_list>

#include "CommitTree.hpp"
#include "RepositoryException.hpp"
#include "Repository.hpp"

int main(int argc, char *argv[])
{
    try
    {
        Repository repo("/home/mikhail/Programming");
//        repo.status();

//        std::vector <std::string> commit_files1{"/home/mikhail/Programming/1",
//                                                "/home/mikhail/Programming/print_tree.cpp",
//                                                "/home/mikhail/Programming/huff.cpp"};

//        std::vector <std::string> commit_files2{"/home/mikhail/Programming/Huffman/src/TreeNode.cpp",
//                                                "/home/mikhail/Programming/Huffman/src/CodeStatistics.cpp",
//                                                "/home/mikhail/Programming/Huffman/src/ValueStatistics.cpp"};

//        std::vector <std::string> commit_files3{"/home/mikhail/Programming/Huffman/src/code2",
//                                                "/home/mikhail/Programming/Huffman/src/out2",
//                                                "/home/mikhail/Programming/Huffman/src/input2"};

//        repo.add_commit(commit_files1);
//        repo.add_commit(commit_files2);
//        repo.create_branch(commit_files3, "6cc886d5a9a9a761ba52ae997804a7bce9f4fc2708acefbeacc746568fd8a4");
    }
    catch (AbstractException &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
