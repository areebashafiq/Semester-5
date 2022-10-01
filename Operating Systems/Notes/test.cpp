#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
    int q, n;
    q = fork();
    if (q == 0)
    {
        n = 1;
    }
    else
    {
        wait(NULL);
        n = 6;
    }
    for (int i = n; i < n + 5; i++)
    {
        cout << " " << i;
    }
    return 0;
}