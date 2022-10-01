/*
Abdul Saboor
20L-1113
BDS-5A1

This program executes three commands by creating child processes
*/

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main()
{
    pid_t retVal;
    retVal = fork();
    if (retVal < 0)
    {
        cout << "Fork Failed" << endl;
    }
    else if (retVal == 0)
    {
        // First Child Process
        pid_t retVal1;
        retVal1 = fork();
        if (retVal1 < 0)
        {
            cout << "Fork Failed" << endl;
        }
        else if (retVal1 == 0)
        {
            // Second Child Process
            pid_t retVal2;
            retVal2 = fork();
            if (retVal2 < 0)
            {
                cout << "Fork Failed" << endl;
            }
            else if (retVal2 == 0)
            {
                // Third Child Process
                execlp("mkdir", "mkdir", "myFolder_1", "my_Folder2", NULL);
            }
            else
            {
                // parent process
                wait(NULL);
                execlp("mkdir", "mkdir", "myFolder_1/mySubFolder", NULL);
            }
        }
        else
        {
            // parent process
            wait(NULL);
            execlp("ls", "ls -S", NULL);
        }
    }
    else
    {
        // parent process
        wait(NULL);
        cout << "Program Completed" << endl;
    }
}