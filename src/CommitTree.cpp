#include "CommitTree.hpp"
#include "RepositoryException.hpp"

#include <fstream>
#include <map>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/utility.hpp>

CommitTree::CommitTree()
{
    std::cout << "Constructor" << std::endl;
    deserialize();
}

CommitTree::~CommitTree()
{
    std::cout << "Destructor" << std::endl;
    serialize();
}

void CommitTree::push_commit(const Commit &commit)
{
    // insert to commit tree
    std::shared_ptr<TreeNode> add_node(new TreeNode(commit, m_current_node));
    m_current_node = add_node;

    if (m_branches.size() == 0)
    {
        m_branches.push_back(m_current_node);
        m_current_index_branch = 0;
        return;
    }

    // copy all files to local repository
    commit.add_to_storage();

    m_branches[m_current_index_branch] = m_current_node;
}

void CommitTree::create_branch(const Commit &commit, const std::string parent_hash_code)
{
    std::shared_ptr <TreeNode> branch_node = find_node_by_hash_code(parent_hash_code);
    if (branch_node == nullptr)
    {
        throw BranchNotCreatedException("Branch could not be created!");
    }

    commit.add_to_storage();

    std::shared_ptr <TreeNode> add_node(new TreeNode(commit, branch_node));
    m_branches.push_back(add_node);
    m_current_index_branch = m_branches.size() - 1;
    m_current_node = add_node;
    // std::cout << "Branch created!" << std::endl;
}

std::shared_ptr <TreeNode> CommitTree::find_node_by_hash_code(const std::string& parent_hash_code)
{
    for(std::shared_ptr <TreeNode> node : m_branches)
    {
        for(std::shared_ptr <TreeNode> ptr = node; ptr != nullptr; ptr = ptr->m_parent_node)
        {
            if (ptr->m_commit_value.get_hash_code().hash_code().to_string() == parent_hash_code)
            {
                return ptr;
            }
        }
    }
    return nullptr;
}

void CommitTree::print_current_node() const
{
    //for(std::shared_ptr <TreeNode> ptr = m_current_node; ptr != nullptr; ptr = ptr->m_parent_node)
    //    ptr->m_commit_value.print();
}

void CommitTree::pop_commit()
{
    if (m_current_node == nullptr)
    {
        // throw exception
        return;
    }
    std::shared_ptr <TreeNode> parent_node = m_current_node->m_parent_node;
    //delete m_current_node;
    m_current_node = parent_node;
    m_branches[m_current_index_branch] = m_current_node;
}

void CommitTree::serialize()
{
    return;
//    std::ofstream out_file("./serialization.bin");
//    boost::archive::text_oarchive archive(out_file);
//
//    // <node index, <Commit, parent node index>>
//    std::map <size_t, std::pair<Commit, size_t>> table_tree;
//    for(std::shared_ptr <TreeNode> node : m_branches)
//    {
//        for(std::shared_ptr <TreeNode> ptr = node; ptr != nullptr; ptr = ptr->m_parent_node)
//        {
//            // if current node was not added to the table
//            if (table_tree.find(node->m_index_position) == table_tree.end())
//            {
//                table_tree[node->m_index_position]
//                        = std::make_pair(node->m_commit_value,
//                        // if parent of the current node then return nullptr current position
//                                         (node->m_parent_node) ? node->m_parent_node->m_index_position
//                                                               : node->m_index_position);
//            }
//            else
//                break;
//        }
//    }
//
//    std::vector <size_t> last_commits_indexes(m_branches.size());
//    for(size_t i = 0; i < m_branches.size(); ++i)
//        last_commits_indexes[i] = m_branches[i]->m_index_position;
//
//    archive << m_last_index << m_current_index_branch << table_tree << last_commits_indexes;
}

void CommitTree::deserialize()
{
    return;
//    std::ifstream in_file("./serialization.bin");
//    if (!in_file.is_open())
//    {
//        std::cout << "File is not found!" << std::endl;
//        return;
//    }
//    try
//    {
//        boost::archive::text_iarchive archive(in_file);
//        std::map <size_t, std::pair<Commit, size_t>> table_tree;
//        std::vector <size_t> last_commits_indexes;
//        archive >> m_last_index >> m_current_index_branch >> table_tree >> last_commits_indexes;
//
//        std::cout << m_last_index << " " << m_current_index_branch << std::endl;
//
//        std::vector <std::shared_ptr <TreeNode>> pointers(table_tree.size(), nullptr);
//        for(std::pair <size_t, std::pair<Commit, size_t>> p : table_tree)
//        {
//            std::cout << p.first << " - " << p.second.second << std::endl;
//            pointers[p.first] = std::make_shared <TreeNode>(p.second.first, p.first, pointers[p.second.second - 1]);
//        }
//
//        for(size_t index : last_commits_indexes)
//        {
//            index = index;
//            //m_branches.push_back(pointers[index]);
//        }
//    }
//    catch (boost::archive::archive_exception &e)
//    {
//        std::cout << e.what() << std::endl;
//    }
}