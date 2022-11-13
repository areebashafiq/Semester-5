// this is an implemtation of the first algorithm in shared memory

#include <iostream>

using namespace std;

int turn = 0; // 0 is for process 1 and 1 is for process 2

void p1()
{
    while (turn != 0)
    {
        // do nothing in bounded waiting
    }
    // critical section
    cout << "Process 1 is in critical section" << endl;
    turn = 1;
    // remainder section
}

void p2()
{
    while (turn != 1)
    {
        // do nothing in bounded waiting
    }
    // critical section
    cout << "Process 2 is in critical section" << endl;
    turn = 0;
    // remainder section
}

int main()
{
    p2();
    p1();
}