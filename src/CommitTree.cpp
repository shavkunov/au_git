//
// Created by mikhail on 10/9/15.
//

#include "../include/CommitTree.hpp"

CommitTree::CommitTree()
{
    deserialize();
}

CommitTree::~CommitTree()
{
    serialize();
}

void CommitTree::push_commit(const Commit &commit)
{
    TreeNode *node = new TreeNode(commit);
    ++m_tree_size;
    if (m_tree_size == 0)
    {
        m_root_tree = node;
        m_tail_tree = node;
        return;
    }

    TreeNode *pointer = m_root_tree;
    while (pointer->m_next_node != nullptr)
    {
        pointer = pointer->m_next_node;
    }

    pointer->m_next_node = node;
    node->m_parent_node = pointer;
    m_tail_tree = node;
}

void CommitTree::pop_commit()
{
    // если в дереве находится единственный элемент...
    if (m_tail_tree->m_parent_node == nullptr)
    {
        delete m_tail_tree;
        m_root_tree = nullptr;
        m_tail_tree = nullptr;
        m_tree_size = 0;
        return;
    }

    TreeNode *temp_pointer = m_tail_tree->m_parent_node;
    delete m_tail_tree;
    temp_pointer->m_next_node = nullptr;
    m_tail_tree = temp_pointer;
    --m_tree_size;
}

bool CommitTree::is_empty() const
{
    return m_tree_size == 0;
}

size_t CommitTree::tree_size() const
{
    return m_tree_size;
}

Commit CommitTree::last_commit() const
{
    return m_tail_tree->m_commit_value;
}

void CommitTree::serialize()
{
    std::cout << "Serialize" << std::endl;
}

void CommitTree::deserialize()
{
    std::cout << "Desirialize" << std::endl;
}