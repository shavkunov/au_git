//
// Created by mikhail on 10/9/15.
//

#ifndef AU_GIT_COMMITTREE_HPP
#define AU_GIT_COMMITTREE_HPP

#include "Commit.hpp"
#include "TreeNode.hpp"

class TreeNode;

class CommitTree
{
public:
    CommitTree();
    ~CommitTree();

    void push_commit(const Commit &commit);
    void pop_commit();
    void create_branch(const Commit &commit, size_t position);
    void print_current_node() const;

private:
    void serialize();
    void deserialize();

    TreeNode* find_node_by_node_index(size_t index);

private:
    std::vector <TreeNode*> m_branches;
    TreeNode*               m_current_node = nullptr;
    size_t                  m_last_index   = 0;
    size_t                  m_current_index_branch;
};


#endif //AU_GIT_COMMITTREE_HPP
