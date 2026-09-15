#pragma once
#include <iostream>
#include <functional>
#include <utility>
using namespace std;

template <typename T>
class List
{
protected:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node(T value)
        {
            data = value;
            next = nullptr;
            prev = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int listSize;

    void copyFrom(const List<T>& other)
    {
        Node* current = other.head;

        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }
    }

    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    Node* findNode(T value)
    {
        Node* current = head;

        while (current != nullptr)
        {
            if (current->data == value)
            {
                return current;
            }

            current = current->next;
        }

        return nullptr;
    }

    bool removeNode(Node* node)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node == head && node == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else if (node == head)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else if (node == tail)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        delete node;
        listSize--;

        return true;
    }

public:
    List()
    {
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }

    List(T newData)
    {
        head = nullptr;
        tail = nullptr;
        listSize = 0;
        push_back(newData);
    }

    List(const List<T>& other)
    {
        head = nullptr;
        tail = nullptr;
        listSize = 0;
        copyFrom(other);
    }

    List(List<T>&& other) noexcept
    {
        head = other.head;
        tail = other.tail;
        listSize = other.listSize;

        other.head = nullptr;
        other.tail = nullptr;
        other.listSize = 0;
    }

    virtual ~List()
    {
        clear();
    }

    List<T>& operator=(const List<T>& other)
    {
        if (this != &other)
        {
            clear();
            copyFrom(other);
        }

        return *this;
    }

    List<T>& operator=(List<T>&& other) noexcept
    {
        if (this != &other)
        {
            clear();

            head = other.head;
            tail = other.tail;
            listSize = other.listSize;

            other.head = nullptr;
            other.tail = nullptr;
            other.listSize = 0;
        }

        return *this;
    }

    bool empty() const
    {
        return listSize == 0;
    }

    int size() const
    {
        return listSize;
    }

    void push_front(T data)
    {
        Node* newNode = new Node(data);

        if (empty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        listSize++;
    }

    void push_back(T data)
    {
        Node* newNode = new Node(data);

        if (empty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        listSize++;
    }

    T front() const
    {
        if (empty())
        {
            cout << "List is empty" << endl;
            return T();
        }

        return head->data;
    }

    T back() const
    {
        if (empty())
        {
            cout << "List is empty" << endl;
            return T();
        }

        return tail->data;
    }

    void pop_front()
    {
        if (empty())
        {
            cout << "List is empty" << endl;
            return;
        }

        Node* oldNode = head;

        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }

        delete oldNode;
        listSize--;
    }

    void pop_back()
    {
        if (empty())
        {
            cout << "List is empty" << endl;
            return;
        }

        Node* oldNode = tail;

        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete oldNode;
        listSize--;
    }

    bool remove(T value)
    {
        Node* node = findNode(value);
        return removeNode(node);
    }

    virtual void traverse(function<void(T&)> doIt)
    {
        Node* current = head;

        while (current != nullptr)
        {
            doIt(current->data);
            current = current->next;
        }
    }
};