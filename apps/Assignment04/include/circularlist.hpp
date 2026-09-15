#pragma once
#include "list.hpp"

template <typename T>
class CircularList : public List<T>
{
public:
    void traverse(T startValue, function<void(T&)> doIt)
    {
        typename List<T>::Node* start = this->findNode(startValue);

        if (start == nullptr)
        {
            cout << "Starting value not found" << endl;
            return;
        }

        typename List<T>::Node* current = start;

        do
        {
            doIt(current->data);

            current = current->next;

            if (current == nullptr)
            {
                current = this->head;
            }

        } while (current != start);
    }

    void traverse(function<void(T&)> doIt) override
    {
        if (this->empty())
        {
            return;
        }

        traverse(this->front(), doIt);
    }
};