#include <iostream>
#include <string>
#include <vector>
#include "LevelTraversal.hpp"
using namespace std;

int main()
{
    Tree<int> numbers{45, 74, 28, 32, 44, 100};
    vector<int> visited;

    cout << "Growing a Tree - Part 4" << endl;
    cout << "Level order: ";

    levelTraversal(numbers, [&](int number)
    {
        cout << number << " ";
        visited.push_back(number);
    });
    cout << endl;

    vector<int> expected{45, 74, 28, 100, 32, 44};
    bool passed = (visited == expected);

    Tree<int> emptyTree;
    int emptyVisits = 0;
    levelTraversal(emptyTree, [&](int)
    {
        emptyVisits++;
    });
    passed = passed && (emptyVisits == 0);

    Tree<int> singleTree{7};
    vector<int> singleVisit;
    levelTraversal(singleTree, [&](int number)
    {
        singleVisit.push_back(number);
    });
    passed = passed && singleVisit == vector<int>{7};

    Tree<string> words{"cat", "dog", "ant"};
    vector<string> wordOrder;
    levelTraversal(words, [&](const string& word)
    {
        wordOrder.push_back(word);
    });
    passed = passed && wordOrder == vector<string>({"cat", "dog", "ant"});

    // The traversal only reads the original Tree.
    passed = passed && numbers.size() == 6;
    passed = passed && numbers.validParentLinks();

    cout << (passed ? "All level traversal tests passed!"
                    : "Level traversal test FAILED") << endl;
    return passed ? 0 : 1;
}
