//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_COMMITTREE_HPP
#define AU_GIT_COMMITTREE_HPP

#include "Commit.hpp"
#include "TreeNode.hpp"

class CommitTree
{
public:
    CommitTree();
    ~CommitTree();

    void   push_commit(const Commit &commit);
    void   pop_commit ();
    bool   is_empty   () const;
    size_t tree_size  () const;
    Commit last_commit() const;

private:
    TreeNode* m_root_tree = new TreeNode();
    TreeNode* m_tail_tree = nullptr;
    size_t    m_tree_size = 0;

    void serialize();
    void deserialize();
};


#endif //AU_GIT_COMMITTREE_HPP
