#include <iostream>
#include <initializer_list>

#include "CommitTree.hpp"
#include "CommitException.hpp"

#include <boost/filesystem.hpp>

int main()
{

    try
    {
        CommitTree tree;

        std::vector <CommitFile> commits{ CommitFile("1"), CommitFile("2"), CommitFile("3") };
        Commit simple_commit;
        simple_commit.add_files(commits);
        tree.push_commit(simple_commit);

        std::vector <CommitFile> commits3{ CommitFile("11"), CommitFile("211"), CommitFile("311") };
        Commit simple_commit3;
        simple_commit3.add_files(commits3);
        tree.push_commit(simple_commit3);

        std::vector <CommitFile> commits2{ CommitFile("4"), CommitFile("5"), CommitFile("6") };
        Commit simple_commit2;
        simple_commit2.add_files(commits2);
        //tree.push_commit(simple_commit2);

        tree.create_branch(simple_commit2, 0);

        //tree.print_current_node();
    }
    catch (CommitException &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}