#include <iostream>
#include <chrono>
#include "vector.hpp"
#include "array.hpp"
using namespace std;
using namespace std::chrono;

void timeVector(Vector<int>* numbers, string name, int amount)
{
    auto start = steady_clock::now();

    for (int i = 0; i < amount; i++)
    {
        numbers->push_back(i);
    }

    auto end = steady_clock::now();

    auto timeTaken = duration_cast<milliseconds>(end - start).count();

    cout << name << endl;
    cout << "Amount Added: " << amount << endl;
    cout << "Final Size: " << numbers->size() << endl;
    cout << "Final Capacity: " << numbers->capacity() << endl;
    cout << "Time: " << timeTaken << " milliseconds" << endl;
    cout << endl;

    delete numbers;
}

void testArray()
{
    Array<int> numbers(5);

    numbers.put(10, 0);
    numbers.put(20, 1);
    numbers.put(30, 2);
    numbers.put(40, 3);
    numbers.put(50, 4);

    cout << "Array Test" << endl;
    numbers.traverse();
    cout << "Array size: " << numbers.size() << endl;
    cout << "Array capacity: " << numbers.capacity() << endl;
    cout << endl;
}

int main()
{
    int sizes[] = {
        2, 4, 8, 16, 32, 64, 128, 256,
        512, 1024, 2048, 4096, 8192,
        16384, 32768, 65536, 131072,
        262144, 524288, 1048576
    };

    int numberOfSizes = 20;

    cout << "Vector Timing Assignment" << endl;
    cout << "------------------------" << endl;
    cout << endl;

    for (int i = 0; i < numberOfSizes; i++)
    {
        int amount = sizes[i];

        timeVector(new Vector<int>(), "Regular Vector", amount);
        timeVector(new CopyVector<int>(), "Copy Vector", amount);
        timeVector(new BigVector<int>(), "Big Vector", amount);
    }

    testArray();

    return 0;
}