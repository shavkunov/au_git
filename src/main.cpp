#include <iostream>

#include "../include/CommitTree.hpp"
#include "../include/CommitException.hpp"

#include <boost/filesystem.hpp>

int main()
{

    try
    {

        CommitTree tree;
        //    for(int i = 0; i < 10; ++i)
        //        tree.push_commit(Commit(i));
        //
        //    std::cout << "Tree size: " << tree.tree_size() << std::endl;
        //
        //    while (!tree.is_empty())
        //    {
        //        tree.last_commit().print();
        //        tree.pop_commit();
        //    }
        // test

        Commit test_commit;
        std::list<CommitFile> files;

        files.push_back(CommitFile("./Commit.cpp"));
        files.push_back(CommitFile("3"));
        files.push_back(CommitFile("2"));
        test_commit.add_files(files);

        Commit s;
        std::list<CommitFile> files2;

        files2.push_back(CommitFile("1"));
        files2.push_back(CommitFile("13"));
        files2.push_back(CommitFile("2"));
        files2.push_back(CommitFile("21"));
        files2.push_back(CommitFile("27"));
        s.add_files(files2);


        tree.push_commit(test_commit);
        tree.push_commit(s);

        while (!tree.is_empty())
        {
            tree.last_commit().print();
            tree.pop_commit();
        }
    }
    catch (CommitException &e)
    {
        std::cout << e.what() << std::endl;
    }


    return 0;
}