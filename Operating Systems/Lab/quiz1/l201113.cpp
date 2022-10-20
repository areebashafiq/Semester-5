// Abdul SAboor
// 20L-1113
// BDS-5A1

#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

#define READ_END 0
#define WRITE_END 1
#define array_size 10

int main()
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        cout << "Pipe failed" << endl;
        return 1;
    }
    int pid = fork();
    if (pid == 0)
    {
        // child process
        close(pipefd[WRITE_END]);
        int arr1[array_size];
        read(pipefd[READ_END], arr1, sizeof(arr1));

        // calculating average
        int avg = 0;
        for (int i = 0; i < 10; i++)
        {
            avg += arr1[i];
        }
        cout << "Average of numbers is: " << avg / array_size << endl;
        close(pipefd[READ_END]);
        exit(0);
    }
    else if (pid > 0)
    {
        // parent process
        close(pipefd[READ_END]);
        int arr[array_size];
        for (int i = 0; i < 10; i++)
        {
            arr[i] = rand();
            cout << arr[i] << " ";
        }
        cout << endl;
        write(pipefd[WRITE_END], arr, sizeof(arr));
        close(pipefd[WRITE_END]);
    }
    else
    {
        // error
        cout << "fork failed" << endl;
    }
}