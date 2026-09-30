#include <iostream>
#include "queue.hpp"
#include "stack.hpp"
using namespace std;

int josephus(int players, int passes)
{
    Queue<int> circle;

    for (int i = 1; i <= players; i++)
    {
        circle.push(i);
    }

    cout << "Elimination order: ";

    while (circle.size() > 1)
    {
        for (int i = 0; i < passes; i++)
        {
            int person = circle.front();
            circle.pop();
            circle.push(person);
        }

        int eliminated = circle.front();
        circle.pop();

        cout << eliminated << " ";
    }

    cout << endl;

    return circle.front();
}

int main()
{
    int players;
    int passes;

    cout << "Josephus Problem" << endl;
    cout << "----------------" << endl;

    cout << "Enter number of players: ";
    cin >> players;

    cout << "Enter number of passes: ";
    cin >> passes;

    if (players <= 0 || passes < 0)
    {
        cout << "Invalid input." << endl;
        return 0;
    }

    int winner = josephus(players, passes);

    cout << "Winner: " << winner << endl;

    return 0;
}