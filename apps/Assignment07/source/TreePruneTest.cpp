#include <iostream>
#include <vector>
#include <string>
#include "Prune.hpp"
using namespace std;

int main()
{
    bool passed = true;

    Tree<int> original{45, 74, 28, 32, 44, 100};
    Tree<int>& smaller = prune(original);
    vector<int> before;
    vector<int> after;
    original.preorder([&](int value) { before.push_back(value); });
    smaller.preorder([&](int value) { after.push_back(value); });

    cout << "Growing a Tree - Part 5" << endl;
    cout << "Original: ";
    for (int value : before) cout << value << " ";
    cout << endl;
    cout << "Pruned:   ";
    for (int value : after) cout << value << " ";
    cout << endl;

    passed = passed && (before == vector<int>{45, 74, 100, 28, 32, 44});
    passed = passed && (after == vector<int>{45, 74, 28, 32});
    passed = passed && (original.size() == 6);
    passed = passed && (smaller.size() == 4);
    passed = passed && original.validParentLinks();
    passed = passed && smaller.validParentLinks();

    // Empty tree stays empty.
    Tree<int> empty;
    Tree<int>& emptyResult = prune(empty);
    passed = passed && emptyResult.isEmpty();

    // A single root is also a leaf, so it is removed.
    Tree<int> one{7};
    Tree<int>& oneResult = prune(one);
    passed = passed && oneResult.isEmpty();
    passed = passed && (one.size() == 1);

    // Remove just the original leaves, not parents that become new leaves.
    Tree<int> full{10, 15, 5, 20, 12, 7, 2};
    Tree<int>& fullResult = prune(full);
    vector<int> fullValues;
    fullResult.preorder([&](int value) { fullValues.push_back(value); });
    passed = passed && (fullValues == vector<int>{10, 15, 5});
    passed = passed && (full.size() == 7);
    passed = passed && fullResult.validParentLinks();

    // Tree with one child and a string tree also work.
    Tree<int> chain{10, 5, 2};
    Tree<int>& chainResult = prune(chain);
    vector<int> chainValues;
    chainResult.preorder([&](int value) { chainValues.push_back(value); });
    passed = passed && (chainValues == vector<int>{10, 5});

    Tree<string> words{"mango", "zebra", "apple", "banana"};
    Tree<string>& wordResult = prune(words);
    vector<string> wordValues;
    wordResult.preorder([&](const string& value) { wordValues.push_back(value); });
    passed = passed && (wordValues == vector<string>{"mango", "apple"});
    passed = passed && wordResult.validParentLinks();

    // These results were created with new, so delete them when finished.
    delete &smaller;
    delete &emptyResult;
    delete &oneResult;
    delete &fullResult;
    delete &chainResult;
    delete &wordResult;

    cout << (passed ? "All prune tests passed!" : "Prune test FAILED") << endl;
    return passed ? 0 : 1;
}
