#include "CommitTree.hpp"

#include <fstream>
#include <map>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/utility.hpp>

#include "RepositoryException.hpp"

CommitTree::CommitTree()
{
}

CommitTree::~CommitTree()
{
}

void CommitTree::push_commit(const Commit &commit)
{
    std::shared_ptr<TreeNode> new_node(new TreeNode(commit, m_head));
    m_head = new_node;
}

std::shared_ptr<TreeNode> CommitTree::find_node_by_hash_code(const std::string& hash_code)
{
    for(std::shared_ptr<TreeNode> ptr = m_head; ptr != nullptr; ptr = ptr->m_parent_node)
    {
        if (ptr->m_commit_value.get_hash_code().hash_code().to_string() == hash_code)
        {
            return ptr;
        }
    }
    return nullptr;
}

void CommitTree::pop_commit()
{
    if (m_head == nullptr)
    {
        // TODO: throw exception
        return;
    }
    std::shared_ptr<TreeNode> parent_node = m_head->m_parent_node;
    m_head = parent_node;
}
