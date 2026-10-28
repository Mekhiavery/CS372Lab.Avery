#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include "Pair.hpp"
#include "List.hpp"
#include "AVLTree.hpp"

template <typename Key, typename Value>
struct PairKeyLess
{
    bool operator()(const Pair<Key, Value>& a, const Pair<Key, Value>& b) const
    { return a.first < b.first; }

    bool operator()(const Key& key, const Pair<Key, Value>& pair) const
    { return key < pair.first; }

    bool operator()(const Pair<Key, Value>& pair, const Key& key) const
    { return pair.first < key; }
};

template <typename Key, typename Value>
class Dictionary
{
private:
    AVLTree<Pair<Key, Value>, PairKeyLess<Key, Value>> items;
    mutable List<Key> keyList;
    mutable List<Value> valueList;

    void updateLists() const
    {
        keyList.clear();
        valueList.clear();
        items.inorder_traverse([this](const Pair<Key, Value>& entry)
        {
            keyList.push_back(entry.first);
            valueList.push_back(entry.second);
        });
    }

public:
    Dictionary() = default;
    Dictionary(const Dictionary& rhs) = default;
    Dictionary& operator=(const Dictionary& rhs) = default;
    Dictionary(Dictionary&& rhs) = default;
    Dictionary& operator=(Dictionary&& rhs) = default;
    ~Dictionary() = default;

    Value& operator[](const Key& key)
    {
        Pair<Key, Value>* found = items.findKey(key);
        if (!found)
        {
            items.insert(Pair<Key, Value>{key, Value{}});
            found = items.findKey(key);
        }
        return found->second;
    }

    Value& at(const Key& key)
    {
        Pair<Key, Value>* found = items.findKey(key);
        if (!found) throw std::out_of_range("Key not found in Dictionary");
        return found->second;
    }

    const Value& at(const Key& key) const
    {
        const Pair<Key, Value>* found = items.findKey(key);
        if (!found) throw std::out_of_range("Key not found in Dictionary");
        return found->second;
    }

    void insert(const Pair<Key, Value>& entry) { items.insert(entry); }
    void insert(const Key& key, const Value& value) { insert(Pair<Key, Value>{key, value}); }

    bool erase(const Key& key)
    {
        const Pair<Key, Value>* found = items.findKey(key);
        if (!found) return false;
        Pair<Key, Value> entry = *found;
        return items.remove(entry);
    }

    void clear()
    {
        items.clear();
        keyList.clear();
        valueList.clear();
    }

    List<Key>& keys() { updateLists(); return keyList; }
    const List<Key>& keys() const { updateLists(); return keyList; }
    List<Value>& values() { updateLists(); return valueList; }
    const List<Value>& values() const { updateLists(); return valueList; }

    bool isEmpty() const { return items.empty(); }
    std::size_t size() const { return items.size(); }
};
