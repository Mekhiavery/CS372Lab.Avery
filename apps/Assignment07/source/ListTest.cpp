#include <cassert>
#include <iostream>
#include <utility>
#include "List.hpp"

int main()
{
    List<int> a;
    assert(a.empty());
    a.push_back(20);
    a.push_front(10);
    a.push_back(30);
    assert(a.front() == 10);
    assert(a.back() == 30);

    auto it = a.begin();
    ++it;
    a.insert(it, 15);
    int correct[] = {10, 15, 20, 30};
    int count = 0;
    for (int v : a) assert(v == correct[count++]);
    assert(count == 4);

    a.erase(a.begin());
    assert(a.front() == 15);
    a.pop_back();
    assert(a.back() == 20);

    List<int> copy(a);
    copy.push_back(99);
    assert(a.back() == 20);
    assert(copy.back() == 99);

    List<int> assigned;
    assigned = copy;
    assert(assigned.back() == 99);
    assigned = assigned;
    assert(assigned.back() == 99);

    List<int> moved(std::move(assigned));
    assert(moved.back() == 99);
    assert(assigned.empty());
    assigned.push_back(7);
    assert(assigned.front() == 7);

    List<int> moveAssigned;
    moveAssigned = std::move(moved);
    assert(moveAssigned.back() == 99);
    assert(moved.empty());

    int sum = 0;
    moveAssigned.traverse([&](int& v){ sum += v; });
    assert(sum == 15 + 20 + 99);

    List<int> single(42);
    assert(single.front() == 42);
    assert(single.back() == 42);
    single.pop_front();
    assert(single.empty());

    const List<int>& cref = copy;
    auto constIt = cref.begin();
    assert(*constIt == 15);

    bool threw = false;
    try { a.erase(a.end()); }
    catch (const std::out_of_range&) { threw = true; }
    assert(threw);

    std::cout << "List tests passed" << std::endl;
}
