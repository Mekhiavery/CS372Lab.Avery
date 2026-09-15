#include <iostream>
#include <string>
#include <utility>
#include "list.hpp"
#include "bag.hpp"
#include "circularlist.hpp"
using namespace std;

void printInt(int& number)
{
    cout << number << " ";
}

void printString(string& word)
{
    cout << word << " ";
}

int main()
{
    cout << "List Test" << endl;
    cout << "---------" << endl;

    List<int> numbers;

    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_front(10);

    cout << "List: ";
    numbers.traverse(printInt);
    cout << endl;

    cout << "Front: " << numbers.front() << endl;
    cout << "Back: " << numbers.back() << endl;
    cout << "Size: " << numbers.size() << endl;

    numbers.pop_front();

    cout << "After pop_front: ";
    numbers.traverse(printInt);
    cout << endl;

    numbers.pop_back();

    cout << "After pop_back: ";
    numbers.traverse(printInt);
    cout << endl;

    cout << endl;

    cout << "Copy Constructor Test" << endl;
    List<int> copiedList = numbers;
    copiedList.push_back(99);

    cout << "Copied list: ";
    copiedList.traverse(printInt);
    cout << endl;

    cout << endl;

    cout << "Copy Assignment Test" << endl;
    List<int> assignedList;
    assignedList = copiedList;

    cout << "Assigned list: ";
    assignedList.traverse(printInt);
    cout << endl;

    cout << endl;

    cout << "Move Constructor Test" << endl;
    List<int> movedList = move(assignedList);

    cout << "Moved list: ";
    movedList.traverse(printInt);
    cout << endl;

    cout << endl;

    cout << "Move Assignment Test" << endl;
    List<int> moveAssignedList;
    moveAssignedList = move(movedList);

    cout << "Move assigned list: ";
    moveAssignedList.traverse(printInt);
    cout << endl;

    cout << endl;

    cout << "Bag Test" << endl;
    cout << "--------" << endl;

    Bag<string> myBag;

    myBag.insert("apple");
    myBag.insert("orange");
    myBag.insert("apple");

    cout << "Bag size: " << myBag.size() << endl;
    cout << "Apple count: " << myBag.count("apple") << endl;
    cout << "Orange count: " << myBag.count("orange") << endl;

    cout << "Popped item: " << myBag.pop() << endl;
    cout << "Bag size after pop: " << myBag.size() << endl;

    cout << endl;

    cout << "Circular List Test" << endl;
    cout << "------------------" << endl;

    CircularList<int> circle;

    circle.push_back(1);
    circle.push_back(2);
    circle.push_back(3);
    circle.push_back(4);

    cout << "Circular traverse from 3: ";
    circle.traverse(3, printInt);
    cout << endl;

    return 0;
}