#include <gtest/gtest.h>
#include "receiptbag.hpp"

TEST(ReceiptBagUnitTests, DefaultConstructor)
{
    ReceiptBag<int> aBag;

    EXPECT_EQ(aBag.size(), 0);
    EXPECT_EQ(aBag.count(42), 0);
}

TEST(ReceiptBagUnitTests, InsertReturnsReceipt)
{
    ReceiptBag<int> aBag;

    int receipt1 = aBag.insert(42);
    int receipt2 = aBag.insert(59);

    EXPECT_NE(receipt1, receipt2);
    EXPECT_EQ(aBag.size(), 2);
    EXPECT_EQ(aBag.count(42), 1);
    EXPECT_EQ(aBag.count(59), 1);
}

TEST(ReceiptBagUnitTests, RemoveByReceipt)
{
    ReceiptBag<int> aBag;

    int receipt1 = aBag.insert(42);
    int receipt2 = aBag.insert(59);

    int thing = aBag.remove(receipt1);

    EXPECT_EQ(thing, 42);
    EXPECT_EQ(aBag.size(), 1);
    EXPECT_EQ(aBag.count(42), 0);
    EXPECT_EQ(aBag.count(59), 1);

    thing = aBag.remove(receipt2);

    EXPECT_EQ(thing, 59);
    EXPECT_EQ(aBag.size(), 0);
}

TEST(ReceiptBagUnitTests, InsertDuplicateItems)
{
    ReceiptBag<int> aBag;

    int receipt1 = aBag.insert(42);
    int receipt2 = aBag.insert(42);

    EXPECT_EQ(aBag.size(), 2);
    EXPECT_EQ(aBag.count(42), 2);

    int thing = aBag.remove(receipt1);

    EXPECT_EQ(thing, 42);
    EXPECT_EQ(aBag.size(), 1);
    EXPECT_EQ(aBag.count(42), 1);

    thing = aBag.remove(receipt2);

    EXPECT_EQ(thing, 42);
    EXPECT_EQ(aBag.size(), 0);
}

TEST(ReceiptBagUnitTests, BadReceipt)
{
    ReceiptBag<int> aBag;

    aBag.insert(10);

    int thing = aBag.remove(999);

    EXPECT_EQ(thing, 0);
    EXPECT_EQ(aBag.size(), 1);
}

TEST(ReceiptBagUnitTests, MultipleTypes)
{
    ReceiptBag<string> strBag;

    int receipt1 = strBag.insert("hello");
    int receipt2 = strBag.insert("world");

    EXPECT_EQ(strBag.size(), 2);
    EXPECT_EQ(strBag.count("hello"), 1);
    EXPECT_EQ(strBag.count("world"), 1);

    string word = strBag.remove(receipt1);

    EXPECT_EQ(word, "hello");
    EXPECT_EQ(strBag.size(), 1);
}