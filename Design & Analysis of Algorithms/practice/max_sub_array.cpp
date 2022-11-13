// This is a dynamic programming implementation of the maximum suub array problem

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_sub_array(vector<int> &A)
{
    int max_ending_here = 0;
    int max_so_far = 0;
    for (int i = 0; i < A.size(); i++)
    {
        max_ending_here = max(0, max_ending_here + A[i]);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

int main()
{
    vector<int> A = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << max_sub_array(A) << endl;
    return 0;
}