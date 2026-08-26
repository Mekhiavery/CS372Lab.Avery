#include <iostream>
#include <chrono>
#include <stack>
#include <vector>
using namespace std;
using namespace std::chrono;

void moveDisks(int, stack<int>&, stack<int>&, stack<int>&);
void printIt(int, char, char);
void MoveDisksHelper(stack<int>&, stack<int>&, char, char);

long long moveCount = 0;

int main()
{
    vector<int> diskList = { 5, 10, 15, 20, 25, 30, 35 };

    cout << "Iterative Towers of Hanoi Timing" << endl;
    cout << "--------------------------------" << endl;

    for (int numdisks : diskList)
    {
        stack<int> source;
        stack<int> dest;
        stack<int> aux;

        moveCount = 0;

        auto start = steady_clock::now();

        moveDisks(numdisks, source, aux, dest);

        auto end = steady_clock::now();

        auto timeTaken = duration_cast<milliseconds>(end - start).count();

        cout << "Disks: " << numdisks << endl;
        cout << "Moves: " << moveCount << endl;
        cout << "Time: " << timeTaken << " milliseconds" << endl;
        cout << endl;
    }

    return 0;
}

void moveDisks(int num, stack<int>& fromPeg, stack<int>& tempPeg, stack<int>& toPeg)
{
    char s = 'S';
    char d = 'D';
    char a = 'A';

    if (num % 2 == 0)
    {
        char temp = d;
        d = a;
        a = temp;
    }

    long long numberOfMoves = 1;

    for (int i = 0; i < num; i++)
    {
        numberOfMoves = numberOfMoves * 2;
    }

    numberOfMoves = numberOfMoves - 1;

    for (int i = num; i >= 1; i--)
    {
        fromPeg.push(i);
    }

    for (long long i = 1; i <= numberOfMoves; i++)
    {
        if (i % 3 == 0)
        {
            MoveDisksHelper(tempPeg, toPeg, a, d);
        }
        else if (i % 3 == 2)
        {
            MoveDisksHelper(fromPeg, tempPeg, s, a);
        }
        else
        {
            MoveDisksHelper(fromPeg, toPeg, s, d);
        }
    }
}

void MoveDisksHelper(stack<int>& source, stack<int>& dest, char s, char d)
{
    int top1;
    int top2;

    if (source.empty())
    {
        top2 = dest.top();
        dest.pop();
        source.push(top2);
        printIt(top2, d, s);
    }
    else if (dest.empty())
    {
        top1 = source.top();
        source.pop();
        dest.push(top1);
        printIt(top1, s, d);
    }
    else if (source.top() > dest.top())
    {
        top1 = source.top();
        source.pop();

        top2 = dest.top();
        dest.pop();

        source.push(top1);
        source.push(top2);

        printIt(top2, d, s);
    }
    else
    {
        top2 = dest.top();
        dest.pop();

        top1 = source.top();
        source.pop();

        dest.push(top2);
        dest.push(top1);

        printIt(top1, s, d);
    }
}

void printIt(int disk, char fromPeg, char toPeg)
{
    moveCount++;
}