#pragma once
#include "list.hpp"

template <typename T>
class Stack
{
private:
    List<T> stackList;

public:
    Stack()
    {
    }

    bool empty() const
    {
        return stackList.empty();
    }

    int size() const
    {
        return stackList.size();
    }

    void push(T data)
    {
        stackList.push_front(data);
    }

    T top()
    {
        return stackList.front();
    }

    void pop()
    {
        stackList.pop_front();
    }
};