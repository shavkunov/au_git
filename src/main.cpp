#include <iostream>
#include <initializer_list>

#include "CommitTree.hpp"
#include "RepositoryException.hpp"

int main()
{
    try
    {
        CommitTree tree;
        std::vector <CommitFile> commits{ CommitFile("/home/mikhail/Programming/1"),
                                          CommitFile("/home/mikhail/Programming/print_tree.cpp"),
                                          CommitFile("/home/mikhail/Programming/huff.cpp") };

        Commit simple_commit;
        simple_commit.add_files(commits);

        tree.push_commit(simple_commit);

        std::vector <CommitFile> commits3{ CommitFile("/home/mikhail/Programming/Huffman/src/TreeNode.cpp"),
                                           CommitFile("/home/mikhail/Programming/Huffman/src/CodeStatistics.cpp"),
                                           CommitFile("/home/mikhail/Programming/Huffman/src/ValueStatistics.cpp") };
        Commit simple_commit3;
        simple_commit3.add_files(commits3);
        tree.push_commit(simple_commit3);

        std::vector <CommitFile> commits2{ CommitFile("/home/mikhail/Programming/Huffman/src/code2"),
                                           CommitFile("/home/mikhail/Programming/Huffman/src/out2"),
                                           CommitFile("/home/mikhail/Programming/Huffman/src/input2") };
        Commit simple_commit2;
        simple_commit2.add_files(commits2);
        //tree.push_commit(simple_commit2);

        tree.create_branch(simple_commit2, "baeff715efadd6bd6f6c372c70b5c41e533fc0992dedda359c8ed5d2bdf7560");
        //tree.print_current_node();
    }
    catch (AbstractException &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}