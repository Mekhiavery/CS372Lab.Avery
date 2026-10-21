#pragma once
#include "Tree.hpp"

// Make a new tree without the leaf nodes from the original tree.
// This helper returns by value so every recursive call owns its result.
template <typename T>
Tree<T> pruneCopy(const Tree<T>& tree)
{
    if (tree.isEmpty())
    {
        return Tree<T>();
    }

    Tree<T> leftTree = tree.left();
    Tree<T> rightTree = tree.right();

    // A leaf has no children, so do not copy it into the new tree.
    if (leftTree.isEmpty() && rightTree.isEmpty())
    {
        return Tree<T>();
    }

    // Keep this node, and remove only the original leaves below it.
    return Tree<T>(pruneCopy(leftTree), tree.root(), pruneCopy(rightTree));
}

// Stand-alone function (not a member of Tree).
// It returns a reference to a new Tree, as the assignment requests.
// IMPORTANT: The caller owns this result and must delete &result when done.
template <typename T>
Tree<T>& prune(const Tree<T>& original)
{
    Tree<T>* result = new Tree<T>(pruneCopy(original));
    return *result;
}
