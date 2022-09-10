#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
    pid_t retVal;                               // this is just a variable struct to store process id (from unistd library)
    cout << "process Id: " << getpid() << endl; // getpid returns id of current calling function
    retVal = fork();                            // fork system call creates child
    // if fork call fails then all unix process return -1
    // there may be variety of reasons: limit reasons, resource reasons
    // if call is successful then a clone is created immediately after fork
    // - child id is returned in parent's address space
    // - 0 is returned in child's address space

    if (retVal < 0)
    {
        // fork failed
        cout << "fork failed" << endl;
    }
    else if (retVal == 0)
    {
        // child process id
        cout << "child process id: " << getpid() << endl;
    }
    else
    {
        // parent process
        cout << "parent process: " << getpid() << endl;
    }
    // now the thing to understand is that both process are ditto same, same code and same everything, every line is same
    // so both parent and child have same code copy
    // fork has been executed, now after fork control will be given to assignment statement and assign process id
    // this means that both parallel process can do different code
    // after fork statement, both parent and child will start executing next statements

    // COPY ON WRITE
    // initially retVal variable will be shared after fork, both will be pointing same variable
    // now for efficiency purpose when any of these process changes variable, a separate copy is made in that process's address space
    // all child statements will start running after fork
}