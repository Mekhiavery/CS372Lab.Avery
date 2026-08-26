#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

void moveDisks(int, int, int, int);
void printIt(int, int, int);

long long moveCount = 0;

int main()
{
    const int FROMPEG = 1;
    const int TOPEG = 3;
    const int TEMPPEG = 2;

    vector<int> diskList = { 5, 10, 15, 20, 25, 30, 35 };

    cout << "Recursive Towers of Hanoi Timing" << endl;
    cout << "--------------------------------" << endl;

    for (int numdisks : diskList)
    {
        moveCount = 0;

        auto start = steady_clock::now();

        moveDisks(numdisks, FROMPEG, TOPEG, TEMPPEG);

        auto end = steady_clock::now();

        auto timeTaken = duration_cast<milliseconds>(end - start).count();

        cout << "Disks: " << numdisks << endl;
        cout << "Moves: " << moveCount << endl;
        cout << "Time: " << timeTaken << " milliseconds" << endl;
        cout << endl;
    }

    return 0;
}

void moveDisks(int num, int fromPeg, int toPeg, int tempPeg)
{
    if (num > 0)
    {
        moveDisks(num - 1, fromPeg, tempPeg, toPeg);
        printIt(num, fromPeg, toPeg);
        moveDisks(num - 1, tempPeg, toPeg, fromPeg);
    }
}

void printIt(int disk, int fromPeg, int toPeg)
{
    moveCount++;
}