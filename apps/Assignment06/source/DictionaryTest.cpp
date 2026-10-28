#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <vector>
#include "Dictionary.hpp"

int main()
{
    Dictionary<std::string, int> ages;
    assert(ages.isEmpty());

    ages.insert("Chris", 25);
    ages.insert("Alex", 20);
    ages.insert("Beth", 22);
    ages.insert("Alex", 999); // same key should not create a second entry
    assert(ages.size() == 3);
    assert(ages.at("Alex") == 20);

    ages["Beth"] = 23;
    ages["Dana"] = 28;
    assert(ages.size() == 4);
    assert(ages.at("Beth") == 23);

    std::cout << "Keys in order: ";
    std::vector<std::string> names;
    for (const auto& key : ages.keys())
    {
        std::cout << key << " ";
        names.push_back(key);
    }
    std::cout << "\n";
    assert((names == std::vector<std::string>{"Alex", "Beth", "Chris", "Dana"}));

    std::cout << "Values in key order: ";
    std::vector<int> vals;
    for (const auto& value : ages.values())
    {
        std::cout << value << " ";
        vals.push_back(value);
    }
    std::cout << "\n";
    assert((vals == std::vector<int>{20, 23, 25, 28}));

    bool error = false;
    try { ages.at("Missing"); }
    catch (const std::out_of_range&) { error = true; }
    assert(error);

    Dictionary<std::string, int> copied = ages;
    ages.erase("Alex");
    assert(ages.size() == 3);
    assert(copied.size() == 4);
    assert(copied.at("Alex") == 20);
    assert(!ages.erase("Missing"));

    Dictionary<std::string, int> assigned;
    assigned = ages;
    assert(assigned.size() == 3);
    Dictionary<std::string, int> moved = std::move(assigned);
    assert(moved.size() == 3);
    assert(assigned.isEmpty());
    assigned = std::move(moved);
    assert(assigned.size() == 3);

    // Larger test exercises the rotations and deletion logic.
    Dictionary<int, std::string> many;
    for (int i = 0; i < 500; ++i) many[i] = std::to_string(i);
    assert(many.size() == 500);
    for (int i = 0; i < 500; i += 2) assert(many.erase(i));
    assert(many.size() == 250);
    for (int i = 1; i < 500; i += 2) assert(many.at(i) == std::to_string(i));
    const auto& constMany = many;
    assert(constMany.at(3) == "3");
    many.clear();
    assert(many.isEmpty());
    assert(many.size() == 0);

    // Show the C++20 Pair comparison called for in Step 1.
    Pair<int, std::string> a{1, "one"};
    Pair<int, std::string> b{2, "two"};
    assert(a < b);

    std::cout << "All Dictionary tests passed!\n";
}
