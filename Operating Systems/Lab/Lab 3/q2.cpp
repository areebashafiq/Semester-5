/*
Abdul Saboor
20L-1113
BDS-5A
*/

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char *arg[])
{
    pid_t retVal;
    retVal = fork();
    if (retVal < 0)
    {
        // fork failed
        cout << "fork failed" << endl;
    }
    else if (retVal == 0)
    {
        // child process
        execlp("/Users/carbon/Documents/Semester-5/Operating Systems/Lab/Lab 3/hello", NULL);
    }
    else
    {
        wait(NULL);
        // parent process
        cout << "Program Completed." << endl;
    }
}