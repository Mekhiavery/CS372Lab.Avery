#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Array
{
private:
    T* arr;
    size_t arrSize;

public:
    Array(size_t size)
    {
        if (size < 1)
        {
            size = 1;
        }

        arrSize = size;
        arr = new T[arrSize];
    }

    ~Array()
    {
        delete[] arr;
        arr = nullptr;
    }

    void put(T data, size_t index)
    {
        if (index < arrSize)
        {
            arr[index] = data;
        }
        else
        {
            cout << "Index out of range" << endl;
        }
    }

    T& at(size_t index)
    {
        if (index >= arrSize)
        {
            cout << "Index out of range" << endl;
            return arr[0];
        }

        return arr[index];
    }

    T& operator[](size_t index)
    {
        return at(index);
    }

    size_t size()
    {
        return arrSize;
    }

    size_t capacity()
    {
        return arrSize;
    }

    void traverse()
    {
        for (size_t i = 0; i < arrSize; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }
};