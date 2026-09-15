#pragma once
#include "list.hpp"

template <typename T>
class Bag
{
private:
    List<T> items;

public:
    Bag()
    {
    }

    void insert(T thing)
    {
        items.push_back(thing);
    }

    T pop()
    {
        if (items.empty())
        {
            return T();
        }

        T thing = items.back();
        items.pop_back();

        return thing;
    }

    bool remove(T thing)
    {
        return items.remove(thing);
    }

    int size()
    {
        return items.size();
    }

    int count(T thing)
    {
        int total = 0;

        items.traverse([&](T& item)
            {
                if (item == thing)
                {
                    total++;
                }
            });

        return total;
    }
};