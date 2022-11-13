// this is an implementation of the rod cutting problem

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// brute force solution
int cut_rod(vector<int> &p, int n)
{
    if (n == 0) // base case
        return 0;
    int q = -1;                               // initialize q to -1
    for (int i = 1; i <= n; i++)              // for each i in 1..n
        q = max(q, p[i] + cut_rod(p, n - i)); // find the max of q and p[i] + cut_rod(p, n - i)
    return q;
}

// memoized solution
int memoized_cut_rod_aux(vector<int> &p, int n, vector<int> &r)
{
    if (r[n] >= 0)
        return r[n];
    int q;
    if (n == 0)
        q = 0;
    else
    {
        q = -1;
        for (int i = 1; i <= n; i++)
            q = max(q, p[i] + memoized_cut_rod_aux(p, n - i, r));
    }
    r[n] = q;
    return q;
}

int memoized_cut_rod(vector<int> &p, int n)
{
    vector<int> r(n + 1, -1);
    return memoized_cut_rod_aux(p, n, r);
}

// bottom-up solution
int bottom_up_cut_rod(vector<int> &p, int n)
{
    vector<int> r(n + 1, -1);
    r[0] = 0;
    for (int j = 1; j <= n; j++)
    {
        int q = -1;
        for (int i = 1; i <= j; i++)
            q = max(q, p[i] + r[j - i]);
        r[j] = q;
    }
    return r[n];
}

int main()
{
    vector<int> p = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    cout << cut_rod(p, 4) << endl;
    cout << memoized_cut_rod(p, 4) << endl;
    cout << bottom_up_cut_rod(p, 4) << endl;
    return 0;
}