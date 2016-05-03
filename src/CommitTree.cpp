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
    std::shared_ptr<TreeNode> new_node(new TreeNode(commit, _head));
    _head = new_node;
}

Commit& CommitTree::get_current_commit()
{
    return _head->commit_value;
}

std::shared_ptr<TreeNode> CommitTree::find_node_by_hash_code(const std::string& hash_code)
{
    for(std::shared_ptr<TreeNode> ptr = _head; ptr != nullptr; ptr = ptr->parent_node)
    {
        if (ptr->commit_value.get_hash_code().hash_code().to_string() == hash_code)
        {
            return ptr;
        }
    }
    return nullptr;
}

void CommitTree::pop_commit()
{
    if (_head == nullptr)
    {
        // TODO: throw exception
        return;
    }
    std::shared_ptr<TreeNode> parent_node = _head->parent_node;
    _head = parent_node;
}
