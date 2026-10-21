#pragma once
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

// Doubly linked List based on the professor's version.
// next owns the next node; prev is weak so the nodes do not form a cycle.
template <typename T>
class List
{
private:
    struct Node
    {
        T data{};
        std::weak_ptr<Node> prev;
        std::shared_ptr<Node> next;
        bool isHiddenNode = false;

        Node() = default;
        Node(const T& value) : data(value) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

public:
    class const_iterator
    {
    protected:
        std::shared_ptr<Node> current;
        const T& retrieve() const { return current->data; }
        explicit const_iterator(std::shared_ptr<Node> p) : current(p) {}
        friend class List<T>;

    public:
        const_iterator() : current(nullptr) {}

        const T& operator*() const { return retrieve(); }

        const_iterator& operator++()
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator& rhs) const
        {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator& rhs) const
        {
            return !(*this == rhs);
        }
    };

    class iterator : public const_iterator
    {
    protected:
        explicit iterator(std::shared_ptr<Node> p) : const_iterator(p) {}
        friend class List<T>;

    public:
        iterator() = default;

        T& operator*() { return this->current->data; }
        const T& operator*() const { return this->current->data; }

        iterator& operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }
    };

private:
    void setupList()
    {
        head = std::make_shared<Node>();
        tail = std::make_shared<Node>();
        head->isHiddenNode = true;
        tail->isHiddenNode = true;
        head->next = tail;
        tail->prev = head;
    }

    void swapWith(List& other) noexcept
    {
        head.swap(other.head);
        tail.swap(other.tail);
    }

public:
    List() { setupList(); }

    explicit List(T newData) : List()
    {
        push_back(newData);
    }

    List(const List& rhs) : List()
    {
        for (auto it = rhs.cbegin(); it != rhs.cend(); ++it)
        {
            push_back(*it);
        }
    }

    List& operator=(const List& rhs)
    {
        if (this != &rhs)
        {
            List copy(rhs);
            swapWith(copy);
        }
        return *this;
    }

    List(List&& rhs) : List()
    {
        swapWith(rhs);
    }

    List& operator=(List&& rhs)
    {
        if (this != &rhs)
        {
            List moved(std::move(rhs));
            swapWith(moved);
        }
        return *this;
    }

    virtual ~List()
    {
        clear();
        // shared_ptr deletes the hidden nodes automatically.
    }

    bool empty() const { return head->next == tail; }

    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(tail); }
    const_iterator begin() const { return cbegin(); }
    const_iterator end() const { return cend(); }
    const_iterator cbegin() const { return const_iterator(head->next); }
    const_iterator cend() const { return const_iterator(tail); }

    iterator insert(iterator itr, const T& value)
    {
        auto p = itr.current;
        if (!p || p == head)
        {
            throw std::out_of_range("Invalid list insertion position");
        }

        auto previous = p->prev.lock();
        if (!previous)
        {
            throw std::out_of_range("Invalid list insertion position");
        }

        auto newNode = std::make_shared<Node>(value);
        newNode->prev = previous;
        newNode->next = p;
        previous->next = newNode;
        p->prev = newNode;
        return iterator(newNode);
    }

    iterator erase(iterator itr)
    {
        auto p = itr.current;
        if (!p || p == head || p == tail)
        {
            throw std::out_of_range("Invalid list erase position");
        }

        auto previous = p->prev.lock();
        auto following = p->next;
        previous->next = following;
        following->prev = previous;
        p->prev.reset();
        p->next.reset();
        return iterator(following);
    }

    iterator erase(iterator first, iterator last)
    {
        while (first != last)
        {
            first = erase(first);
        }
        return last;
    }

    void push_front(T data) { insert(begin(), data); }
    void push_back(T data) { insert(end(), data); }

    T front() const
    {
        if (empty()) throw std::out_of_range("front(): List is empty");
        return head->next->data;
    }

    T back() const
    {
        if (empty()) throw std::out_of_range("back(): List is empty");
        return tail->prev.lock()->data;
    }

    void pop_front()
    {
        if (!empty()) erase(begin());
        else std::cerr << "pop_front(): List is empty" << std::endl;
    }

    void pop_back()
    {
        if (!empty()) erase(iterator(tail->prev.lock()));
        else std::cerr << "pop_back(): List is empty" << std::endl;
    }

    void clear()
    {
        while (!empty()) erase(begin());
    }

    void traverse(std::function<void(T&)> doIt)
    {
        for (auto it = begin(); it != end(); ++it)
        {
            doIt(*it);
        }
    }
};
