#pragma once
#include <algorithm>
#include <functional>
#include <memory>
#include <utility>

// Based on the AVLTree example in Module 06 Part B.
// The findKey helper is added for looking up Dictionary entries by key.
template <typename T, typename Compare = std::less<T>>
class AVLTree
{
private:
    struct Node
    {
        T key;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int height = 1;
        explicit Node(const T& k) : key(k) {}
    };

    std::unique_ptr<Node> root_;
    Compare comp_{};
    std::size_t count_ = 0;

    static int heightOf(const Node* node)
    {
        return node ? node->height : 0;
    }

    static int balanceOf(const Node* node)
    {
        return node ? heightOf(node->left.get()) - heightOf(node->right.get()) : 0;
    }

    static void updateHeight(Node* node)
    {
        node->height = 1 + std::max(heightOf(node->left.get()), heightOf(node->right.get()));
    }

    static std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> node)
    {
        auto newRoot = std::move(node->left);
        node->left = std::move(newRoot->right);
        updateHeight(node.get());
        newRoot->right = std::move(node);
        updateHeight(newRoot.get());
        return newRoot;
    }

    static std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> node)
    {
        auto newRoot = std::move(node->right);
        node->right = std::move(newRoot->left);
        updateHeight(node.get());
        newRoot->left = std::move(node);
        updateHeight(newRoot.get());
        return newRoot;
    }

    static std::unique_ptr<Node> rebalance(std::unique_ptr<Node> node)
    {
        if (!node) return node;
        updateHeight(node.get());
        int balance = balanceOf(node.get());
        if (balance > 1)
        {
            if (balanceOf(node->left.get()) < 0)
                node->left = rotateLeft(std::move(node->left));
            return rotateRight(std::move(node));
        }
        if (balance < -1)
        {
            if (balanceOf(node->right.get()) > 0)
                node->right = rotateRight(std::move(node->right));
            return rotateLeft(std::move(node));
        }
        return node;
    }

    std::unique_ptr<Node> insertNode(std::unique_ptr<Node> node, const T& value)
    {
        if (!node)
        {
            ++count_;
            return std::make_unique<Node>(value);
        }
        if (comp_(value, node->key))
            node->left = insertNode(std::move(node->left), value);
        else if (comp_(node->key, value))
            node->right = insertNode(std::move(node->right), value);
        else
            return node;
        return rebalance(std::move(node));
    }

    static Node* minNode(Node* node)
    {
        while (node && node->left) node = node->left.get();
        return node;
    }

    std::unique_ptr<Node> deleteNode(std::unique_ptr<Node> node, const T& value)
    {
        if (!node) return node;
        if (comp_(value, node->key))
            node->left = deleteNode(std::move(node->left), value);
        else if (comp_(node->key, value))
            node->right = deleteNode(std::move(node->right), value);
        else
        {
            if (!node->left) return std::move(node->right);
            if (!node->right) return std::move(node->left);
            Node* next = minNode(node->right.get());
            node->key = next->key;
            node->right = deleteNode(std::move(node->right), next->key);
        }
        return rebalance(std::move(node));
    }

    static std::unique_ptr<Node> clone(const std::unique_ptr<Node>& node)
    {
        if (!node) return nullptr;
        auto newNode = std::make_unique<Node>(node->key);
        newNode->height = node->height;
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);
        return newNode;
    }

    template <typename Function>
    static void inorder(const Node* node, Function& visit)
    {
        if (!node) return;
        inorder(node->left.get(), visit);
        visit(node->key);
        inorder(node->right.get(), visit);
    }

public:
    AVLTree() = default;
    AVLTree(const AVLTree& rhs)
        : root_(clone(rhs.root_)), comp_(rhs.comp_), count_(rhs.count_) {}
    AVLTree& operator=(const AVLTree& rhs)
    {
        if (this != &rhs)
        {
            root_ = clone(rhs.root_);
            comp_ = rhs.comp_;
            count_ = rhs.count_;
        }
        return *this;
    }
    AVLTree(AVLTree&& rhs) noexcept
        : root_(std::move(rhs.root_)), comp_(std::move(rhs.comp_)), count_(rhs.count_)
    {
        rhs.count_ = 0;
    }
    AVLTree& operator=(AVLTree&& rhs) noexcept
    {
        if (this != &rhs)
        {
            root_ = std::move(rhs.root_);
            comp_ = std::move(rhs.comp_);
            count_ = rhs.count_;
            rhs.count_ = 0;
        }
        return *this;
    }
    ~AVLTree() = default;

    void insert(const T& value) { root_ = insertNode(std::move(root_), value); }

    bool remove(const T& value)
    {
        if (!find(value)) return false;
        root_ = deleteNode(std::move(root_), value);
        --count_;
        return true;
    }

    T* find(const T& value)
    {
        Node* current = root_.get();
        while (current)
        {
            if (comp_(value, current->key)) current = current->left.get();
            else if (comp_(current->key, value)) current = current->right.get();
            else return &current->key;
        }
        return nullptr;
    }

    const T* find(const T& value) const
    {
        const Node* current = root_.get();
        while (current)
        {
            if (comp_(value, current->key)) current = current->left.get();
            else if (comp_(current->key, value)) current = current->right.get();
            else return &current->key;
        }
        return nullptr;
    }

    // Supports a key whose type differs from the stored Pair type.
    template <typename Search>
    T* findKey(const Search& value)
    {
        Node* current = root_.get();
        while (current)
        {
            if (comp_(value, current->key)) current = current->left.get();
            else if (comp_(current->key, value)) current = current->right.get();
            else return &current->key;
        }
        return nullptr;
    }

    template <typename Search>
    const T* findKey(const Search& value) const
    {
        const Node* current = root_.get();
        while (current)
        {
            if (comp_(value, current->key)) current = current->left.get();
            else if (comp_(current->key, value)) current = current->right.get();
            else return &current->key;
        }
        return nullptr;
    }

    template <typename Function>
    void inorder_traverse(Function visit) const { inorder(root_.get(), visit); }

    void clear() { root_.reset(); count_ = 0; }
    bool empty() const { return count_ == 0; }
    std::size_t size() const { return count_; }
};
