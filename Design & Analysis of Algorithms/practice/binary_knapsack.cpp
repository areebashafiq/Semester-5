// This is an implementation of the binary knapsack problem

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// brute force solution
int knapsack(vector<int> &w, vector<int> &v, int W)
{
    if (W == 0 || w.size() == 0)
        return 0;
    if (w[0] > W)
        return knapsack(vector<int>(w.begin() + 1, w.end()), vector<int>(v.begin() + 1, v.end()), W);
    return max(knapsack(vector<int>(w.begin() + 1, w.end()), vector<int>(v.begin() + 1, v.end()), W),
               v[0] + knapsack(vector<int>(w.begin() + 1, w.end()), vector<int>(v.begin() + 1, v.end()), W - w[0]));
}

// memoized solution
int memoized_knapsack_aux(vector<int> &w, vector<int> &v, int W, vector<vector<int>> &r)
{
    if (r[w.size()][W] >= 0)
        return r[w.size()][W];
    int q;
    if (W == 0 || w.size() == 0)
        q = 0;
    else if (w[0] > W)
        q = memoized_knapsack_aux(vector<int>(w.begin() + 1, w.end()), vector<int>(v.begin() + 1, v.end()), W, r);
    else
        q = max(memoized_knapsack_aux(vector<int>(w.begin() + 1, w.end()), vector<int>(v.begin() + 1, v.end()), W, r),
                v[0] + memoized_knapsack_aux(vector<int>(w.begin() + 1, w.end()), vector<int>(v.begin() + 1, v.end()), W - w[0], r));
    r[w.size()][W] = q;
    return q;
}

int memoized_knapsack(vector<int> &w, vector<int> &v, int W)
{
    vector<vector<int>> r(w.size() + 1, vector<int>(W + 1, -1));
    return memoized_knapsack_aux(w, v, W, r);
}

// bottom-up solution
int bottom_up_knapsack(vector<int> &w, vector<int> &v, int W)
{
    vector<vector<int>> r(w.size() + 1, vector<int>(W + 1, -1));
    for (int i = 0; i <= w.size(); i++)
        r[i][0] = 0;
    for (int j = 0; j <= W; j++)
        r[0][j] = 0;
    for (int i = 1; i <= w.size(); i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (w[i - 1] > j)
                r[i][j] = r[i - 1][j];
            else
                r[i][j] = max(r[i - 1][j], v[i - 1] + r[i - 1][j - w[i - 1]]);
        }
    }
    return r[w.size()][W];
}

int main()
{
    vector<int> w = {2, 3, 4, 5};
    vector<int> v = {3, 4, 5, 6};
    int W = 5;
    cout << knapsack(w, v, W) << endl;
    cout << memoized_knapsack(w, v, W) << endl;
    cout << bottom_up_knapsack(w, v, W) << endl;
    return 0;
}