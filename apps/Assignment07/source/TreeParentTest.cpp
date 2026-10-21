#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "Tree.hpp"
using namespace std;

int main()
{
    Tree<int> numbers{45, 74, 28, 32, 44, 100};
    int parent = -1;
    bool good = true;

    cout << "Growing a Tree - Part 2" << endl;
    cout << "Tree: " << numbers << endl;
    cout << "Size: " << numbers.size() << endl;

    good = good && numbers.rootHasNoParent();
    good = good && numbers.findParent(74, parent) && parent == 45;
    good = good && numbers.findParent(100, parent) && parent == 74;
    good = good && numbers.findParent(32, parent) && parent == 28;
    good = good && numbers.findParent(44, parent) && parent == 32;
    good = good && !numbers.findParent(45, parent);

    Tree<int> larger = numbers.insert(40);
    good = good && !numbers.member(40);  // Original Tree stays unchanged.
    good = good && larger.member(40);
    good = good && larger.findParent(40, parent) && parent == 44;
    good = good && larger.rootHasNoParent();

    Tree<int> childTree = numbers.left();
    good = good && childTree.root() == 74;
    good = good && childTree.rootHasNoParent();
    good = good && childTree.findParent(100, parent) && parent == 74;

    Tree<int> combined(numbers.left(), 50, numbers.right());
    good = good && combined.rootHasNoParent();
    good = good && combined.findParent(74, parent) && parent == 50;
    good = good && combined.findParent(28, parent) && parent == 50;
    good = good && numbers.findParent(74, parent) && parent == 45;

    Tree<int> copied = numbers;
    good = good && copied.findParent(44, parent) && parent == 32;
    Tree<int> moved = std::move(copied);
    good = good && moved.findParent(44, parent) && parent == 32;

    Tree<int> subtree;
    good = good && numbers.find(28, subtree);
    good = good && subtree.rootHasNoParent();
    good = good && subtree.findParent(44, parent) && parent == 32;

    vector<int> order;
    numbers.inorder([&](int value) { order.push_back(value); });
    good = good && order == vector<int>({100, 74, 45, 44, 32, 28});

    Tree<string> words{"apple", "banana", "cherry"};
    good = good && words.member("banana");

    // Extra checks added after the AI code review.
    good = good && numbers.validParentLinks();
    good = good && larger.validParentLinks();
    good = good && combined.validParentLinks();
    good = good && moved.validParentLinks();
    good = good && subtree.validParentLinks();
    good = good && childTree.validParentLinks();

    Tree<int> emptyTree;
    good = good && emptyTree.validParentLinks();
    bool emptyRootThrows = false;
    try
    {
        emptyTree.root();
    }
    catch (const std::out_of_range&)
    {
        emptyRootThrows = true;
    }
    good = good && emptyRootThrows;

    Tree<int> duplicate = numbers.insert(45);
    good = good && duplicate.size() == numbers.size();
    good = good && duplicate.validParentLinks();

    cout << (good ? "All Tree parent tests passed!" : "Tree parent test FAILED") << endl;
    return good ? 0 : 1;
}
