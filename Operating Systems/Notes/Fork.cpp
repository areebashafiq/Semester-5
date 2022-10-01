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

// /* Parent creates pipe, forks a child, child writes into
//  pipe, and parent reads from pipe */
// #include <iostream>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <cstring>
// #include <unistd.h>
// using namespace std;
// int main()
// {
//     int pipefd[2], pid, n, rc, nr, status;
//     char *testString = "Hello, world!\n";
//     char buf[1024];
//     rc = pipe(pipefd);
//     if (rc < 0)
//     {
//         perror("pipe");
//         exit(1);
//     }
//     pid = fork();
//     if (pid < 0)
//     {
//         perror("fork");
//         exit(1);
//     }
//     if (pid == 0)
//     { /* Child’s Code */
//         close(pipefd[0]);
//         // sleep(20);
//         write(pipefd[1], testString, strlen(testString));
//         close(pipefd[1]);
//         exit(0);
//     }
//     /* Parent’s Code */
//     close(pipefd[1]);
//     wait(&status);
//     n = strlen(testString);
//     nr = read(pipefd[0], buf, n);
//     rc = write(1, buf, nr);
//     close(pipefd[0]);
//     cout << "Good work child!" << endl;
//     return (0);
// }