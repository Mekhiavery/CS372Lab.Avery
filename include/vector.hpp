#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class Vector
{
protected:
    T* arr;
    int vCapacity;
    int length;

    virtual int getNewCapacity()
    {
        return vCapacity * 2;
    }

    virtual void expand(int newCapacity)
    {
        if (newCapacity > vCapacity)
        {
            T* temp = new T[newCapacity];

            for (int i = 0; i < length; i++)
            {
                temp[i] = arr[i];
            }

            delete[] arr;

            arr = temp;
            vCapacity = newCapacity;
        }
    }

public:
    Vector()
    {
        arr = new T[1];
        vCapacity = 1;
        length = 0;
    }

    Vector(int startingCapacity)
    {
        if (startingCapacity < 1)
        {
            startingCapacity = 1;
        }

        arr = new T[startingCapacity];
        vCapacity = startingCapacity;
        length = 0;
    }

    virtual ~Vector()
    {
        delete[] arr;
        arr = nullptr;
    }

    void push_back(T data)
    {
        if (length == vCapacity)
        {
            expand(getNewCapacity());
        }

        arr[length] = data;
        length++;
    }

    void put(T data, int index)
    {
        if (index == length)
        {
            push_back(data);
        }
        else if (index >= 0 && index < length)
        {
            arr[index] = data;
        }
        else
        {
            cout << "Index out of range" << endl;
        }
    }

    T& at(int index)
    {
        if (index < 0 || index >= length)
        {
            cout << "Index out of range" << endl;
            return arr[0];
        }

        return arr[index];
    }

    T& operator[](int index)
    {
        return at(index);
    }

    int size()
    {
        return length;
    }

    int capacity()
    {
        return vCapacity;
    }

    void traverse()
    {
        for (int i = 0; i < length; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }
};

template <typename T>
class CopyVector : public Vector<T>
{
protected:
    void expand(int newCapacity) override
    {
        if (newCapacity > this->vCapacity)
        {
            T* temp = new T[newCapacity];

            copy(this->arr, this->arr + this->length, temp);

            delete[] this->arr;

            this->arr = temp;
            this->vCapacity = newCapacity;
        }
    }
};

template <typename T>
class BigVector : public Vector<T>
{
protected:
    int getNewCapacity() override
    {
        return this->vCapacity * 4;
    }

public:
    BigVector() : Vector<T>(128)
    {
    }
};