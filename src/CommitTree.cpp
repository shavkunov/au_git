#include "CommitTree.hpp"

#include <fstream>
#include <map>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/utility.hpp>

#include "RepositoryException.hpp"
#include "Log.hpp"

CommitTree::CommitTree() : _head(nullptr)
{
}

CommitTree::~CommitTree()
{
}

void CommitTree::push_commit(Commit &commit)
{
    //LOG << "start of creating shared ptr" << std::endl;
    std::shared_ptr<TreeNode> new_node(new TreeNode(commit, _head));
    //LOG << "made shared ptr" << std::endl;
    _head = new_node;

    //LOG << "push done" << std::endl;
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
