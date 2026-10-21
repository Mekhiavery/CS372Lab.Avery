// Based on the Tree class provided in the CS372 lecture sample.
// Assignment07, Part 2: add parent links to the nodes.
#pragma once

#include <memory>
#include <functional>
#include <cassert>
#include <initializer_list>
#include <cstddef>
#include <ostream>
#include <stdexcept>

template <typename T>
class Tree
{
private:
    struct Node
    {
        Node(std::shared_ptr<const Node> left, T value,
             std::shared_ptr<const Node> right)
            : _lft(left), _val(value), _rgt(right)
        {
        }

        std::shared_ptr<const Node> _lft;
        T _val;
        std::shared_ptr<const Node> _rgt;

        // A weak_ptr lets us point back to the parent without a cycle.
        std::weak_ptr<const Node> _parent;
    };

    std::shared_ptr<const Node> _root;

    explicit Tree(std::shared_ptr<const Node> node) : _root(node)
    {
    }

    // We make new nodes for each attached subtree because the original
    // Tree class can share subtrees between different Tree objects.
    // A node must not have two different parents at the same time.
    static std::shared_ptr<const Node> copyNodes(
        const std::shared_ptr<const Node>& oldNode,
        const std::shared_ptr<const Node>& parent)
    {
        if (oldNode == nullptr)
        {
            return nullptr;
        }

        auto newNode = std::make_shared<Node>(nullptr, oldNode->_val, nullptr);
        newNode->_parent = parent;
        newNode->_lft = copyNodes(oldNode->_lft, newNode);
        newNode->_rgt = copyNodes(oldNode->_rgt, newNode);
        return newNode;
    }

    // Build a new Tree when inserting. The original Tree is unchanged.
    template <typename Compare>
    static std::shared_ptr<const Node> insertNodes(
        const std::shared_ptr<const Node>& oldNode,
        const T& value,
        const std::shared_ptr<const Node>& parent,
        Compare compare)
    {
        if (oldNode == nullptr)
        {
            auto newNode = std::make_shared<Node>(nullptr, value, nullptr);
            newNode->_parent = parent;
            return newNode;
        }

        auto newNode = std::make_shared<Node>(nullptr, oldNode->_val, nullptr);
        newNode->_parent = parent;

        if (compare(value, oldNode->_val))
        {
            newNode->_lft = insertNodes(oldNode->_lft, value, newNode, compare);
            newNode->_rgt = copyNodes(oldNode->_rgt, newNode);
        }
        else if (compare(oldNode->_val, value))
        {
            newNode->_lft = copyNodes(oldNode->_lft, newNode);
            newNode->_rgt = insertNodes(oldNode->_rgt, value, newNode, compare);
        }
        else
        {
            newNode->_lft = copyNodes(oldNode->_lft, newNode);
            newNode->_rgt = copyNodes(oldNode->_rgt, newNode);
        }

        return newNode;
    }

    // Check that every node points to the correct parent.
    // This is useful for testing the new parent links.
    static bool checkParents(const std::shared_ptr<const Node>& node,
                             const std::shared_ptr<const Node>& parent)
    {
        if (node == nullptr) return true;

        if (node->_parent.lock() != parent) return false;

        return checkParents(node->_lft, node) &&
               checkParents(node->_rgt, node);
    }

    static size_t countNodes(const std::shared_ptr<const Node>& node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + countNodes(node->_lft) + countNodes(node->_rgt);
    }

    template <typename Visitor>
    static void preorderNodes(const std::shared_ptr<const Node>& node, Visitor& visit)
    {
        if (node == nullptr) return;
        visit(node->_val);
        preorderNodes(node->_lft, visit);
        preorderNodes(node->_rgt, visit);
    }

    template <typename Visitor>
    static void inorderNodes(const std::shared_ptr<const Node>& node, Visitor& visit)
    {
        if (node == nullptr) return;
        inorderNodes(node->_lft, visit);
        visit(node->_val);
        inorderNodes(node->_rgt, visit);
    }

    template <typename Visitor>
    static void postorderNodes(const std::shared_ptr<const Node>& node, Visitor& visit)
    {
        if (node == nullptr) return;
        postorderNodes(node->_lft, visit);
        postorderNodes(node->_rgt, visit);
        visit(node->_val);
    }

public:
    Tree() : _root(nullptr) {}
    Tree(const Tree& other) = default;
    Tree& operator=(const Tree& other) = default;
    Tree(Tree&& other) = default;
    Tree& operator=(Tree&& other) = default;
    ~Tree() = default;

    // Construct a Tree from a left subtree, root value, and right subtree.
    Tree(Tree leftTree, T value, Tree rightTree)
    {
        auto newRoot = std::make_shared<Node>(nullptr, value, nullptr);
        // Root parent is empty (equivalent to nullptr).
        newRoot->_lft = copyNodes(leftTree._root, newRoot);
        newRoot->_rgt = copyNodes(rightTree._root, newRoot);
        _root = newRoot;
    }

    Tree(std::initializer_list<T> initialValues) : Tree()
    {
        Tree result;
        for (T value : initialValues)
        {
            result = result.insert(value);
        }
        _root = result._root;
    }

    bool isEmpty() const { return _root == nullptr; }
    size_t size() const { return countNodes(_root); }

    const T& root() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("root(): Tree is empty");
        }
        return _root->_val;
    }

    Tree left() const
    {
        assert(!isEmpty());
        // A standalone subtree must have no parent above its root.
        return Tree(copyNodes(_root->_lft, nullptr));
    }

    Tree right() const
    {
        assert(!isEmpty());
        return Tree(copyNodes(_root->_rgt, nullptr));
    }

    template <typename Compare = std::greater<T>>
    Tree insert(const T& value, Compare compare = std::greater<T>()) const
    {
        if (member(value, compare))
        {
            return *this;  // Do not add duplicates.
        }
        return Tree(insertNodes(_root, value, nullptr, compare));
    }

    template <typename Compare = std::greater<T>>
    bool member(const T& value, Compare compare = std::greater<T>()) const
    {
        auto current = _root;
        while (current != nullptr)
        {
            if (compare(value, current->_val)) current = current->_lft;
            else if (compare(current->_val, value)) current = current->_rgt;
            else return true;
        }
        return false;
    }

    template <typename Compare = std::greater<T>>
    bool find(const T& value, Tree& subtreeWhereFound,
              Compare compare = std::greater<T>()) const
    {
        auto current = _root;
        while (current != nullptr)
        {
            if (compare(value, current->_val)) current = current->_lft;
            else if (compare(current->_val, value)) current = current->_rgt;
            else
            {
                subtreeWhereFound = Tree(copyNodes(current, nullptr));
                return true;
            }
        }
        subtreeWhereFound = Tree();
        return false;
    }

    // New for Assignment07: determine the parent of a value in the tree.
    // Returns false if the value is absent or is the root.
    template <typename Compare = std::greater<T>>
    bool findParent(const T& value, T& parentValue,
                    Compare compare = std::greater<T>()) const
    {
        auto current = _root;
        while (current != nullptr)
        {
            if (compare(value, current->_val)) current = current->_lft;
            else if (compare(current->_val, value)) current = current->_rgt;
            else
            {
                auto parent = current->_parent.lock();
                if (parent == nullptr) return false;
                parentValue = parent->_val;
                return true;
            }
        }
        return false;
    }

    // New for Assignment07: check the root's parent link.
    bool rootHasNoParent() const
    {
        return isEmpty() || _root->_parent.expired();
    }

    // Check parent pointers throughout the whole tree, not just the root.
    bool validParentLinks() const
    {
        return checkParents(_root, nullptr);
    }

    template <typename Visitor>
    void preorder(Visitor visit) const { preorderNodes(_root, visit); }

    template <typename Visitor>
    void inorder(Visitor visit) const { inorderNodes(_root, visit); }

    template <typename Visitor>
    void postorder(Visitor visit) const { postorderNodes(_root, visit); }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree)
{
    if (tree.isEmpty())
    {
        os << "[]";
        return os;
    }

    os << "[";
    tree.preorder([&os](T value) { os << value << " "; });
    os << "]";
    return os;
}
