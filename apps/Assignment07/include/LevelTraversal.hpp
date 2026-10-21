#pragma once
#include <queue>
#include "Tree.hpp"

// This helper visits one node, then recursively visits the next in the queue.
// The queue keeps nodes in level order (root, then the next level, and so on).
template <typename T, typename Visitor>
void visitNextLevelNode(std::queue<Tree<T>>& waiting, Visitor& doIt)
{
    if (waiting.empty())
    {
        return;
    }

    Tree<T> current = waiting.front();
    waiting.pop();

    doIt(current.root());

    Tree<T> leftTree = current.left();
    Tree<T> rightTree = current.right();

    if (!leftTree.isEmpty())
    {
        waiting.push(leftTree);
    }

    if (!rightTree.isEmpty())
    {
        waiting.push(rightTree);
    }

    visitNextLevelNode(waiting, doIt);
}

// Stand-alone function: not a member of Tree.
// Its first parameter is the Tree by reference; its second is a callable.
template <typename T, typename Visitor>
void levelTraversal(const Tree<T>& tree, Visitor doIt)
{
    if (tree.isEmpty())
    {
        return;
    }

    std::queue<Tree<T>> waiting;
    waiting.push(tree);
    visitNextLevelNode(waiting, doIt);
}
