/*
Abdul Saboor
20L-1113
BDS-5A

Homework 3
*/

#include <iostream>
using namespace std;

float bottomup(int num)
{
    float sum = 1;
    float calc = 1;
    for (int i = 1; i <= num; i++)
    {
        calc = ((float(2) / float(i)) * float(sum)) + float(i);
        sum += calc;
    }
    return calc;
}

float bruteforce(int num)
{
    if (num == 0)
        return 1;
    float total = 1;
    for (int i = 1; i < num; i++)
        total += bottomup(i);
    return ((float(2) / float(num)) * float(total)) + float(num);
}

float topdown(int num, float totals[])
{
    if (totals[num] == -1)
    {
        if (num == 0)
            totals[num] = 1;
        else
        {
            topdown(num - 1, totals);
            totals[num] = (((float(2) / float(num)) * float(totals[num - 1])) + float(num)) + totals[num - 1];
        }
    }
    return ((float(2) / float(num)) * float(totals[num - 1])) + float(num);
}

int main()
{
    cout << "Brute Force Approach" << endl;
    cout << bruteforce(3) << endl;

    cout << "\nTop Down Recursive Approach" << endl;
    float arr[6];
    arr[0] = 1;
    for (int i = 1; i < 6; i++)
        arr[i] = -1;

    cout << topdown(4, arr) << endl;

    cout << "\nBottom Up Iterative" << endl;
    cout << bottomup(5) << endl;
    return 0;
}