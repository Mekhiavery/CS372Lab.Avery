#pragma once
#include "list.hpp"

template <typename T>
class Queue
{
private:
    List<T> queueList;

public:
    Queue()
    {
    }

    bool empty() const
    {
        return queueList.empty();
    }

    int size() const
    {
        return queueList.size();
    }

    void push(T data)
    {
        queueList.push_back(data);
    }

    T front()
    {
        return queueList.front();
    }

    T back()
    {
        return queueList.back();
    }

    void pop()
    {
        queueList.pop_front();
    }
};